#pragma once

#include <vector>

#include "Module.h"
#include "Globals.h"
#include "ConsolePanel.h"

using namespace std;

#define MAX_IT_HIST 100

class ModuleEditor : public Module
{
public:
	ModuleEditor(Application* app, bool start_enabled = true);
	~ModuleEditor();

	bool Start();
	bool Update(float dt);
	bool CleanUp();

	// Imgui Variables
	bool window;
	bool windowHelp;
	bool demo;

	bool fullscreen;
	bool resizable;

	float fpsLog[MAX_IT_HIST];
	int i=0;

	//vector<float> fps_log;
private:
	ConsolePanel consolePanel;
};
