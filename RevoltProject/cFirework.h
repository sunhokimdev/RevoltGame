#pragma once

#include "cItem.h"

class cFirework : public cItem
{
public:
	cFirework();
	virtual ~cFirework();

	virtual void Setup();
	virtual void Update();
	virtual void Render();
};

