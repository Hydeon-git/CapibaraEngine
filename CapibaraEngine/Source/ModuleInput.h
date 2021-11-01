#pragma once
#include "Module.h"
#include "Globals.h"

#define MAX_MOUSE_BUTTONS 5

enum KEY_STATE
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

class ModuleInput : public Module
{
public:
	
	ModuleInput(bool start_enabled = true);
	~ModuleInput();

	bool Init() override;
	bool PreUpdate(float dt) override;
	bool CleanUp() override;

	KEY_STATE GetKey(int id) const
	{
		return keyboard[id];
	}

	KEY_STATE GetMouseButton(int id) const
	{
		return mouseButtons[id];
	}

	int GetMouseX() const
	{
		return mouseX;
	}

	int GetMouseY() const
	{
		return mouseY;
	}

	int GetMouseZ() const
	{
		return mouseZ;
	}

	int GetMouseXMotion() const
	{
		return mouseXMotion;
	}

	int GetMouseYMotion() const
	{
		return mouseYMotion;
	}

	void GetMousePosition(int& x, int& y) const
	{
		x = mouseX;
		y = mouseY;
	}
	void GetMouseMotion(int& x, int& y) const
	{
		x = mouseXMotion;
		y = mouseYMotion;
	}

private:
	KEY_STATE* keyboard;
	KEY_STATE mouseButtons[MAX_MOUSE_BUTTONS];
	int mouseX;
	int mouseY;
	int mouseZ;
	int mouseXMotion;
	int mouseYMotion;

	char* droppedFileDir;
};