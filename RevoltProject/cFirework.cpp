#include "stdafx.h"
#include "cFirework.h"
#include "ObjectLoader.h"
#include "PFirework.h"

cFirework::cFirework()
	: m_pPhysX(NULL)
	, m_pEffect(NULL)
	, m_pTail(NULL)
	, m_isSleep(false)
	, m_isTarget(false)
{
}


cFirework::~cFirework()
{
	SAFE_DELETE(m_pEffect);
	SAFE_DELETE(m_pTail);
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


	m_pEffect = new PFirework(100, 3.0f);
	m_pEffect->Init(g_pD3DDevice, "Objects/firework/particle_flare.bmp");

	m_pTail = new PFirework(5, 1.0f);
	m_pTail->Init(g_pD3DDevice, "Objects/firework/particle_flare.bmp");
}

void cFirework::Update()
{
	cItem::Update();

	fwPos.x = m_pPhysX->pPhysX->m_pActor->getGlobalPosition().x;
	fwPos.y = m_pPhysX->pPhysX->m_pActor->getGlobalPosition().y;
	fwPos.z = m_pPhysX->pPhysX->m_pActor->getGlobalPosition().z;

	if (m_isUse && !m_pEffect->GetIsUse())
	{
		NxVec3 force;

		if (m_isTarget)
		{
			D3DXVECTOR3 tar = D3DXVECTOR3(-10.0f, 0.0f, -10.0f);
			dir = tar - fwPos;

			D3DXVec3Normalize(&dir, &dir);

			force.x = dir.x * 1000;
			force.y = dir.y * 500;
			force.z = dir.z * 500;
		}
		else
		{
			dir.y = 0.0f;
			D3DXVec3Normalize(&dir, &dir);

			force.x = dir.x * 300;
			force.y = -dir.y * 1000;
			force.z = dir.z * 300;
		}
		
		m_pPhysX->pPhysX->m_pActor->addForce(force);
	}

	m_pTail->SetPosition(&fwPos);
	m_pTail->Update(0.1f);
	m_pTail->Reset();

	if (m_isUse && m_fTime > FIREWORKEFFECT)
	{
		m_pPhysX->pPhysX->m_pActor->putToSleep();
		m_pPhysX->pPhysX->m_pActor->raiseActorFlag(NX_AF_DISABLE_COLLISION);

		m_pPhysX->pTrigger->m_pActor->wakeUp();
		m_pPhysX->pTrigger->m_pActor->clearActorFlag(NX_AF_DISABLE_COLLISION);

		NxVec3 n = m_pPhysX->pPhysX->m_pActor->getGlobalPose().t;
		m_pEffect->SetPosition(&fwPos);
		m_pEffect->SetIsUse(true);
		m_pEffect->Reset();
		m_isUse = false;
		m_isSleep = true;
		m_fTime = 0;
	}

	if (!m_pEffect->GetIsUse())
	{
		m_pPhysX->pTrigger->m_pActor->putToSleep();
		m_pPhysX->pTrigger->m_pActor->raiseActorFlag(NX_AF_DISABLE_COLLISION);
	}

	if (!m_isUse && m_pEffect->GetIsUse())
		m_pEffect->Update(0.3f);

	m_pPhysX->pTrigger->m_pActor->setGlobalPosition(m_pPhysX->pPhysX->m_pActor->getGlobalPose().t);
}

void cFirework::Render()
{
	cItem::Render();

	if (m_isUse)
	{
		m_pPhysX->pMesh->Render();
		m_pTail->Render();
	}
	if (!m_isUse && m_pEffect->GetIsUse())
	{
		m_pEffect->Render();
	}
}

void cFirework::Create(D3DXVECTOR3 angle, D3DXVECTOR3 pos)
{
	m_isTarget = false;
	dir = angle;

	m_pPhysX->pos.x = pos.x;
	m_pPhysX->pos.y = pos.y + 1;
	m_pPhysX->pos.z = pos.z;
	
	NxVec3 force;


	D3DXVec3Normalize(&angle,&angle);

	force.x = angle.x * 50;
	force.y = 1500;
	force.z = angle.z * 50;
	
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
		m_pPhysX->pPhysX->m_pActor = MgrPhysX->CreateActor(NX_SHAPE_CAPSULE, m_pPhysX->pos, NULL, NxVec3(0.5f, 1.5f, 0.0f), E_PHYSX_MATERIAL_CAR, m_pUser);
		m_pPhysX->pTrigger->m_pActor = MgrPhysX->CreateActor(NX_SHAPE_SPHERE, m_pPhysX->pos, NULL, NxVec3(2.5f, 0.0f, 0.0f), E_PHYSX_MATERIAL_CAR, m_pUser);

		m_pPhysX->pTrigger->m_pActor->putToSleep();
		m_pPhysX->pTrigger->m_pActor->raiseActorFlag(NX_AF_DISABLE_COLLISION);
		SetActorGroup(m_pPhysX->pPhysX->m_pActor, 1	);
		this->SetPhysXData(m_pPhysX->pPhysX);
		m_isInit = false;
	}
	else
		m_pPhysX->pPhysX->m_pActor->setGlobalPosition(m_pPhysX->pos);

	m_pPhysX->pPhysX->m_pActor->addForce(force);
	m_pPhysX->pPhysX->m_pActor->addTorque(NxVec3(angle.x, angle.y, angle.z));
}
