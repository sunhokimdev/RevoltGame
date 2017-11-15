#pragma once

#define UPDATETIME 300

class cMybombImapct;
class PSystem;

#include "cItem.h"


class cMyBomb : public cItem
{
private:
	cMybombImapct* m_pImpact;	// 임팩트 적용
	bool m_isSleep;		// 충돌을 끌지 체크

	PSystem* m_BombTime;
	D3DXVECTOR3 m_BombPos;		// 폭탄 자신의 포지션

	float m_fTimer;
public:
	cMyBomb();
	virtual ~cMyBomb();

	virtual void Setup();
	virtual void Update();
	virtual void Render();
	virtual void Create(D3DXVECTOR3 angle, D3DXVECTOR3 pos);
	virtual void Destroy();

	void MoveActorOnPath();
};

