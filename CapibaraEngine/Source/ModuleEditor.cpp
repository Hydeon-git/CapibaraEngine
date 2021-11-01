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
	windowHelp = false;
	demo = false;
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
	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
	{
		ImGuiID dockspace_id = ImGui::GetID("CapibaraDockSpace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None);
	}
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
		if (ImGui::BeginMenu("Basic Shapes"))
		{
			if (ImGui::MenuItem("Cube"))
			{
				App->engineScene->cubeDraw = true;
			}
			if (ImGui::MenuItem("Sphere"))
			{
				App->engineScene->sphereDraw = true;
			}
			if (ImGui::MenuItem("Pyramid"))
			{
				App->engineScene->pyramidDraw = true;
			}
			if (ImGui::MenuItem("Cylinder"))
			{
				App->engineScene->cylinderDraw = true;
			}



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
				"\n- ImGui 1.86 WIP"
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

	consolePanel.Update(dt);
	configurationPanel.Update(dt);
	hierarchyPanel.Update(dt);
	inspectorPanel.Update(dt);

	return ret;
}

// Unload assets
bool ModuleEditor::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}