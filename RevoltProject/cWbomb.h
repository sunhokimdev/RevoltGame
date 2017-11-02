#pragma once

#define WATERIMPACT 200

#include "cItem.h"

class cWaterBombImpact;

class cWbomb : public cItem
{
private:
	ST_PHYSX* m_pPhysX;
	cWaterBombImpact* m_pImapt;
public:
	cWbomb();
	virtual ~cWbomb();

	virtual void Setup();
	virtual void Update();
	virtual void Render();
	virtual void Create(D3DXVECTOR3 angle, D3DXVECTOR3 pos);
};

