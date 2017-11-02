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

void cWbomb::Create()
{
	ST_PHYSX* pPhysX = new ST_PHYSX;

	USERDATA* user1 = new USERDATA;
	user1->ID = 1;

	pPhysX->pos = NxVec3(5, 0, 3);

	pPhysX->pPhysX = new cPhysX;
	pPhysX->pTrigger = new cPhysX;
	pPhysX->pMesh = new cMesh;

	ObjectLoader::LoadMesh(pPhysX->pMesh, "Objects/wbomb", "wbomb.obj");

	pPhysX->pPhysX->m_pActor = MgrPhysX->CreateActor(NX_SHAPE_SPHERE, pPhysX->pos, NULL, NxVec3(1.0f, 0.0f, 0.0f), user1);
	pPhysX->pPhysX->m_pActor->addForce(NxVec3(10000, 7000, 0));
	

	this->SetPhysXData(pPhysX->pPhysX);

	SetActorGroup(pPhysX->pPhysX->m_pActor, 1);

	m_vecPhysX.push_back(pPhysX);
}
