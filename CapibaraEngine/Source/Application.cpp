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
	AddModule(sceneIntro);
	AddModule(editor);

	// Renderer last!
	AddModule(renderer3D);
}

Application::~Application()
{
	std::list<Module*>::iterator item;
	for (item = --moduleList.end(); item != moduleList.begin(); --item)
	{
		delete *item;
	}
}

bool Application::Init()
{
	bool ret = true;

	// Call Init() in all modules
	
	std::list<Module*>::iterator item;
	for (item = moduleList.begin(); item != moduleList.end() && ret; ++item)
	{
		ret = (*item)->Init();
	}

	// After all Init calls we call Start() in all modules
	LOG("Application Start --------------");	

	for (item = moduleList.begin(); item != moduleList.end() && ret; ++item)
	{
		ret = (*item)->Start();
	}
	
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
	
	std::list<Module*>::iterator item = moduleList.begin();
	
	for (item = moduleList.begin(); item != moduleList.end() && ret; ++item)
	{
		ret = (*item)->PreUpdate(dt);
	}
	for (item = moduleList.begin(); item != moduleList.end() && ret; ++item)
	{
		ret = (*item)->Update(dt);
	}
	for (item = moduleList.begin(); item != moduleList.end() && ret; ++item)
	{
		ret = (*item)->PostUpdate(dt);
	}

	FinishUpdate();
	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;
	std::list<Module*>::iterator item;

	for (item = moduleList.end(); item != moduleList.begin() && ret; --item)
	{
		ret = (*item)->CleanUp();
	}
	return ret;
}

void Application::AddModule(Module* mod)
{
	moduleList.push_back(mod);
}