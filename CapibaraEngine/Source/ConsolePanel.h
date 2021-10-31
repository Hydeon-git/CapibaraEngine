#pragma once

#include "Panels.h"

class ConsolePanel : public Panels
{
public:
	ConsolePanel(bool enabled = true);
	~ConsolePanel();

	bool Update(float dt) override;
	void ClearConsole();
	void AddLog(const char* fmt, ...);
private:
	ImGuiTextBuffer textBuffer;

	bool console, scrollBar;
};
