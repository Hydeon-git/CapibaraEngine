#pragma once

#include "Application.h"
#include "Module.h"
#include "Globals.h"

class ModuleTextureLoader : public Module
{
public:
	ModuleTextureLoader(Application* app, bool enabled = true);
	~ModuleTextureLoader();

	void LoadTexture(const char* texturePath);
	bool CleanUp() override;
};
