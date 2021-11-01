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

using namespace std;

class ModuleFbxLoader : public Module
{
public:
	ModuleFbxLoader(bool enabled = true);
	~ModuleFbxLoader();

	void LoadFile(const char* filePath, vector<MeshComponent>& meshDataVec);
	bool CleanUp() override;
};
