#include "stdafx.h"
#include "cFakeBomb.h"
#include "cFakeImpact.h"
#include "ObjectLoader.h"
#include "cCar.h"

cFakeBomb::cFakeBomb()
	: m_bombAngle(0.0f)
	, m_bombTime(0.0f)
{
	cItem::cItem();
}


cFakeBomb::~cFakeBomb()
{

}

void cFakeBomb::Setup()
{
	cItem::Setup();

	m_pImpact = new cFakeImpact;
	m_pImpact->Setup();
	m_pImpact->SetIsUse(false);

	ObjectLoader::LoadMesh(m_pPhysX->pMesh, "Objects/fakebomb", "pickup.obj");

	m_pUser->USER_TAG = E_PHYSX_TAG_FAKEBOMB;
}

void cFakeBomb::Update()
{
	cItem::Update();
	
	if (m_pCar->GetPhysXData()->m_pUserData->isFakebombCollision)
	{
		m_pPhysX->pPhysX->m_pActor->wakeUp();
		m_pPhysX->pPhysX->m_pActor->clearActorFlag(NX_AF_DISABLE_COLLISION);
		m_pImpact->SetIsUse(true);
		m_isUse = false;
		m_bombTime = 0.0f;
	}

	if (m_isUse && !m_pImpact->GetIsUse())
		m_bombAngle += 0.1f;
	
	if (!m_isUse && m_pImpact->GetIsUse())
	{
		m_bombTime++;
		m_pImpact->Update();
	}

	if (m_bombTime > UPDATETIME)
	{
		m_pPhysX->pPhysX->m_pActor->putToSleep();
		m_pPhysX->pPhysX->m_pActor->raiseActorFlag(NX_AF_DISABLE_COLLISION);
	}

	if (!m_isUse && !m_pImpact->GetIsUse())
		SetIsEnd(true);
}

void cFakeBomb::Render()
{
	cItem::Render();
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);

	D3DXMatrixRotationY(&matWorld, m_bombAngle);

	if (m_isUse && !m_pImpact->GetIsUse())
	{
		matWorld._41 = m_pPhysX->pos.x;
		matWorld._42 = m_pPhysX->pos.y;
		matWorld._43 = m_pPhysX->pos.z;
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
		m_pPhysX->pMesh->Render();
	}
	
	if (!m_isUse && m_pImpact->GetIsUse())
	{
		m_pImpact->Render();
	}

	m_pPhysX->pPhysX->m_pActor->setGlobalPosition(m_pPhysX->pos);
}

void cFakeBomb::Create(D3DXVECTOR3 angle, D3DXVECTOR3 pos)
{
	m_pPhysX->pos.x = pos.x - angle.x;
	m_pPhysX->pos.y = pos.y + 0.4;
	m_pPhysX->pos.z = pos.z - (angle.z * 5);

	if (m_isInit)
	{
		m_pPhysX->pPhysX->m_pActor = MgrPhysX->CreateActor(NX_SHAPE_SPHERE, m_pPhysX->pos, NULL, NxVec3(3.0f, 0.0f, 0.0f), E_PHYSX_MATERIAL_CAR, m_pUser, false);
		m_pPhysX->pTrigger->m_pActor = MgrPhysX->CreateActor(NX_SHAPE_SPHERE, m_pPhysX->pos, NULL, NxVec3(1.0f, 0.0f, 0.0f), E_PHYSX_MATERIAL_CAR, m_pUser, true);
		SetActorGroup(m_pPhysX->pTrigger->m_pActor, E_PHYSX_TAG_FAKEBOMB);
		SetActorGroup(m_pPhysX->pPhysX->m_pActor, E_PHYSX_TAG_FAKEBOMB);
		m_isInit = false;
	}

	m_pPhysX->pPhysX->m_pActor->putToSleep();
	m_pPhysX->pPhysX->m_pActor->raiseActorFlag(NX_AF_DISABLE_COLLISION);
	m_pPhysX->pPhysX->m_pActor->setGlobalPosition(m_pPhysX->pos);
	m_pCar->GetPhysXData()->m_pUserData->isFireFakebomb = true;
	m_pCar->GetPhysXData()->m_pUserData->isFakebombCollision = false;

	m_isUse = true;
	m_isEnd = false;
}
