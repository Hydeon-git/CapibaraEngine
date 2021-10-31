#pragma once

#include "Application.h"
#include "Module.h"
#include "Globals.h"

class ModuleTextureLoader : public Module
{
public:
	ModuleTextureLoader(Application* app, bool enabled = true);
	~ModuleTextureLoader();
		
	bool CleanUp() override;	
};
