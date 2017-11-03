#include "stdafx.h"
#include "cGravityball.h"
#include "cImpact.h"
#include "GravityBallImpact.h"

cGravityball::cGravityball()
	: m_impactIndex(0)
{
}


cGravityball::~cGravityball()
{
}

void cGravityball::Setup()
{
	cItem::Setup();

	m_vecImpact.resize(100);

	for (int i = 0;i < m_vecImpact.size();i++)
	{
		m_vecImpact[i] = new GravityBallImpact;
		m_vecImpact[i]->SetIsUse(true);
		m_vecImpact[i]->Setup();
		m_vecImpact[i]->SetAlpha(255);
		m_vecImpact[i]->SetDelta(20);
	}

	m_pUser->USER_TAG = E_PHYSX_TAG_GRIVATEBALL;
}

void cGravityball::Update()
{
	if (m_isUse)
	{
		m_vecImpact[m_impactIndex]->SetPosition(
			D3DXVECTOR3(m_pPhysX->pPhysX->m_pActor->getGlobalPose().t.x,
				m_pPhysX->pPhysX->m_pActor->getGlobalPose().t.y,
				m_pPhysX->pPhysX->m_pActor->getGlobalPose().t.z));

		m_impactIndex++;

		for (int i = 0; i < m_impactIndex; ++i)
		{
			m_vecImpact[i]->Update();
		}

		if (m_vecImpact.size() == m_impactIndex)
			m_impactIndex = 0;

		MoveActorOnPath();
	}

	cItem::Update();
}

void cGravityball::Render()
{
	if (m_isUse)
	{
		for (int i = 0;i < m_impactIndex;++i)
		{
			m_vecImpact[i]->Render();
		}
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

	if (m_isInit)
	{
		m_pPhysX->pPhysX->m_pActor = MgrPhysX->CreateActor(NX_SHAPE_SPHERE, m_pPhysX->pos, NULL, NxVec3(1.0f, 0.0f, 0.0f), E_PHYSX_MATERIAL_CAR, m_pUser);
		m_pPhysX->pTrigger->m_pActor = MgrPhysX->CreateActor(NX_SHAPE_SPHERE, m_pPhysX->pos, NULL, NxVec3(3.0f, 0.0f, 0.0f), E_PHYSX_MATERIAL_CAR, m_pUser, true);
		SetActorGroup(m_pPhysX->pPhysX->m_pActor, 2);
		this->SetPhysXData(m_pPhysX->pPhysX);
		m_isInit = false;
	}

	else
		m_pPhysX->pPhysX->m_pActor->setGlobalPosition(m_pPhysX->pos);

	m_pPhysX->pPhysX->m_pActor->addForce(force);
}

void cGravityball::MoveActorOnPath()
{
	m_pPhysX->pPhysX->m_pActor->getGlobalPose().t;

	m_pPhysX->pTrigger->m_pActor->setGlobalPosition(m_pPhysX->pPhysX->m_pActor->getGlobalPose().t);

	for (int i = 0;i < m_vecImpact.size();++i)
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

			if (m_impactIndex == 100)
				m_impactIndex = 0;
			break;
		}
	}
}
