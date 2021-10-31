#pragma once

#include <vector>
#include "Module.h"
#include "Globals.h"

class MeshData;

class EngineScene : public Module
{
public:
	EngineScene(Application* app, bool start_enabled = true);
	~EngineScene();

	bool Start() override;
	bool Update(float dt) override;
	bool Draw() override;
	bool PostUpdate(float dt) override;
	bool CleanUp() override;


	std::vector<MeshData> meshData;
};
