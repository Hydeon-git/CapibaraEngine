#pragma once
#include "Module.h"
#include "Globals.h"
#include <vector>

using namespace std;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	bool Update(float dt);
	bool PostUpdate(float dt);
	bool CleanUp();
	

	vector<float> frames;
public:
};
