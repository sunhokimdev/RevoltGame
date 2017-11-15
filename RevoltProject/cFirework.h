#pragma once
#include "cItem.h"

#define FIREWORKEFFECT 80

class cCar;
class PSystem;

class cFirework : public cItem
{
private:
	ST_PHYSX* m_pPhysX;
	bool m_isSleep;
	
	
	PSystem* m_pEffect;		// ÆøÁ× ÅÍÁö´Â ÆÄÆ¼Å¬
	PSystem* m_pTail;		// ÆøÁ× ²¿¸® ÆÄÆ¼Å¬

	D3DXVECTOR3 fwPos;		// ÆøÁ× ÀÚ½ÅÀÇ Æ÷Áö¼Ç
	D3DXVECTOR3 dir;		// ÆøÁ×ÀÌ ³¯¾Æ°¡´Â ¹æÇâ
	cCar* m_pCar;

public:
	cFirework();
	virtual ~cFirework();

	virtual void Setup();
	virtual void Update();
	virtual void Render();
	virtual void Create(D3DXVECTOR3 angle, D3DXVECTOR3 pos);
	virtual void Destroy();

	void LinkCar(cCar* LinkCar) { m_pCar = LinkCar; }
	SYNTHESIZE(D3DXVECTOR3, m_vTarget, Target);
	SYNTHESIZE(bool, m_isTarget, IsTarget);
};

