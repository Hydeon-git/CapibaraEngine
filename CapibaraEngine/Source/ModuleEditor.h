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

	bool Start() override;
	bool Update(float dt) override;
	bool CleanUp() override;

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
