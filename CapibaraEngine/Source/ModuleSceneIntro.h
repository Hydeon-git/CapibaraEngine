#pragma once

#include <vector>
#include "Module.h"
#include "Globals.h"

#include "MeshData.h"

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start() override;
	bool Update(float dt) override;
	bool Draw() override;
	bool PostUpdate(float dt) override;
	bool CleanUp() override;


	std::vector<MeshData> meshData;
};
