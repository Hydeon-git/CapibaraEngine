#include "Application.h"
#include "ModuleFbxLoader.h"

Application::Application()
{
	window = new ModuleWindow();
	input = new ModuleInput();
	engineScene = new EngineScene(true);
	editor = new ModuleEditor(true);
	fileSystem = new ModuleFileSystem(true);
	fbxLoader = new ModuleFbxLoader(true);
	renderer3D = new ModuleRenderer3D();
	camera = new ModuleCamera3D();

	// Core System
	AddModule(window);
	AddModule(camera);
	AddModule(input);	

	// Management Modules
	AddModule(editor);
	AddModule(fileSystem);
	AddModule(fbxLoader);

	// Scene
	AddModule(engineScene);

	// Renderer Last
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
	for (unsigned int i = 0; i < moduleList.size() && ret; i++)
	{
		ret = moduleList[i]->Init();
	}

	// After all Init calls we call Start() in all modules
	LOG("Application Start --------------");	

	for (unsigned int i = 0; i < moduleList.size() && ret; i++)
	{
		ret = moduleList[i]->Start();
	}
	cappedMs = 1000 / 60;
	msTimer.Start();
	return ret;
}

// ---------------------------------------------
void Application::PrepareUpdate()
{	
	frameCount++;
	lastSecFrameCount++;

	dt = (float)msTimer.Read() / 1000.0f;
	msTimer.Start();
}

// ---------------------------------------------
void Application::FinishUpdate()
{	
	if (lastSecFrameTime.Read() > 1000)
	{
		prevLastSecFrameCount = lastSecFrameCount;
		lastSecFrameCount = 0;
		lastSecFrameTime.Start();
	}

	unsigned int lastFrameMs = msTimer.Read();

	if ((cappedMs > 0) && (lastFrameMs < cappedMs))
	{
		SDL_Delay(cappedMs - lastFrameMs);
	}
}

// Call PreUpdate, Update and PostUpdate on all modules
bool Application::Update()
{
	bool ret = true;
	PrepareUpdate();
	
	
	for (unsigned int i = 0; i < moduleList.size() && ret; i++)
	{
		if (ret) ret = moduleList[i]->PreUpdate(dt);
	}	
	for (unsigned int i = 0; i < moduleList.size() && ret; i++)
	{
		if (ret) ret = moduleList[i]->Update(dt);
	}	
	for (unsigned int i = 0; i < moduleList.size() && ret; i++)
	{
		if (ret) ret = moduleList[i]->Draw();
	}	
	for (unsigned int i = 0; i < moduleList.size() && ret; i++)
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

int Application::GetFPSLimit() const
{
	return ((1.0f / (float)cappedMs) * 1000.0f);
}

void Application::SetFPSLimit(const float fps)
{
	if (fps > 0) cappedMs = 1000 / fps;
	else cappedMs = 0;
}

void Application::RequestBrowser(const std::string& website)
{
	ShellExecuteA(NULL, "open", website.c_str(), NULL, NULL, SW_SHOWNORMAL);
}