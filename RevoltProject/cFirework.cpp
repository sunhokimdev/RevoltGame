#include "stdafx.h"
#include "cFirework.h"
#include "ObjectLoader.h"

cFirework::cFirework()
	: m_pPhysX(NULL)
	, m_isSleep(false)
{
}


cFirework::~cFirework()
{
}

void cFirework::Setup()
{
	cItem::Setup();

	m_pPhysX = new ST_PHYSX;

	m_pPhysX->pPhysX = new cPhysX;
	m_pPhysX->pTrigger = new cPhysX;
	m_pPhysX->pMesh = new cMesh;

	ObjectLoader::LoadMesh(m_pPhysX->pMesh, "Objects/firework", "firework.obj");

	m_pUser->USER_TAG = ePhysXTag::E_PHYSX_TAG_FIREWORK;
}

void cFirework::Update()
{
	cItem::Update();

	D3DXVECTOR3 tar = D3DXVECTOR3(-10.0f, 0.0f, -10.0f);
	D3DXVECTOR3 dir = tar - m_pos;

	D3DXVec3Normalize(&dir, &dir);

	NxVec3 force;

	force.x = dir.x * 1000;
	force.y = dir.y * 1000;
	force.z = dir.z * 1000;

	m_pPhysX->pPhysX->m_pActor->addForce(force);

	m_pPhysX->pTrigger->m_pActor->setGlobalPosition(m_pPhysX->pPhysX->m_pActor->getGlobalPose().t);
}

void cFirework::Render()
{
	cItem::Render();

	if (m_isUse)
		m_pPhysX->pMesh->Render();
}

void cFirework::Create(D3DXVECTOR3 angle, D3DXVECTOR3 pos)
{
	m_pos = pos;

	m_pPhysX->pos.x = pos.x;
	m_pPhysX->pos.y = pos.y + 1;
	m_pPhysX->pos.z = pos.z;

	NxVec3 force;

	force.x = angle.x * 10000;
	force.y = angle.y * 1000;
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
		m_pPhysX->pPhysX->m_pActor = MgrPhysX->CreateActor(NX_SHAPE_CAPSULE, m_pPhysX->pos, NULL, NxVec3(1.0f, 0.0f, 0.0f), E_PHYSX_MATERIAL_CAR, m_pUser);
		m_pPhysX->pTrigger->m_pActor = MgrPhysX->CreateActor(NX_SHAPE_CAPSULE, m_pPhysX->pos, NULL, NxVec3(1.5f, 0.0f, 0.0f), E_PHYSX_MATERIAL_CAR, m_pUser);

		m_pPhysX->pTrigger->m_pActor->putToSleep();
		m_pPhysX->pTrigger->m_pActor->raiseActorFlag(NX_AF_DISABLE_COLLISION);
		SetActorGroup(m_pPhysX->pPhysX->m_pActor, 1);
		this->SetPhysXData(m_pPhysX->pPhysX);
		m_isInit = false;
	}

	else
		m_pPhysX->pPhysX->m_pActor->setGlobalPosition(m_pPhysX->pos);

	m_pPhysX->pPhysX->m_pActor->addForce(force);
	m_pPhysX->pPhysX->m_pActor->addTorque(NxVec3(angle.x, angle.y, angle.z));
}
