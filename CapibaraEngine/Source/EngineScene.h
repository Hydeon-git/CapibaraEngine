#pragma once

#include <vector>
#include "Module.h"
#include "Globals.h"
#include "GameObject.h"

#include "PrimitiveCube.h"
#include "MeshComponent.h"

using namespace std;

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
	void CreateGameObject(GameObject* obj);

	vector<MeshComponent> meshData;

private:
	vector<GameObject*> gameObjects;
};
