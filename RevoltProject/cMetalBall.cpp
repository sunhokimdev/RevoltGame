#include "stdafx.h"
#include "cMetalBall.h"
#include "ObjectLoader.h"

cMetalBall::cMetalBall()
{
}


cMetalBall::~cMetalBall()
{
}

void cMetalBall::Setup()
{
	cItem::Setup();
}

void cMetalBall::Update()
{
	cItem::Update();
}

void cMetalBall::Render()
{
	cItem::Render();

	for (int i = 0; i < m_vecPhysX.size(); ++i)
		m_vecPhysX[i]->pMesh->Render();
}

void cMetalBall::Create(D3DXVECTOR3 angle, D3DXVECTOR3 pos)
{
	ST_PHYSX* pPhysX = new ST_PHYSX;

	USERDATA* user1 = new USERDATA;
	user1->USER_TAG = E_PHYSX_TAG_METALBALL;

	pPhysX->pos.x = pos.x;
	pPhysX->pos.y = pos.y + 1;
	pPhysX->pos.z = pos.z;

	pPhysX->pPhysX = new cPhysX;
	pPhysX->pTrigger = new cPhysX;
	pPhysX->pMesh = new cMesh;

	ObjectLoader::LoadMesh(pPhysX->pMesh, "Objects/football", "football.obj");


	NxVec3 force;

	force.x = angle.x * 1000;
	force.y = angle.y;
	force.z = angle.z * 10000;

	pPhysX->pPhysX->m_pActor = MgrPhysX->CreateActor(NX_SHAPE_SPHERE, pPhysX->pos, NULL, NxVec3(1.0f, 0.0f, 0.0f), E_PHYSX_MATERIAL_CAR, user1);
	pPhysX->pPhysX->m_pActor->addForce(force);

	this->SetPhysXData(pPhysX->pPhysX);

	SetActorGroup(pPhysX->pPhysX->m_pActor, 1);

	m_vecPhysX.push_back(pPhysX);
}
