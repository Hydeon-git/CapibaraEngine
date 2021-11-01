#pragma once
#include <vector>

#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "Light.h"
#include "SDL.h"

#define MAX_LIGHTS 8

typedef unsigned int GLuint;

class ModuleRenderer3D : public Module
{
public:
	ModuleRenderer3D(bool start_enabled = true);
	~ModuleRenderer3D();

	bool Init() override;
	bool PreUpdate(float dt) override;
	bool Draw() override;
	bool PostUpdate(float dt) override;
	bool CleanUp() override;

	void OnResize(int width, int height);	
public:
	std::vector<uint> indices;
	std::vector<float> interleavedVertices;
	int interleavedStride;

	Light lights[MAX_LIGHTS];
	SDL_GLContext context;
	mat3x3 NormalMatrix;
	mat4x4 ModelMatrix, ViewMatrix, ProjectionMatrix;
};