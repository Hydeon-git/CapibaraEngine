#pragma once

#include <vector>
#include "Module.h"
#include "Globals.h"

#include "FbxLoader.h"
#include "MeshData.h"

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	bool Update(float dt);
	bool PostUpdate(float dt);
	bool CleanUp();	

private:
	std::vector<MeshData> meshData;
};
