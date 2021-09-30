#pragma once
#include "Module.h"
#include "Globals.h"
#include <vector>

using namespace std;

#define MAX_IT_HIST 100

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
	bool demo;

	float fpsLog[MAX_IT_HIST];
	int i=0;

	//vector<float> fps_log;
public:
};
