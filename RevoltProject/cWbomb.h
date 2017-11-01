#pragma once

#include "cItem.h"

class cWbomb : public cItem
{
public:
	cWbomb();
	virtual ~cWbomb();

	virtual void Setup();
	virtual void Update();
	virtual void Render();
};

