#pragma once
#include "cItem.h"

#define UPDATETIME 200

class GravityBallImpact;
class cPlasmaImpact;

class cGravityball : public cItem
{
private:
	std::vector<GravityBallImpact*> m_vecImpact;			// 임팩트를 관리하는 클래스
	cPlasmaImpact* m_pPlasma;
	int m_impactIndex;								// 임팩트 벡터 인덱스
	bool m_isSleep;
public:
	cGravityball();
	virtual ~cGravityball();

	virtual void Setup();
	virtual void Update();
	virtual void Render();
	virtual void Create(D3DXVECTOR3 angle, D3DXVECTOR3 pos);
	void MoveActorOnPath();
};

