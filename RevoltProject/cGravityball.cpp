#include "stdafx.h"
#include "cGravityball.h"
#include "cImpact.h"

cGravityball::cGravityball()
{
}


cGravityball::~cGravityball()
{
}

void cGravityball::Setup()
{
}

void cGravityball::Update()
{
	for (int i = 0;i < m_vecImpact.size();++i)
	{
		m_vecImpact[i]->Update();
	}
}

void cGravityball::Render()
{
	for (int i = 0;i < m_vecImpact.size();++i)
	{
		m_vecImpact[i]->Render();
	}
}

void cGravityball::MoveActorOnPath(NxActor * actor, int index)
{
	m_vecPhysX[index]->pPhysX->m_pActor->getGlobalPose().t;

	actor->setGlobalPosition(m_vecPhysX[index]->pPhysX->m_pActor->getGlobalPose().t);

	for (int i = 0;i < m_vecImpact.size();++i)
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
