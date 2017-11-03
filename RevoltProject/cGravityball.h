#pragma once
#include "cItem.h"

class GravityBallImpact;

class cGravityball : public cItem
{
private:
	std::vector<GravityBallImpact*> m_vecImpact;			// 임팩트를 관리하는 클래스
	int m_impactIndex;								// 임팩트 벡터 인덱스
public:
	cGravityball();
	virtual ~cGravityball();

	virtual void Setup();
	virtual void Update();
	virtual void Render();
	virtual void Create(D3DXVECTOR3 angle, D3DXVECTOR3 pos);
	void MoveActorOnPath();
};

