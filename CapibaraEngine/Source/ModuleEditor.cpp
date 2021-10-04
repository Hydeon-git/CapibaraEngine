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
	return true;
}

bool ModuleEditor::PostUpdate(float dt)
{	
	if (ImGui::BeginMainMenuBar())
	{
		bool ret = false;

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
		if (ImGui::BeginMenu("Demo"))
		{
			ImGui::MenuItem("Demo Menu", NULL, &demo);
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Help"))
		{
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


			// Histogram ============
			if (i == (MAX_IT_HIST - 1))
			{
				for (int y = 0; y < i; y++)
				{
					int aux = y + 1;
					fpsLog[y] = fpsLog[aux];
					fpsLog[i] = ImGui::GetIO().Framerate;
				}
			}
			else
			{
				fpsLog[i] = ImGui::GetIO().Framerate;
				i++;
			}
			char title[25];
			sprintf_s(title, 25, "Framerate: %.1f", ImGui::GetIO().Framerate);
			ImGui::PlotHistogram("##framerate", fpsLog, IM_ARRAYSIZE(fpsLog), 0, title, 0.0f, 100.0f, ImVec2(310, 100));
			ImGui::Spacing();
			//sprintf_s(title, 25, "Milliseconds: %0.1f", ImGui::GetIO().Framerate);
			//ImGui::PlotHistogram("##milliseconds", fpsLog, IM_ARRAYSIZE(fpsLog), 0, title, 0.0f, 40.0f, ImVec2(310, 100));

		}
		if (ImGui::CollapsingHeader("Window"))
		{
			/*if (ImGui::SliderInt(" Width", &App->window->width, 0, 1920)) 
			{
				SDL_SetWindowSize(App->window->window, App->window->width, App->window->height);
			}*/
			if (ImGui::Checkbox("Fullscreen", &fullscreen))
				App->window->SetFullscreen(fullscreen);
			ImGui::SameLine();
			if (ImGui::Checkbox("Resizable", &resizable)){}
				//SDL_SetWindowResizable(App->window->window, (SDL_bool)resizable);
				//App->window->SetResizable((SDL_bool)resizable);
		
		}
		if (ImGui::CollapsingHeader("Hardware"))
		{


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

	return true;
}

// Unload assets
bool ModuleEditor::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}