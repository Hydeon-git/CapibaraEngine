#pragma once

#include <vector>
#include "Module.h"
#include "Globals.h"

#include "fbxLoader.h"
#include "MeshData.h"

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

private:
	fbxLoader meshLoader;
	MeshData meshData;
};
