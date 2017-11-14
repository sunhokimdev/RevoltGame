#pragma once
#include "cItem.h"

#define FIREWORKEFFECT 80

class PSystem;

class cFirework : public cItem
{
private:
	ST_PHYSX* m_pPhysX;
	bool m_isSleep;
	bool m_isTarget;		// 타깃이 있는지
	
	PSystem* m_pEffect;		// 폭죽 터지는 파티클
	PSystem* m_pTail;		// 폭죽 꼬리 파티클

	D3DXVECTOR3 fwPos;		// 폭죽 자신의 포지션
	D3DXVECTOR3 dir;		// 폭죽이 날아가는 방향
public:
	cFirework();
	virtual ~cFirework();

	virtual void Setup();
	virtual void Update();
	virtual void Render();
	virtual void Create(D3DXVECTOR3 angle, D3DXVECTOR3 pos);
	virtual void Destroy();

};

