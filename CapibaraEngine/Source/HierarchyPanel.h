#pragma once

#include "Panels.h"

class HierarchyPanel : public Panels
{
public:
	HierarchyPanel(bool enabled = true);
	~HierarchyPanel();

	bool Update(float dt) override;

private:
	bool hierarchy;
};
#pragma once
