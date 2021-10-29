#pragma once
#include "Globals.h"

class MeshData
{
public:
	// Mesh Buffers ID
	uint id_index = 0; // Index in VRAM
	uint id_vertex = 0; // Unique vertex in VRAM
	uint id_texture = 0;

	// Mesh Buffers Size
	uint num_index = 0;
	uint num_vertex = 0;

	// Mesh Buffers
	uint* index = nullptr;	
	float* vertex = nullptr;	
	float* textures = nullptr;	

	// Number of meshes that the model has
	uint num_meshes = 0;

	// Mesh Functions
	void CreateBuffers();
	bool DrawMesh();
};