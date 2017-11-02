#pragma once
#include "cItem.h"

class cGravityball : public cItem
{
private:
	std::vector<cImpact*> m_vecImpact;			// 임팩트를 관리하는 클래스
	std::vector<ST_PHYSX*>	m_vecPhysX;		// 아이템 물리엔진 벡터
	int m_impactIndex;								// 임팩트 벡터 인덱스
public:
	cGravityball();
	virtual ~cGravityball();

	virtual void Setup();
	virtual void Update();
	virtual void Render();
	virtual void Create(D3DXVECTOR3 angle, D3DXVECTOR3 pos);
	void MoveActorOnPath(NxActor* actor, int index);
};

