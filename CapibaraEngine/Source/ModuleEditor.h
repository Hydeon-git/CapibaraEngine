#pragma once
#include "Module.h"
#include "Globals.h"

class ModuleEditor : public Module
{
public:
	ModuleEditor(Application* app, bool start_enabled = true);
	~ModuleEditor();

	bool Start();
	bool Update(float dt);
	bool PostUpdate(float dt);
	bool CleanUp();

	// Imgui Variables
	bool window;
	bool windowHelp;
public:
};
