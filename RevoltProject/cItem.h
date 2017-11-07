#pragma once

#include "Object.h"
class cCar;

class cItem : public Object
{

protected:
	eITEM_LIST m_eTag;

	int m_id;				// 아이템 아이디
	int m_fTime;			// 아이템 시간
	USERDATA*	m_pUser;	// 유저 데이터
	ST_PHYSX*	m_pPhysX;	// 물리엔진 적용
public:
	cItem();
	virtual ~cItem();

	virtual void Setup();
	virtual void Update();
	virtual void Render();
	virtual void Create(D3DXVECTOR3 angle, D3DXVECTOR3 pos);

	SYNTHESIZE(bool, m_isUse, IsUse);		// 사용 가능한 아이템인지 확인
	SYNTHESIZE(bool, m_isInit, IsInit);	// 초기화 해준 것인지 확인
	SYNTHESIZE(cCar*, m_pCar, Car);
	void SetActorGroup(NxActor * actor, NxCollisionGroup group);
	void SetItemTag(eITEM_LIST tag) { m_eTag = tag; }
};

