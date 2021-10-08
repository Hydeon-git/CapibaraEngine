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
	void SetFPSLimit(const float fps);
	inline int GetFPSLimit() const { return ((1.0f / (float)cappedMs) * 1000.0f); }
private:

	void AddModule(Module* mod);
	void PrepareUpdate();
	void FinishUpdate();
};