#pragma once

#include "imgui.h"

class Panels
{
private:
	bool enabled;

public:
	// Enable && Check if is enabled	
	Panels(bool _enabled): enabled(_enabled) {}
	bool* IsEnabled() 
	{
		return &enabled;
	}

	// Virtual Functions
	virtual ~Panels() {}
	virtual bool Update(float dt)
	{
		return true;
	}
	virtual bool CleanUp()
	{
		return true;
	}
};