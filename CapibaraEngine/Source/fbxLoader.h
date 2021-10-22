#pragma once

#include "Application.h"
#include "Globals.h"

#include <vector>

// Assimp Includes + .lib
#include "cimport.h"
#include "scene.h"
#include "postprocess.h"

// Opengl + Glew
#include "glew.h";
#include "SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#include "MeshData.h"

class fbxLoader
{
public:
	fbxLoader(bool enabled = true);
	~fbxLoader();

	void LoadFile(const char* filePath, std::vector<MeshData>& meshDataVec);
	bool CleanUp();	
};
