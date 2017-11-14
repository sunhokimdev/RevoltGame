#include "stdafx.h"
#include "cMyBomb.h"
#include "cMybombImapct.h"
#include "cCar.h"
#include "PFirework.h"

cMyBomb::cMyBomb()
	: m_pImpact(NULL)
	, m_BombTime(NULL)
	, m_isSleep(true)
	, m_fTimer(0.0f)
{
	cItem::cItem();
}


cMyBomb::~cMyBomb()
{
}

void cMyBomb::Setup()
{
	cItem::Setup();

	m_pImpact = new cMybombImapct;
	m_pImpact->Setup();
	m_pImpact->SetIsUse(false);

	m_BombTime = new PFirework(2, 0.2f);
	m_BombTime->Init(g_pD3DDevice, "Objects/firework/particle_flare2.bmp");

	m_pUser->USER_TAG = E_PHYSX_TAG_MYBOMB;
}

void cMyBomb::Update()
{
	cItem::Update();

	MoveActorOnPath();

	m_BombPos.x = m_pCar->GetPhysXData()->GetPositionToNxVec3().x + 0.2f;
	m_BombPos.y = m_BombPos.y + m_fTimer;
	m_BombPos.z = m_pCar->GetPhysXData()->GetPositionToNxVec3().z + 0.2f;

	if (!m_isUse && !m_pImpact->GetIsUse())
	{
		m_pPhysX->pos.y = -50.0f;
		m_pPhysX->pPhysX->m_pActor->setGlobalPosition(m_pPhysX->pos);
		SetIsEnd(true);
	}

	m_fTimer -= 0.0015f;
	if (m_fTimer < -0.35f)
		m_fTimer = -0.35f;

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

	m_BombTime->SetPosition(&m_BombPos);
	m_BombTime->Update(0.1f);
	m_BombTime->Reset();

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
	{
		m_pImpact->Render();
	}
	if(m_isUse)
	{
		m_BombTime->Render();
	}

	cItem::Render();
}

void cMyBomb::Create(D3DXVECTOR3 angle, D3DXVECTOR3 pos)
{
	m_pPhysX->pos.x = pos.x;
	m_pPhysX->pos.y = pos.y + 1;
	m_pPhysX->pos.z = pos.z;

	if (m_isInit)
	{
		m_pPhysX->pPhysX->m_pActor = MgrPhysX->CreateActor(NX_SHAPE_SPHERE, m_pPhysX->pos, NULL, NxVec3(1.5f, 0.0f, 0.0f), E_PHYSX_MATERIAL_CAR, m_pUser);
		m_pPhysX->pPhysX->m_pActor->putToSleep();
		m_pPhysX->pPhysX->m_pActor->raiseActorFlag(NX_AF_DISABLE_COLLISION);
		SetActorGroup(m_pPhysX->pPhysX->m_pActor, E_PHYSX_TAG_MYBOMB);
		this->SetPhysXData(m_pPhysX->pPhysX);
		m_fTimer = 0.0f;
		m_isInit = false;
		m_pCar->GetPhysXData()->m_pUserData->isMyBomb = true;
	}
}

void cMyBomb::Destroy()
{
	SAFE_DELETE(m_pImpact);
	SAFE_DELETE(m_BombTime);

	cItem::Destroy();
}

void cMyBomb::MoveActorOnPath()
{
	m_pPhysX->pPhysX->m_pActor->setGlobalPosition(m_pCar->GetPhysXData()->GetPositionToNxVec3());
	m_BombPos.y = m_pCar->GetPhysXData()->GetPositionToNxVec3().y + 0.8f;
}
