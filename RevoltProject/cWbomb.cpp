#include "stdafx.h"
#include "cWbomb.h"
#include "ObjectLoader.h"
#include "cWaterBombImpact.h"

cWbomb::cWbomb()
	: m_pPhysX(NULL)
	, m_pImapt(NULL)
{
}

cWbomb::~cWbomb()
{
	SAFE_DELETE(m_pImapt);
}

void cWbomb::Setup()
{
	cItem::Setup();

	m_pImapt = new cWaterBombImpact;
	m_pImapt->Setup();
}

void cWbomb::Update()
{
	cItem::Update();

	if (m_isUse && m_fTime > WATERIMPACT)
	{
		m_pPhysX->pPhysX->m_pActor->putToSleep();
		m_pPhysX->pPhysX->m_pActor->raiseActorFlag(NX_AF_DISABLE_COLLISION);
		NxVec3 n = m_pPhysX->pPhysX->m_pActor->getGlobalPose().t;
		D3DXVECTOR3 v;
		v.x = n.x;
		v.y = n.y;
		v.z = n.z;
		m_pImapt->SetIsUse(true);
		m_pImapt->SetPosition(v);
		m_isUse = false;
	}

	if (!m_isUse && m_pImapt->GetIsUse())
		m_pImapt->Update();
}

void cWbomb::Render()
{
	cItem::Render();

	if(m_isUse)
		m_pPhysX->pMesh->Render();

	if (!m_isUse && m_pImapt->GetIsUse())
		m_pImapt->Render();
}

void cWbomb::Create(D3DXVECTOR3 angle, D3DXVECTOR3 pos)
{
	ST_PHYSX* pPhysX = new ST_PHYSX;

	USERDATA* user1 = new USERDATA;
	user1->USER_TAG = E_PHYSX_TAG_WHATEBOMB;

	pPhysX->pos.x = pos.x;
	pPhysX->pos.y = pos.y+1;
	pPhysX->pos.z = pos.z;

	pPhysX->pPhysX = new cPhysX;
	pPhysX->pTrigger = new cPhysX;
	pPhysX->pMesh = new cMesh;

	ObjectLoader::LoadMesh(pPhysX->pMesh, "Objects/wbomb", "wbomb.obj");

	NxVec3 force;

	force.x = angle.x * 10000;
	force.y = 3000;
	force.z = angle.z * 10000;

	pPhysX->pPhysX->m_pActor = MgrPhysX->CreateActor(NX_SHAPE_SPHERE, pPhysX->pos, NULL, NxVec3(1.0f, 0.0f, 0.0f),E_PHYSX_MATERIAL_CAR, user1);
	pPhysX->pPhysX->m_pActor->addForce(force);
	pPhysX->pPhysX->m_pActor->addTorque(NxVec3(angle.x, angle.y, angle.z));

	this->SetPhysXData(pPhysX->pPhysX);

	SetActorGroup(pPhysX->pPhysX->m_pActor, 1);

	m_pPhysX = pPhysX;
}
