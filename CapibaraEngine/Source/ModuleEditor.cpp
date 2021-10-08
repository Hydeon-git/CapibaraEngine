#include "Globals.h"
#include "Application.h"
#include "Primitive.h"
#include "ModuleEditor.h"
#include "ModuleInput.h"

// Imgui
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"

ModuleEditor::ModuleEditor(Application* app, bool start_enabled) : Module(app, start_enabled) 
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
	bool ret = false;
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
				return false;
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
		ImGui::Begin("Configuration", &window/*, ImGuiWindowFlags_NoCollapse*/);
		if (ImGui::CollapsingHeader("Application"))
		{
			static char app_name[20];
			strcpy_s(app_name, 20, TITLE);
			if (ImGui::InputText(" App Name", app_name, 20))
			{
				App->window->SetTitle(app_name);
			}
			ImGui::Spacing();

			static char organization[20] = "UPC CITM";
			ImGui::InputText(" Organization", organization, 20);
			ImGui::Spacing();


			if (fps.size() >= 100)
			{
				for (int i = 0; i < fps.size() - 1; ++i)
				{
					fps[i] = fps[i + 1];
					ms[i] = ms[i + 1];
				}
				fps[fps.size() - 1] = App->GetFPSLimit();
				ms[ms.size() - 1] = 1000.0f / App->GetFPSLimit();
			}
			else
			{
				fps.emplace_back(App->GetFPSLimit());
				ms.emplace_back(1000.0f / App->GetFPSLimit());
			}
			int framerate = App->GetFPSLimit();
			if (ImGui::SliderInt("Max FPS", &framerate, 1, 144))
			{
				App->SetFPSLimit(framerate);
			}
			char title[25];
			sprintf_s(title, 25, "Framerate: %.1f", fps[fps.size() - 1]);
			ImGui::PlotHistogram("##framerate", &fps[0], fps.size(), 0, title, 0.0f, 100.0f, ImVec2(310, 100));
			ImGui::Spacing();
			sprintf_s(title, 25, "Milliseconds: %0.1f", ms[ms.size() - 1]);
			ImGui::PlotHistogram("##milliseconds", &ms[0], ms.size(), 0, title, 0.0f, 40.0f, ImVec2(310, 100));

			//ImGui::PlotHistogram("##memory", &memory[0], memory.size(), 0, "Memory Consumption", 0.0f, (float)stats.peakReportedMemory * 1.2f, ImVec2(310, 100));

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

			if (ImGui::Checkbox("Fullscreen", &fullscreen))
			{
				SDL_SetWindowFullscreen(App->window->window, fullscreen);
			}
			ImGui::SameLine();
			if (ImGui::Checkbox("Resizable", &resizable))
			{
				//SDL_SetWindowResizable(App->window->window, (SDL_bool)resizable);

			}
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("Restart to apply");
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
		if (ImGui::CollapsingHeader("File System"))
		{


		}
		if (ImGui::CollapsingHeader("Input"))
		{


		}
		if (ImGui::CollapsingHeader("Hardware"))
		{
			ImGui::Text("CPUs: %d (Cache: %dkb)", SDL_GetCPUCount(), SDL_GetCPUCacheLineSize());
			ImGui::Text("System RAM: %.2fGb", (float)SDL_GetSystemRAM() / 1024.f);


		}
		ImGui::End();

	}
	if (windowHelp)
	{
		if (ImGui::Begin("About Us", &windowHelp))
		{
			ImGui::TextWrapped
			(
				"Capibara Engine is being developed for Videogame Engines Class in CITM-UPC"
			);
		}
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