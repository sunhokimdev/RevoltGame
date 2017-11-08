#pragma once
#include "cItem.h"

#define FIREWORKEFFECT 80

class PSystem;

class cFirework : public cItem
{
private:
	ST_PHYSX* m_pPhysX;
	bool m_isSleep;

	PSystem* m_pEffect;
	PSystem* m_pTail;

	D3DXVECTOR3 fwPos;
public:
	cFirework();
	virtual ~cFirework();

	virtual void Setup();
	virtual void Update();
	virtual void Render();
	virtual void Create(D3DXVECTOR3 angle, D3DXVECTOR3 pos);
};

