#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	// Imgui Variables
	bool window;
	bool windowHelp;
public:
};