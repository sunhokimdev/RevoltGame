#include "stdafx.h"
#include "cGravityball.h"
#include "cImpact.h"

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

	for (int i = 0; i < m_vecImpact.size(); i++)
	{
		m_vecImpact[i] = new cImpact;
		m_vecImpact[i]->Setup();
	}
}

void cGravityball::Update()
{
	for (int i = 0; i < m_vecImpact.size(); ++i)
	{
		m_vecImpact[i]->Update();
	}

	for (int i = 0; i < m_vecPhysX.size(); ++i)
	{
		MoveActorOnPath(m_vecPhysX[i]->pTrigger->m_pActor, i);
	}
}

void cGravityball::Render()
{
	for (int i = 0; i < m_vecImpact.size(); ++i)
	{
		m_vecImpact[i]->Render();
	}

	cItem::Render();
}

void cGravityball::Create()
{
	ST_PHYSX* pPhysX = new ST_PHYSX;

	USERDATA* user1 = new USERDATA;
	user1->USER_TAG = ePhysXTag::E_PHYSX_TAG_GRIVATEBALL;

	pPhysX->pos = NxVec3(5, 0, 3);

	pPhysX->pPhysX = new cPhysX;
	pPhysX->pTrigger = new cPhysX;

	pPhysX->pPhysX->m_pActor = MgrPhysX->CreateActor(NX_SHAPE_SPHERE, pPhysX->pos, NULL, NxVec3(1.0f, 0.0f, 0.0f), E_PHYSX_MATERIAL_NONE, user1);
	pPhysX->pTrigger->m_pActor = MgrPhysX->CreateActor(NX_SHAPE_SPHERE, pPhysX->pos, NULL, NxVec3(3.0f, 0.0f, 0.0f), E_PHYSX_MATERIAL_NONE, user1, true);
	pPhysX->pPhysX->m_pActor->addForce(NxVec3(30000, 0, 0));

	this->SetPhysXData(pPhysX->pPhysX);

	SetActorGroup(pPhysX->pPhysX->m_pActor, 2);

	m_vecPhysX.push_back(pPhysX);
}

void cGravityball::MoveActorOnPath(NxActor * actor, int index)
{
	m_vecPhysX[index]->pPhysX->m_pActor->getGlobalPose().t;

	actor->setGlobalPosition(m_vecPhysX[index]->pPhysX->m_pActor->getGlobalPose().t);

	for (int i = 0; i < m_vecImpact.size(); ++i)
	{
		if (m_vecImpact[i]->GetIsUse() == false)
		{
			m_vecImpact[m_impactIndex]->SetIsUse(true);
			m_vecImpact[m_impactIndex]->SetAlpha(255);
			m_vecImpact[m_impactIndex]->SetDelta(20);

			D3DXVECTOR3 vec;
			vec.x = m_vecPhysX[index]->pPhysX->m_pActor->getGlobalPose().t.x;
			vec.y = m_vecPhysX[index]->pPhysX->m_pActor->getGlobalPose().t.y;
			vec.z = m_vecPhysX[index]->pPhysX->m_pActor->getGlobalPose().t.z;
			m_vecImpact[m_impactIndex]->SetPosition(vec);
			m_impactIndex++;

			if (m_impactIndex == 100)
				m_impactIndex = 0;
			break;
		}
	}
}
