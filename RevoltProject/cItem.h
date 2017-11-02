#pragma once

#include "Object.h"

class cItem : public Object
{
protected:
	int m_id;					// 아이템 아이디
	float m_fTime;			// 아이템 시간
public:
	cItem();
	virtual ~cItem();

	virtual void Setup();
	virtual void Update();
	virtual void Render();
	virtual void Create(D3DXVECTOR3 angle, D3DXVECTOR3 pos);

	SYNTHESIZE(bool, m_isUse, Use);		// 사용 가능한 아이템인지 확인
	void SetActorGroup(NxActor * actor, NxCollisionGroup group);
};

