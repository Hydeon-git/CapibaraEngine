#pragma once

#include <vector>

#include "Globals.h"
#include "Timer.h"
#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleSceneIntro.h"
#include "ModuleEditor.h"
#include "ModuleRenderer3D.h"
#include "ModuleCamera3D.h"

#include <string>

class Application
{
public:
	ModuleWindow* window;
	ModuleInput* input;
	ModuleSceneIntro* sceneIntro;
	ModuleEditor* editor;
	ModuleRenderer3D* renderer3D;
	ModuleCamera3D* camera;

private:

	Timer	ms_timer;
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