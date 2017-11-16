#include "stdafx.h"
#include "cGravityball.h"
#include "cImpact.h"
#include "GravityBallImpact.h"
#include "cPlasmaImpact.h"
#include "cCar.h"

cGravityball::cGravityball()
	: m_impactIndex(0)
	, m_pPlasma(NULL)
	, m_isSleep(false)
{
}

cGravityball::~cGravityball()
{
}

void cGravityball::Setup()
{
	cItem::Setup();

	m_vecImpact.resize(100);

	for (int i = 0; i < m_vecImpact.size(); i++)
	{
		m_vecImpact[i] = new GravityBallImpact;
		m_vecImpact[i]->Setup();
		m_vecImpact[i]->SetAlpha(255);
		m_vecImpact[i]->SetDelta(20);
	}

	m_pPlasma = new cPlasmaImpact;
	m_pPlasma->Setup();

	m_pUser->USER_TAG = E_PHYSX_TAG_GRIVATEBALL;
}

void cGravityball::Update()
{
	cItem::Update();

	if (m_isUse)
	{
		MoveActorOnPath();

		for (int i = 0; i < m_vecImpact.size(); ++i)
		{
			m_vecImpact[i]->Update();
		}

		{
			NxVec3 v = m_pPhysX->pPhysX->m_pActor->getGlobalPose().t;
			m_pPlasma->UpdateSetPosition(D3DXVECTOR3(v.x, v.y, v.z));
		}
		m_pPlasma->Update();
	}

	if (!m_isUse)
	{
		m_pPhysX->pos.y = -50.0f;
		m_pPhysX->pPhysX->m_pActor->setGlobalPosition(m_pPhysX->pos);
		m_pPhysX->pTrigger->m_pActor->setGlobalPosition(m_pPhysX->pos);
		m_pCar->GetPhysXData()->m_pUserData->isFireGravity = false;
		SetIsEnd(true);
	}

	if (m_fTime % UPDATETIME == 0)
	{
		//m_pPhysX->pTrigger->m_pActor->putToSleep();
		//m_pPhysX->pTrigger->m_pActor->raiseActorFlag(NX_AF_DISABLE_COLLISION);
		m_fTime = 0;
		m_isUse = false;
		m_pPhysX->pPhysX->m_pActor->putToSleep();
		m_pPhysX->pPhysX->m_pActor->raiseActorFlag(NX_AF_DISABLE_COLLISION);
		m_isSleep = true;
	}
}

void cGravityball::Render()
{
	if (m_isUse)
	{
		for (int i = 0;i < m_vecImpact.size();++i)
		{
			m_vecImpact[i]->Render();
		}

		m_pPlasma->Render();
	}

	cItem::Render();
}

void cGravityball::Create(D3DXVECTOR3 angle, D3DXVECTOR3 pos)
{
	m_pPhysX->pos.x = pos.x + angle.x;
	m_pPhysX->pos.y = pos.y + 1;
	m_pPhysX->pos.z = pos.z + angle.z;
	
	NxVec3 force;

	force.x = angle.x * 30000;
	force.y = 0;
	force.z = angle.z * 30000;
	
	g_pSoundManager->Play("shockfire.wav", 0.8f, pos);

	if (m_isSleep)
	{
		m_pPhysX->pPhysX->m_pActor->wakeUp();
		m_pPhysX->pPhysX->m_pActor->clearActorFlag(NX_AF_DISABLE_COLLISION);
	}
	
	if (m_isInit)
	{
		m_pPhysX->pPhysX->m_pActor = MgrPhysX->CreateActor(NX_SHAPE_SPHERE, m_pPhysX->pos, NULL, NxVec3(1.0f, 0.0f, 0.0f), E_PHYSX_MATERIAL_GRIVATEBALL, m_pUser);
		m_pPhysX->pTrigger->m_pActor = MgrPhysX->CreateActor(NX_SHAPE_SPHERE, m_pPhysX->pos, NULL, NxVec3(4.0f, 0.0f, 0.0f), E_PHYSX_MATERIAL_GRIVATEBALL, m_pUser, true);

		SetActorGroup(m_pPhysX->pPhysX->m_pActor, E_PHYSX_TAG_GRIVATEBALL);
		SetActorGroup(m_pPhysX->pTrigger->m_pActor, E_PHYSX_TAG_GRIVATEBALL);
		this->SetPhysXData(m_pPhysX->pPhysX);
		m_pCar->GetPhysXData()->m_pUserData->isFireGravity = true;
		m_isInit = false;
	}

	else
	{	
		m_pPhysX->pPhysX->m_pActor->setGlobalPosition(m_pPhysX->pos);
	}

	m_pPhysX->pPhysX->m_pActor->addForce(force);
}

void cGravityball::Destroy()
{
	for each(auto a in m_vecImpact)
		SAFE_DELETE(a);

	SAFE_DELETE(m_pPlasma);

	cItem::Destroy();
}

void cGravityball::MoveActorOnPath()
{
	m_pPhysX->pTrigger->m_pActor->setGlobalPosition(m_pPhysX->pPhysX->m_pActor->getGlobalPose().t);

	for (int i = 0; i < m_vecImpact.size(); ++i)
	{
		if (m_vecImpact[i]->GetIsUse() == false)
		{
			m_vecImpact[m_impactIndex]->SetIsUse(true);
			m_vecImpact[m_impactIndex]->SetAlpha(255);
			m_vecImpact[m_impactIndex]->SetDelta(20);

			D3DXVECTOR3 vec;
			vec.x = m_pPhysX->pPhysX->m_pActor->getGlobalPose().t.x;
			vec.y = m_pPhysX->pPhysX->m_pActor->getGlobalPose().t.y;
			vec.z = m_pPhysX->pPhysX->m_pActor->getGlobalPose().t.z;

			m_vecImpact[m_impactIndex]->SetPosition(vec);
			m_impactIndex++;

			if (m_impactIndex == m_vecImpact.size())
				m_impactIndex = 0;
			break;
		}
	}
}
