#include "stdafx.h"
#include "cWbomb.h"
#include "ObjectLoader.h"
#include "cWaterBombImpact.h"

cWbomb::cWbomb()
	: m_pImapt(NULL)
	, m_isSleep(false)
{
	cItem::cItem();
}

cWbomb::~cWbomb()
{
	SAFE_DELETE(m_pImapt);
}

void cWbomb::Setup()
{
	cItem::Setup();

	ObjectLoader::LoadMesh(m_pPhysX->pMesh, "Objects/wbomb", "wbomb.obj");
	
	m_pImapt = new cWaterBombImpact;
	m_pImapt->Setup();
	m_pImapt->SetIsUse(false);
	m_pUser->USER_TAG = E_PHYSX_TAG_WHATEBOMB;
}

void cWbomb::Update()
{
	cItem::Update();

	if (m_isUse)
	{

		m_pPhysX->pPhysX->m_pActor->putToSleep();
		m_pPhysX->pPhysX->m_pActor->raiseActorFlag(NX_AF_DISABLE_COLLISION);

		m_pPhysX->pTrigger->m_pActor->wakeUp();
		m_pPhysX->pTrigger->m_pActor->clearActorFlag(NX_AF_DISABLE_COLLISION);

		NxVec3 n = m_pPhysX->pPhysX->m_pActor->getGlobalPosition();

		m_pImapt->SetIsUse(true);
		m_pImapt->SetPosition(D3DXVECTOR3(n.x,n.y,n.z));
		m_isUse = false;
		m_isSleep = true;
		m_fTime = 0;

		if (m_fTime > WATERIMPACT)
		{
			m_pPhysX->pPhysX->m_pActor->putToSleep();
			m_pPhysX->pPhysX->m_pActor->raiseActorFlag(NX_AF_DISABLE_COLLISION);
	
			m_pPhysX->pTrigger->m_pActor->wakeUp();
			m_pPhysX->pTrigger->m_pActor->clearActorFlag(NX_AF_DISABLE_COLLISION);
	
			NxVec3 n = m_pPhysX->pPhysX->m_pActor->getGlobalPosition();
			m_pImapt->SetIsUse(true);
			m_pImapt->SetPosition(D3DXVECTOR3(n.x, n.y, n.z));
			m_isUse = false;
			m_isSleep = true;
			m_fTime = 0;
		}
	
		m_pPhysX->pTrigger->m_pActor->setGlobalPosition(m_pPhysX->pPhysX->m_pActor->getGlobalPosition());
	
		NxVec3 v = m_pPhysX->pPhysX->m_pActor->getGlobalPosition();
	
		printf("%f %f %f\n", v.x, v.y, v.z);

	}
	
	if (!m_pImapt->GetIsUse())
	{
		m_pPhysX->pTrigger->m_pActor->putToSleep();
		m_pPhysX->pTrigger->m_pActor->raiseActorFlag(NX_AF_DISABLE_COLLISION);
	}
	
	if (!m_isUse && m_pImapt->GetIsUse())
	{
		m_pImapt->Update();
	}

	m_pPhysX->pTrigger->m_pActor->setGlobalPosition(m_pPhysX->pPhysX->m_pActor->getGlobalPosition());
}

void cWbomb::Render()
{
	if (m_isUse)
	{
		m_pPhysX->pMesh->Render();
	}
	printf("asdf");
	if (!m_isUse && m_pImapt->GetIsUse())
	{
		m_pImapt->Render();

	}

	cItem::Render();
}

void cWbomb::Create(D3DXVECTOR3 angle, D3DXVECTOR3 pos)
{
	m_pPhysX->pos.x = pos.x;
	m_pPhysX->pos.y = pos.y + 1;
	m_pPhysX->pos.z = pos.z;
	
	NxVec3 force;
	
	force.x = angle.x * 10000;
	force.y = 3000;
	force.z = angle.z * 10000;
	
	if (m_isSleep)
	{
		m_pPhysX->pPhysX->m_pActor->wakeUp();
		m_pPhysX->pPhysX->m_pActor->clearActorFlag(NX_AF_DISABLE_COLLISION);
		
		m_pPhysX->pTrigger->m_pActor->putToSleep();
		m_pPhysX->pTrigger->m_pActor->raiseActorFlag(NX_AF_DISABLE_COLLISION);
		m_isSleep = false;
	}
	
	// 초기화 부분
	if (m_isInit)
	{
		m_pPhysX->pPhysX->m_pActor = MgrPhysX->CreateActor(NX_SHAPE_SPHERE, m_pPhysX->pos, NULL, NxVec3(1.0f, 0.0f, 0.0f), E_PHYSX_MATERIAL_CAR, m_pUser);
		m_pPhysX->pTrigger->m_pActor = MgrPhysX->CreateActor(NX_SHAPE_SPHERE, m_pPhysX->pos, NULL, NxVec3(3.0f, 0.0f, 0.0f), E_PHYSX_MATERIAL_CAR, m_pUser);
		
		NxVec3 v = m_pPhysX->pPhysX->m_pActor->getGlobalPosition();

		m_pPhysX->pTrigger->m_pActor->putToSleep();
		m_pPhysX->pTrigger->m_pActor->raiseActorFlag(NX_AF_DISABLE_COLLISION);
		SetActorGroup(m_pPhysX->pPhysX->m_pActor, E_PHYSX_TAG_WHATEBOMB);
		this->SetPhysXData(m_pPhysX->pPhysX);
		m_isInit = false;
	}
	
	m_pPhysX->pPhysX->m_pActor->addForce(force);
	m_pPhysX->pPhysX->m_pActor->addTorque(NxVec3(angle.x, angle.y, angle.z));
}
