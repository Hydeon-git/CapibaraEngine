#pragma once

#include "Application.h"
#include "Module.h"
#include "Globals.h"

#include <vector>

// Assimp Includes + .lib
#include "cimport.h"
#include "scene.h"
#include "postprocess.h"

#include "MeshComponent.h"

class ModuleFbxLoader : public Module
{
public:
	ModuleFbxLoader(bool enabled = true);
	~ModuleFbxLoader();

	void LoadFile(const char* filePath, std::vector<MeshComponent>& meshDataVec);
	bool CleanUp() override;
};
