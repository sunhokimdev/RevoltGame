#pragma once

#include "cItem.h"

class cFirework : public cItem
{
private:
	ST_PHYSX* m_pPhysX;

	D3DXVECTOR3 m_pos;
	bool m_isSleep;

public:
	cFirework();
	virtual ~cFirework();

	virtual void Setup();
	virtual void Update();
	virtual void Render();
	virtual void Create(D3DXVECTOR3 angle, D3DXVECTOR3 pos);
};

