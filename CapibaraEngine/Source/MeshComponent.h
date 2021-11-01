#pragma once
#include "Globals.h"
#include "Component.h"

class MeshComponent : public Component
{
public:
	// Mesh Buffers ID
	uint idIndex = 0; // Index in VRAM
	uint idVertex = 0; // Unique vertex in VRAM
	uint idTexture = 0; // Unique vertex in VRAM

	// Mesh Buffers Size
	uint numIndex = 0;
	uint numVertex = 0;
	uint numTextures = 0;

	// Mesh Buffers
	uint* index = nullptr;	
	float* vertex = nullptr;	
	float* textures = nullptr;	

	// Number of meshes that the model has
	uint numMeshes = 0;

	// Mesh Functions
	void CreateMeshBuffers();
	bool DrawMesh();
};