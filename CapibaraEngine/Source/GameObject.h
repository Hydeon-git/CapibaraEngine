#pragma once

#include "Component.h"

#include <vector>

using namespace std;

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	void Update(float dt);
	Component* CreateComponent(ComponentType type);

private:
	vector<Component*> components;
	GameObject* parent;
	vector<Component*> children;
};