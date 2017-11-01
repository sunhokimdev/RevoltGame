#pragma once
#include "cItem.h"

class Firework : public cItem
{
public:
	Firework();
	~Firework();

	virtual void Setup();
	virtual void Update();
	virtual void Render();
};

