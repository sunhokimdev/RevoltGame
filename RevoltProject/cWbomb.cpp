#include "stdafx.h"
#include "cWbomb.h"
#include "ObjectLoader.h"

cWbomb::cWbomb()
{
}

cWbomb::~cWbomb()
{
}

void cWbomb::Setup()
{
	cItem::Setup();
}

void cWbomb::Update()
{
	cItem::Update();
}

void cWbomb::Render()
{
	cItem::Render();

	for (int i = 0;i < m_vecPhysX.size();++i)
		m_vecPhysX[i]->pMesh->Render();
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
	force.y = 7000;
	force.z = angle.z * 10000;

	pPhysX->pPhysX->m_pActor = MgrPhysX->CreateActor(NX_SHAPE_SPHERE, pPhysX->pos, NULL, NxVec3(1.0f, 0.0f, 0.0f),E_PHYSX_MATERIAL_CAR, user1);
	pPhysX->pPhysX->m_pActor->addForce(force);

	this->SetPhysXData(pPhysX->pPhysX);

	SetActorGroup(pPhysX->pPhysX->m_pActor, 1);

	m_vecPhysX.push_back(pPhysX);
}
