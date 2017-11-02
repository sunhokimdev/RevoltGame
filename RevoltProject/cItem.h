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

	void SetActorGroup(NxActor * actor, NxCollisionGroup group);
};

