#include "ConfigurationPanel.h"
#include "Globals.h"
#include "Application.h"

#include "SDL.h"

ConfigurationPanel::ConfigurationPanel(bool enabled) : Panels(enabled) 
{
	window = true;
	resizable = true;
	fullscreen = false;
	fullDesktop = SDL_WINDOW_FULLSCREEN_DESKTOP;
	borderless = false;
}
ConfigurationPanel::~ConfigurationPanel() {}


bool ConfigurationPanel::Update(float dt)
{
	if (window)
	{
		if (fps_log.size() >= 100)
		{
			for (int i = 0; i < fps_log.size() - 1; ++i)
			{
				fps_log[i] = fps_log[i + 1];
				ms_log[i] = ms_log[i + 1];
			}
			fps_log[fps_log.size() - 1] = App->GetFPSLimit();
			ms_log[ms_log.size() - 1] = 1000.0f / App->GetFPSLimit();
		}
		else
		{
			fps_log.emplace_back(App->GetFPSLimit());
			ms_log.emplace_back(1000.0f / App->GetFPSLimit());
		}

		ImGui::Begin("Configuration", &window);
		if (ImGui::CollapsingHeader("Application"))
		{
			static char app_name[20];
			strcpy_s(app_name, 20, TITLE);
			if (ImGui::InputText("App Name", app_name, 20))
			{
				App->window->SetTitle(app_name);
			}
			ImGui::Spacing();

			static char organization[20] = ORG;
			ImGui::InputText("Organization", organization, 20);
			ImGui::Spacing();


			int framerate = App->GetFPSLimit();

			if (ImGui::SliderInt("Max FPS", &framerate, 1, 144))
			{
				App->SetFPSLimit(framerate);
			}

			ImGui::Text("Limit Framerate: ");
			ImGui::SameLine(); ImGui::TextColored({ 255,255,0,255 }, "%d", framerate);

			char title[25];
			sprintf_s(title, 25, "Framerate: %.1f", fps_log[fps_log.size() - 1]);
			ImGui::PlotHistogram("##framerate", &fps_log[0], fps_log.size(), 0, title, 0.0f, 100.0f, ImVec2(310, 100));
			ImGui::Spacing();
			sprintf_s(title, 25, "Milliseconds: %0.1f", ms_log[ms_log.size() - 1]);
			ImGui::PlotHistogram("##milliseconds", &ms_log[0], ms_log.size(), 0, title, 0.0f, 40.0f, ImVec2(310, 100));


		}
		if (ImGui::CollapsingHeader("Window"))
		{
			if (ImGui::SliderFloat("Brightness", &App->window->brightness, 0.0f, 1.0f, "%f", 0))
			{
				SDL_SetWindowBrightness(App->window->window, App->window->brightness);
			}

			if (ImGui::SliderInt("Width", &App->window->width, 640, 1920, "%d", 0))
			{
				SDL_SetWindowSize(App->window->window, App->window->width, App->window->height);
			}

			if (ImGui::SliderInt("Height", &App->window->height, 480, 1080, "%d", 0))
			{
				SDL_SetWindowSize(App->window->window, App->window->width, App->window->height);
			}

			ImGui::Text("Refresh rate: ");
			ImGui::SameLine(); ImGui::TextColored({ 255,255,0,255 }, "%.0f", ImGui::GetIO().Framerate);


			if (ImGui::Checkbox("Fullscreen", &fullscreen))
			{
				SDL_SetWindowFullscreen(App->window->window, fullscreen);
			}
			ImGui::SameLine();
			if (ImGui::Checkbox("Resizable", &resizable))
			{
				//SDL_SetWindowResizable(App->window->window, (SDL_bool)resizable);

			}
			if (ImGui::Checkbox("Borderless", &borderless))
			{
				SDL_SetWindowBordered(App->window->window, (SDL_bool)borderless);
			}
			ImGui::SameLine();
			if (ImGui::Checkbox("Full desktop", &fullDesktop))
			{
				SDL_SetWindowFullscreen(App->window->window, fullDesktop);
			}

			//App->window->SetResizable((SDL_bool)resizable);

		}

		if (ImGui::CollapsingHeader("Input"))
		{
			int mouseX, mouseY;
			App->input->GetMousePosition(mouseX, mouseY);
			ImGui::Text("Mouse Position:");
			ImGui::SameLine();
			ImGui::TextColored({ 255,255,0,255 }, "%i,%i", mouseX, mouseY);

			App->input->GetMouseMotion(mouseX, mouseY);
			ImGui::Text("Mouse Motion:");
			ImGui::SameLine();
			ImGui::TextColored({ 255,255,0,255 }, "%i,%i", mouseX, mouseY);

			int wheel = App->input->GetMouseZ();
			ImGui::Text("Mouse Wheel:");
			ImGui::SameLine();
			ImGui::TextColored({ 255,255,0,255 }, "%i", wheel);

		}

		if (ImGui::CollapsingHeader("Hardware"))
		{
			SDL_version version;
			SDL_VERSION(&version);
			ImGui::Text("SDL Version: ");
			ImGui::SameLine(); ImGui::TextColored({ 255,255,0,255 }, "%d.%d.%d", version.major, version.minor, version.patch);

			ImGui::Separator();

			ImGui::Text("CPUs: ");
			ImGui::SameLine(); ImGui::TextColored({ 255,255,0,255 }, "%d (Cache: %dkb)", SDL_GetCPUCount(), SDL_GetCPUCacheLineSize());

			ImGui::Text("System RAM: ");
			ImGui::SameLine(); ImGui::TextColored({ 255,255,0,255 }, "%.2fGb", (float)SDL_GetSystemRAM() / 1024.f);

			ImGui::Text("Caps: ");
			ImGui::SameLine(); if (SDL_Has3DNow())ImGui::TextColored({ 255,255,0,255 }, "3DNow, ");
			ImGui::SameLine();  if (SDL_HasAltiVec())ImGui::TextColored({ 255,255,0,255 }, "AltiVec, ");
			ImGui::SameLine(); if (SDL_HasAVX())ImGui::TextColored({ 255,255,0,255 }, "AVX, ");
			ImGui::SameLine();  if (SDL_HasAVX2())ImGui::TextColored({ 255,255,0,255 }, "AVX2, ");
			ImGui::SameLine();  if (SDL_HasMMX())ImGui::TextColored({ 255,255,0,255 }, "MMX, ");
			ImGui::SameLine();  if (SDL_HasRDTSC())ImGui::TextColored({ 255,255,0,255 }, "RDTSC, ");
			ImGui::SameLine();  if (SDL_HasSSE())ImGui::TextColored({ 255,255,0,255 }, "SSE, ");
			ImGui::SameLine();  if (SDL_HasSSE2())ImGui::TextColored({ 255,255,0,255 }, "SSE2, ");
			if (SDL_HasSSE3())ImGui::TextColored({ 255,255,0,255 }, "SSE3, ");
			ImGui::SameLine();  if (SDL_HasSSE41())ImGui::TextColored({ 255,255,0,255 }, "SSE41, ");
			ImGui::SameLine();  if (SDL_HasSSE42())ImGui::TextColored({ 255,255,0,255 }, "SSE42 ");

			ImGui::Separator();

		}
		ImGui::End();

	}
	return true;
}