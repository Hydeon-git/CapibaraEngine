#include "Globals.h"
#include "Application.h"
#include "Primitive.h"
#include "ModuleEditor.h"
#include "ModuleInput.h"

// Imgui
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"

ModuleEditor::ModuleEditor(bool start_enabled) : Module(start_enabled) 
{
	window = true;
	windowHelp = false;
	demo = false;
	resizable = true;
	fullscreen = false;
	fullDesktop = SDL_WINDOW_FULLSCREEN_DESKTOP;
	borderless = false;
}
ModuleEditor::~ModuleEditor() {}

// Load assets
bool ModuleEditor::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;
	
	return ret;
}

bool ModuleEditor::Update(float dt)
{	
	bool ret = true;
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			ImGui::MenuItem("New Project", NULL, &ret);
			ImGui::MenuItem("Open Project", "Ctrl + O", &ret);
			ImGui::MenuItem("Save Project", "Ctrl + S", &ret);
			ImGui::Separator();

			if (ImGui::MenuItem("Exit", "Alt + F4", &ret))
			{
				ret = false;
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Edit"))
		{
			ImGui::MenuItem("Undo", "Ctrl + Z", &ret);
			ImGui::MenuItem("Redo", "Ctrl + Y", &ret);
			ImGui::EndMenu();
		}
		
		if (ImGui::BeginMenu("Help"))
		{
			ImGui::MenuItem("Demo Menu", NULL, &demo);

			if (ImGui::MenuItem("Documentation"))
				App->RequestBrowser("https://github.com/Hydeon-git/CapibaraEngine");
			
			if (ImGui::MenuItem("Download latest"))
				App->RequestBrowser("https://github.com/Hydeon-git/CapibaraEngine/releases");
			
			if (ImGui::MenuItem("Report a bug"))
				App->RequestBrowser("https://github.com/Hydeon-git/CapibaraEngine/issues");

			ImGui::MenuItem("About Us", NULL, &windowHelp);
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
	if (demo)
	{
		ImGui::ShowDemoWindow(&demo);
	}

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
	if (windowHelp)
	{
		if (ImGui::Begin("About", &windowHelp))
		{
			ImGui::TextWrapped
			(
				"Capibara Engine 1.0\n"
				"\nDeveloped for Videogame Engines Class in CITM-UPC"
				"\nBy Albert Pou and Arnau Bonada\n"
				"\n3rd Party Libraries used:"
				"\n- SDL 2.0.16"
				"\n- Glew 2.1"
				"\n- ImGui 1.84"
				"\n- MathGeoLib 1.5"
				"\n- OpenGL 3.1"
				"\n- Assimp 5.0.1"
				"\n- DevIL 1.8.0"
				"\n\nLicense:"
				"\n\nMIT License"
				"\n\nCopyright (c) 2021 Capibara Engine"
				"\n\nPermission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the 'Software'), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:"
				"\n\nThe above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software."
				"\n\nTHE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE."
			);		}
		ImGui::End();
	}

	ret = consolePanel.Update(dt);
	return ret;
}

// Unload assets
bool ModuleEditor::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}