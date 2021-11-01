#include "InspectorPanel.h"

InspectorPanel::InspectorPanel(bool enabled) : Panels(enabled)
{
	inspector = true;
}

InspectorPanel::~InspectorPanel() {  }

bool InspectorPanel::Update(float dt)
{
	if (ImGui::Begin("Inspector", &inspector))
	{
		if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
		{
		}
		if (ImGui::CollapsingHeader("Mesh", ImGuiTreeNodeFlags_DefaultOpen))
		{
		}
		if (ImGui::CollapsingHeader("Texture", ImGuiTreeNodeFlags_DefaultOpen))
		{
		}
	}
	ImGui::End();


	return true;
}
