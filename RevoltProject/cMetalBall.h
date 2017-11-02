#pragma once

#include "cItem.h"

class cMetalBall : public cItem
{
private:
	std::vector<ST_PHYSX*>	m_vecPhysX;

public:
	cMetalBall();
	~cMetalBall();

	virtual void Setup();
	virtual void Update();
	virtual void Render();
	virtual void Create(D3DXVECTOR3 angle, D3DXVECTOR3 pos);
};

