#pragma once

#include "Application.h"
#include "Module.h"
#include "Globals.h"

#include <vector>

#include "MeshData.h"

class ModuleFbxLoader : public Module
{
public:
	ModuleFbxLoader(Application* app, bool enabled = true);
	~ModuleFbxLoader();

	void LoadFile(const char* filePath, std::vector<MeshData>& meshDataVec);
	void LoadTexture(const char* filePath, std::vector<MeshData>& meshDataVec);
	bool CleanUp() override;
};
