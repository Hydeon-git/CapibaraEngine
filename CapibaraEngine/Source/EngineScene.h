#pragma once

#include <vector>
#include "Module.h"
#include "Globals.h"
#include "GameObject.h"

#include "MeshComponent.h"

// Primitives
#include "PrimitiveCube.h"
#include "PrimitiveCylinder.h"
#include "PrimitivePyramid.h"
#include "PrimitiveSphere.h"

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
		
	void CreateGameObject(GameObject* obj);

	vector<MeshComponent> meshData;

	PrimitiveCube* cube;
	PrimitiveCylinder* cylinder;
	PrimitivePyramid* pyramid;
	PrimitiveSphere* sphere;
	bool cubeDraw = false;
	bool cylinderDraw = false;
	bool pyramidDraw = false;
	bool sphereDraw = false;

private:
	vector<GameObject*> gameObjects;
};
