#pragma once

#include "Panels.h"

class ConsolePanel : public Panels
{
public:
	ConsolePanel(bool enabled = true);
	~ConsolePanel();

	bool Update(float dt);

private:
	bool console, scrollBar;
};
