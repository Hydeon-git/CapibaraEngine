#pragma once

#include <vector>
#include "Module.h"
#include "Globals.h"

#include "PrimitiveCube.h"
#include "MeshComponent.h"

class EngineScene : public Module
{
public:
	EngineScene(bool start_enabled = true);
	~EngineScene();

	bool Start() override;
	bool Update(float dt) override;
	bool Draw() override;
	bool PostUpdate(float dt) override;
	bool CleanUp() override;

	PrimitiveCube* cube;
	std::vector<MeshComponent> meshData;
};
