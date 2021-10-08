#pragma once

#include <vector>

#include "Module.h"
#include "Globals.h"
#include "ConsolePanel.h"

using namespace std;


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
	bool borderless;
	bool fullDesktop;

	vector<float> fps;
	vector<float> ms;
	vector<float> memory;

private:
	ConsolePanel consolePanel;
};
