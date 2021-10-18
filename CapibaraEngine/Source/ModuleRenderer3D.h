#pragma once
#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "Light.h"

#include "fbxLoader.h"

#define MAX_LIGHTS 8

typedef unsigned int GLuint;

struct mesh
{
	void CreateMeshBuffers();
	void DrawMesh();

	uint id_index = 0; // Index in VRAM
	uint num_index = 0;
	uint* index = nullptr;

	uint id_vertex = 0; // Unique vertex in VRAM
	uint num_vertex = 0;
	float* vertex = nullptr;
};


class ModuleRenderer3D : public Module
{
public:
	ModuleRenderer3D(Application* app, bool start_enabled = true);
	~ModuleRenderer3D();

	bool Init() override;
	bool PreUpdate(float dt) override;
	bool Draw() override;
	bool PostUpdate(float dt) override;
	bool CleanUp() override;

	void OnResize(int width, int height);
	void DrawDirectCube();
	void DrawElementsCube();
	
public:
	std::vector<uint> indices;
	std::vector<float> interleavedVertices;
	int interleavedStride;

	Light lights[MAX_LIGHTS];
	SDL_GLContext context;
	mat3x3 NormalMatrix;
	mat4x4 ModelMatrix, ViewMatrix, ProjectionMatrix;

private:
	fbxLoader meshLoader;
	mesh meshData;
};