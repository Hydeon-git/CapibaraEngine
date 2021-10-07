#include "ConsolePanel.h"

ConsolePanel::ConsolePanel(bool enabled) : Panels(enabled) {}
ConsolePanel::~ConsolePanel() {}


bool ConsolePanel::PostUpdate(float dt)
{
	ImGui::Begin("Console", &console);
	if (scrollBar)
	{
		ImGui::SetScrollHereX(1.0f);
		ImGui::SetScrollHereY(1.0f);
	}		
	scrollBar = false;
	ImGui::End();
	return true;
}
