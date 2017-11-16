#pragma once

#include "cItem.h"

#define UPDATETIME 100

class cFakeImpact;

class cFakeBomb : public cItem
{
private:
	cFakeImpact* m_pImpact;
	float m_bombTime;
	float m_bombAngle;
public:
	cFakeBomb();
	virtual ~cFakeBomb();

	virtual void Setup();
	virtual void Update();
	virtual void Render();
	virtual void Create(D3DXVECTOR3 angle, D3DXVECTOR3 pos);
	virtual void Destroy();
};

