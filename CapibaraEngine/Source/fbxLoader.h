#pragma once

//
#include "Globals.h"

// Assimp Includes + .lib
#include "cimport.h"
#include "scene.h"
#include "postprocess.h"
#pragma comment (lib, "assimp-vc142-mt.lib")

typedef unsigned int uint;

class fbxLoader
{
public:
	fbxLoader(bool enabled = true);
	~fbxLoader();		
	
	bool CleanUp();

private:
	struct vertexData
	{
		uint id_index = 0; // Index in VRAM
		uint num_index = 0;
		uint* index = nullptr;

		uint id_vertex = 0; // Unique vertex in VRAM
		uint num_vertex = 0;
		float* vertex = nullptr;
	};

public:
	void LoadFile(char filePath[]);
};
