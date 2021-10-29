#pragma once

#include "Application.h"
#include "Module.h"
#include "Globals.h"

#include <vector>

// Assimp Includes + .lib
#include "cimport.h"
#include "scene.h"
#include "postprocess.h"

#include "MeshData.h"

class ModuleFbxLoader : public Module
{
public:
	ModuleFbxLoader(Application* app, bool enabled = true);
	~ModuleFbxLoader();

	void LoadFile(const char* filePath, std::vector<MeshData>& meshDataVec);
	bool CleanUp() override;
};
