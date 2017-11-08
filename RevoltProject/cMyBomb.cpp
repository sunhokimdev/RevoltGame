#include "stdafx.h"
#include "cMyBomb.h"
#include "cMybombImapct.h"
#include "cCar.h"

cMyBomb::cMyBomb()
	: m_pImpact(NULL)
	, m_isSleep(true)
{
	cItem::cItem();
}


cMyBomb::~cMyBomb()
{
	SAFE_DELETE(m_pImpact);
}

void cMyBomb::Setup()
{
	cItem::Setup();

	m_pImpact = new cMybombImapct;
	m_pImpact->Setup();

	m_pUser->USER_TAG = E_PHYSX_TAG_MYBOMB;
}

void cMyBomb::Update()
{
	cItem::Update();

	MoveActorOnPath();

	if (m_pCar->GetPhysXData()->m_pUserData->isMyBomb && m_isUse)
	{
		if (m_fTime > UPDATETIME)
		{
			m_pPhysX->pPhysX->m_pActor->wakeUp();
			m_pPhysX->pPhysX->m_pActor->clearActorFlag(NX_AF_DISABLE_COLLISION);

			NxVec3 n = m_pPhysX->pPhysX->m_pActor->getGlobalPose().t;
			m_pImpact->SetIsUse(true);
			m_pImpact->SetPosition(m_pCar->GetPhysXData()->GetPositionToD3DXVec3());
			m_isUse = false;
			m_isSleep = true;
			m_fTime = 0;
			m_pCar->GetPhysXData()->m_pUserData->isMyBomb = false;
		}
	}

	if (m_pImpact->GetIsUse() == false)
	{
		m_pPhysX->pPhysX->m_pActor->putToSleep();
		m_pPhysX->pPhysX->m_pActor->raiseActorFlag(NX_AF_DISABLE_COLLISION);
	}

	if (!m_isUse && m_pImpact->GetIsUse())
		m_pImpact->Update();
}

void cMyBomb::Render()
{
	if (!m_isUse && m_pImpact->GetIsUse())
		m_pImpact->Render();

	cItem::Render();
}

void cMyBomb::Create(D3DXVECTOR3 angle, D3DXVECTOR3 pos)
{
	m_pPhysX->pos.x = pos.x;
	m_pPhysX->pos.y = pos.y + 1;
	m_pPhysX->pos.z = pos.z;

	if (m_isInit)
	{
		m_pPhysX->pPhysX->m_pActor = MgrPhysX->CreateActor(NX_SHAPE_SPHERE, m_pPhysX->pos, NULL, NxVec3(3.0f, 0.0f, 0.0f), E_PHYSX_MATERIAL_CAR, m_pUser);
		m_pPhysX->pPhysX->m_pActor->putToSleep();
		m_pPhysX->pPhysX->m_pActor->raiseActorFlag(NX_AF_DISABLE_COLLISION);
		SetActorGroup(m_pPhysX->pPhysX->m_pActor, 2);
		this->SetPhysXData(m_pPhysX->pPhysX);
		m_isInit = false;
		m_pCar->GetPhysXData()->m_pUserData->isMyBomb = true;
	}
}

void cMyBomb::MoveActorOnPath()
{
	m_pPhysX->pPhysX->m_pActor->setGlobalPosition(m_pCar->GetPhysXData()->GetPositionToNxVec3());
}
