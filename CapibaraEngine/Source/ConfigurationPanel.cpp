#include "ConfigurationPanel.h"
#include "Globals.h"
#include "Application.h"

#include "mmgr.h"

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
		if (fpsLog.size() >= 100)
		{
			for (int i = 0; i < fpsLog.size() - 1; ++i)
			{
				fpsLog[i] = fpsLog[i + 1];
				msLog[i] = msLog[i + 1];
			}
			fpsLog[fpsLog.size() - 1] = App->GetFPSLimit();
			msLog[msLog.size() - 1] = 1000.0f / App->GetFPSLimit();
		}
		else
		{
			fpsLog.push_back(App->GetFPSLimit());
			msLog.push_back(1000.0f / App->GetFPSLimit());
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
			sprintf_s(title, 25, "Framerate: %.1f", fpsLog[fpsLog.size() - 1]);
			ImGui::PlotHistogram("##framerate", &fpsLog[0], fpsLog.size(), 0, title, 0.0f, 100.0f, ImVec2(310, 100));
			ImGui::Spacing();
			sprintf_s(title, 25, "Milliseconds: %0.1f", msLog[msLog.size() - 1]);
			ImGui::PlotHistogram("##milliseconds", &msLog[0], msLog.size(), 0, title, 0.0f, 40.0f, ImVec2(310, 100));

			sMStats stats = m_getMemoryStatistics();

			if (memoryLog.size() == 100)
			{
				for (int i = 0; i < memoryLog.size() - 1; ++i)
				{
					memoryLog[i] = memoryLog[i + 1];
				}				
				memoryLog[memoryLog.size() - 1] = (float)stats.totalReportedMemory;
			}
			else
				memoryLog.push_back((float)stats.totalReportedMemory);

			ImGui::Spacing();
			sprintf_s(title, 25, "Memory Consumption", memoryLog[memoryLog.size() - 1]);
			ImGui::PlotHistogram("##memory", &memoryLog[0], memoryLog.size(), 0, title, 0.0f, (float)stats.peakReportedMemory * 1.2f, ImVec2(310, 100));

			ImGui::Spacing();
			ImGui::Text("Total Reported Mem: %i", stats.totalReportedMemory);
			ImGui::Text("Total Actual Mem: %i", stats.totalActualMemory);
			ImGui::Text("Peak Reported Mem: %i", stats.peakReportedMemory);
			ImGui::Text("Peak Actual Mem: %i", stats.peakActualMemory);
			ImGui::Text("Accumulated Reported Mem: %i", stats.accumulatedReportedMemory);
			ImGui::Text("Accumulated Actual Mem: %i", stats.accumulatedActualMemory);
			ImGui::Text("Accumulated Alloc Unit Count: %i", stats.accumulatedAllocUnitCount);
			ImGui::Text("Total Alloc Unit Count: %i", stats.totalAllocUnitCount);
			ImGui::Text("Peak Alloc Unit Count: %i", stats.peakAllocUnitCount);

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