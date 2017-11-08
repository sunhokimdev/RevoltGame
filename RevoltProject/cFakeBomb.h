#pragma once

#include "cItem.h"

class cFakeBomb : public cItem
{
public:
	cFakeBomb();
	virtual ~cFakeBomb();

	virtual void Setup();
	virtual void Update();
	virtual void Render();
	virtual void Create(D3DXVECTOR3 angle, D3DXVECTOR3 pos);
};

