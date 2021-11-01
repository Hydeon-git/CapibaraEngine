#include "HierarchyPanel.h"

HierarchyPanel::HierarchyPanel(bool enabled) : Panels(enabled)
{
	hierarchy = true;
}

HierarchyPanel::~HierarchyPanel() {  }

bool HierarchyPanel::Update(float dt)
{
	if (ImGui::Begin("Hierarchy", &hierarchy))
	{
		if (ImGui::CollapsingHeader("Game Objects", ImGuiTreeNodeFlags_DefaultOpen))
		{

		}
	}
	ImGui::End();


	return true;
}
