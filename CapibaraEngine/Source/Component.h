#pragma once
class GameObject;

enum ComponentType
{
	TRANSFORM,
	MESH,
	MATERIAL,
	LIGHT,
};

class Component
{
private :
	bool enabled;
	GameObject* owner;

public:

	virtual bool Enable() 
	{
		return true; 
	}

	virtual bool Update(float dt)
	{
		return true;
	}

	virtual bool Disable()
	{
		return true;
	}
};