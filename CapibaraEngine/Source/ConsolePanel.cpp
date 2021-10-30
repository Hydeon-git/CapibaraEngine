#include "ConsolePanel.h"

ConsolePanel::ConsolePanel(bool enabled) : Panels(enabled) {}
ConsolePanel::~ConsolePanel() {}


bool ConsolePanel::Update(float dt)
{
	if (ImGui::Begin("Console", &console))
	{
		ImGui::TextUnformatted(textBuffer.begin());
	}

	if (scrollBar)
	{
		ImGui::SetScrollHereX(1.0f);
		ImGui::SetScrollHereY(1.0f);
	}		
	scrollBar = false;
	ImGui::End();
	return true;
}

void ConsolePanel::AddLog(const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	textBuffer.appendfv(fmt, args);
	textBuffer.appendfv("\n", args);
	va_end(args);

	scrollBar = true;
}