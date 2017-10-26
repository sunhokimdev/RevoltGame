#pragma once
class RevoltUIObject
{
private:
public:
	RevoltUIObject();
	virtual ~RevoltUIObject();

	virtual void Setup();
	virtual void Update();
	virtual void Render();
};

