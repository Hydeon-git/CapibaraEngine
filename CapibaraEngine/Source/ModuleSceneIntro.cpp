#include "Globals.h"
#include "Application.h"
#include "Primitive.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"

// Imgui
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl2.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));
	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update(float dt)
{
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();

	return UPDATE_CONTINUE;
}

update_status ModuleSceneIntro::PostUpdate()
{
	if (ImGui::BeginMainMenuBar())
	{
		bool ret = false;

		if (ImGui::BeginMenu("File"))
		{			
			ImGui::MenuItem("New Project", NULL, &ret);
			ImGui::MenuItem("Open Project", NULL, &ret);

			ImGui::Separator();

			ImGui::MenuItem("Save", "Ctrl + S", &ret);
			if (ImGui::MenuItem("Exit", "Alt + F4", &ret))
			{
				return update_status::UPDATE_STOP;
			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Edit Window"))
		{
			ImGui::MenuItem("Undo", "Ctrl + Z", &ret);
			ImGui::MenuItem("Redo", "Ctrl + Y", &ret);
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Main Window"))
		{
			ImGui::MenuItem("Demo Menu", NULL, &window);
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Help Window"))
		{
			ImGui::MenuItem("About Us", NULL, &windowHelp);
			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}
	if (window)
	{
		ImGui::ShowDemoWindow(&window);

		ImGui::Begin("Capibara Engine", &window);
		if (ImGui::Button("Close", ImVec2(0, 0)))
		{
			return update_status::UPDATE_STOP;
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

	return update_status::UPDATE_CONTINUE;
}