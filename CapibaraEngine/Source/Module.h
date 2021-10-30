#pragma once

class Application;

class Module
{
private :
	bool enabled;

public:
	//Application* App;

	Module(bool start_enabled = true) {}

	virtual ~Module() {}

	virtual bool Init() 
	{
		return true; 
	}

	virtual bool Start()
	{
		return true;
	}

	virtual bool PreUpdate(float dt)
	{
		return true;
	}

	virtual bool Update(float dt)
	{
		return true;
	}
	
	virtual bool Draw()
	{
		return true;
	}

	virtual bool PostUpdate(float dt)
	{
		return true;
	}

	virtual bool CleanUp() 
	{ 
		return true; 
	}
};