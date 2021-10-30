#include "Globals.h"
#include "Application.h"
#include "Primitive.h"
#include "EngineScene.h"
#include "ModuleInput.h"
#include "ModuleFbxLoader.h"
#include "ModuleTextureLoader.h"

EngineScene::EngineScene(Application* app, bool start_enabled) : Module(app, start_enabled) {}
EngineScene::~EngineScene() {}

// Load assets
bool EngineScene::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	App->fbxLoader->LoadFile("Assets/BakerHouse.fbx", meshData);
	App->textureLoader->LoadTexture("Textures/bakeHouse.png");
	
	return ret;
}

bool EngineScene::Update(float dt)
{
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();

	return true;
}

bool EngineScene::Draw()
{
	for (int i = 0; i < meshData.size(); i++)
	{
		meshData[i].DrawMesh();
	}

	return true;
}

bool EngineScene::PostUpdate(float dt)
{		
	return true;
}

// Unload assets
bool EngineScene::CleanUp()
{
	LOG("Unloading Intro scene");


	return true;
}