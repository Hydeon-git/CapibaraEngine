#pragma once

#include <vector>
#include "Panels.h"

using namespace std;

class ConfigurationPanel : public Panels
{
public:
	ConfigurationPanel(bool enabled = true);
	~ConfigurationPanel();

	bool Update(float dt) override;

	// Imgui Variables
	bool window;
	

	bool fullscreen;
	bool resizable;
	bool borderless;
	bool fullDesktop;

	vector<float> fpsLog;
	vector<float> msLog;
	vector<float> memoryLog;

private:

};
