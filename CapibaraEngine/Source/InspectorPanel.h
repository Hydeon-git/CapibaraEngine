#pragma once

#include "Panels.h"

class InspectorPanel : public Panels
{
public:
	InspectorPanel(bool enabled = true);
	~InspectorPanel();

	bool Update(float dt) override;

private:
	bool inspector;
};
#pragma once
