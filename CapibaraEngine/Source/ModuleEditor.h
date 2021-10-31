#pragma once

#include <vector>

#include "Module.h"
#include "Globals.h"
#include "ConsolePanel.h"
#include "ConfigurationPanel.h"

using namespace std;


class ModuleEditor : public Module
{
public:
	ModuleEditor(bool start_enabled = true);
	~ModuleEditor();

	bool Start() override;
	bool Update(float dt) override;
	bool CleanUp() override;

	bool windowHelp;
	bool demo;

	ConsolePanel consolePanel;
	ConfigurationPanel configurationPanel;

private:
	
};
