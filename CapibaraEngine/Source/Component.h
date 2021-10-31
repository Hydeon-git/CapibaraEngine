#pragma once

class Component
{
private :
	bool enabled;

public:

	Component() {}
	virtual ~Component() {}

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