#pragma once

#include <vector>

#include "Globals.h"
#include "Timer.h"
#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleSceneIntro.h"
#include "ModuleEditor.h"
#include "ModuleFileSystem.h"
#include "ModuleRenderer3D.h"
#include "ModuleCamera3D.h"

#include <string>

class ModuleFbxLoader;

class Application
{
public:
	ModuleWindow* window;
	ModuleInput* input;
	ModuleSceneIntro* sceneIntro;
	ModuleEditor* editor;
	ModuleFileSystem* fileSystem;
	ModuleFbxLoader* fbxLoader;
	ModuleRenderer3D* renderer3D;
	ModuleCamera3D* camera;

private:

	Timer ms_timer;
	Timer lastSecFrameTime;

	unsigned int lastSecFrameCount = 0;
	unsigned int prevLastSecFrameCount = 0;
	unsigned int frameCount = 0;

	float	dt;
	int cappedMs = -1;
	std::vector<Module*> moduleList;


public:

	Application();
	~Application();

	bool Init();
	bool Update();
	bool CleanUp();
	int GetFPSLimit() const;
	void SetFPSLimit(const float fps);
	void RequestBrowser(const std::string& website);
private:

	void AddModule(Module* mod);
	void PrepareUpdate();
	void FinishUpdate();
};