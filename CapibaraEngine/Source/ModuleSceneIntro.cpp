#include "Globals.h"
#include "Application.h"
#include "Primitive.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled) {}
ModuleSceneIntro::~ModuleSceneIntro() {}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	FbxLoader fbxLoader;
	fbxLoader.LoadFile("Assets/BakerHouse.fbx", meshData);

	return ret;
}

bool ModuleSceneIntro::Update(float dt)
{
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();

	return true;
}

bool ModuleSceneIntro::Draw()
{
	for (int i = 0; i < meshData.size(); i++)
	{
		meshData[i].DrawMesh();
	}

	return true;
}

bool ModuleSceneIntro::PostUpdate(float dt)
{		
	return true;
}

// Unload assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");


	return true;
}