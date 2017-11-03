#pragma once
#include "cItem.h"

//===================================================================
// - written by ¡§¡æ»∆
// - æ∆¿Ã≈€ ∆¯¡◊ ø¿∫Í¡ß∆Æ
//===================================================================

class Firework : public cItem
{
public:
	Firework();
	~Firework();

	virtual void Setup();
	virtual void Update();
	virtual void Render();
};

