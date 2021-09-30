#include "Application.h"
#include <list>

Application::Application()
{
	window = new ModuleWindow(this);
	input = new ModuleInput(this);
	sceneIntro = new ModuleSceneIntro(this, true);
	editor = new ModuleEditor(this, true);
	renderer3D = new ModuleRenderer3D(this);
	camera = new ModuleCamera3D(this);

	// The order of calls is very important!
	// Modules will Init() Start() and Update in this order
	// They will CleanUp() in reverse order

	// Main Modules
	AddModule(window);
	AddModule(camera);
	AddModule(input);

	// Scenes
	AddModule(editor);
	AddModule(sceneIntro);
	

	// Renderer last!
	AddModule(renderer3D);
}

Application::~Application()
{
	for (int i = 0; i < moduleList.size(); i++)
	{
		delete moduleList[i];
	}
	moduleList.clear();
}

bool Application::Init()
{
	bool ret = true;

	// Call Init() in all modules
	
	
	for (unsigned int i = 0; i < moduleList.size(); i++)
	{
		ret = moduleList[i]->Init();
	}

	// After all Init calls we call Start() in all modules
	LOG("Application Start --------------");	

	for (unsigned int i = 0; i < moduleList.size(); i++)
	{
		ret = moduleList[i]->Start();
	}
	
	ms_timer.Start();
	return ret;
}

// ---------------------------------------------
void Application::PrepareUpdate()
{	
	dt = (float)ms_timer.Read() / 1000.0f;
	ms_timer.Start();
}

// ---------------------------------------------
void Application::FinishUpdate()
{	
}

// Call PreUpdate, Update and PostUpdate on all modules
bool Application::Update()
{
	bool ret = true;
	PrepareUpdate();
	
	
	for (unsigned int i = 0; i < moduleList.size(); i++)
	{
		if (ret) ret = moduleList[i]->PreUpdate(dt);
	}	
	for (unsigned int i = 0; i < moduleList.size(); i++)
	{
		if (ret) ret = moduleList[i]->Update(dt);
	}	
	for (unsigned int i = 0; i < moduleList.size(); i++)
	{
		if (ret) ret = moduleList[i]->PostUpdate(dt);
	}
	

	FinishUpdate();
	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for (int i = moduleList.size() - 1; i >= 0 && ret == true; --i)
	{
		ret = moduleList[i]->CleanUp();
	}


	return ret;
}

void Application::AddModule(Module* mod)
{
	moduleList.push_back(mod);
}