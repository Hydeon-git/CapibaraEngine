#pragma once

#include "Globals.h"

// Assimp Includes + .lib
#include "cimport.h"
#include "scene.h"
#include "postprocess.h"


// Opengl + Glew
#include "glew.h";
#include "SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>


class fbxLoader
{
public:
	fbxLoader(bool enabled = true);
	~fbxLoader();		
	
	bool CleanUp();

private:

public:
	
	void LoadFile(const char* filePath, struct mesh& meshData);	
};
