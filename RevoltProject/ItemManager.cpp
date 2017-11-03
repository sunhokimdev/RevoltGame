#include "stdafx.h"
#include "ItemManager.h"
#include "cItem.h"
#include "ObjectLoader.h"
#include "cImpact.h"
#include "cGravityball.h"
#include "cWbomb.h"

ItemManager::ItemManager()
	: box1(NULL)
	, box2(NULL)
	, box3(NULL)
	, m_max(50)
	, m_index(0)
{
}

ItemManager::~ItemManager()
{
}

void ItemManager::Init()
{
	MgrPhysXScene->setUserTriggerReport(new TriggerCallback());

	USERDATA* user1 = new USERDATA;
	user1->USER_TAG = E_PHYSX_TAG_NONE;

	box1 = MgrPhysX->CreateActor(NX_SHAPE_BOX, NxVec3(6, 0, 5), NULL, NxVec3(3.0f, 3.0f, 3.0f), E_PHYSX_MATERIAL_CAR, user1);
	box2 = MgrPhysX->CreateActor(NX_SHAPE_BOX, NxVec3(5, 0, 0), NULL, NxVec3(3.0f, 3.0f, 3.0f), E_PHYSX_MATERIAL_CAR, user1);
	box3 = MgrPhysX->CreateActor(NX_SHAPE_BOX, NxVec3(4, 0, 3), NULL, NxVec3(1.0f, 1.0f, 1.0f), E_PHYSX_MATERIAL_CAR, user1);
	box4 = MgrPhysX->CreateActor(NX_SHAPE_BOX, NxVec3(20, 0, 3), NULL, NxVec3(1.0f, 1.0f, 1.0f), E_PHYSX_MATERIAL_CAR, user1);

	for (int i = 0;i < 10;i++)
	{
		cWbomb* pItem = new cWbomb;
		pItem->Setup();
		pItem->SetItemTag(ITEM_WBOMB);
		m_vecItem.push_back(pItem);
	}

	//for (int i = 0;i < 10;i++)
	//{
	//	cGravityball* pItem = new cGravityball;
	//	pItem->Setup();
	//	pItem->SetUse(true);
	//	m_vecItem.push_back(pItem);
	//}

	InitCollisionGroup();
}

void ItemManager::Update()
{
	for (int i = 0;i < m_index;++i)
	{
		m_vecItem[i]->Update();
	}
	for (int i = 0;i < m_index;++i)
	{
		m_vecItem[i]->LastUpdate();
	}

	if(m_index > 10)
		m_index = 0;
}

void ItemManager::Render()
{
	for (int i = 0;i < m_index;++i)
	{
		m_vecItem[i]->Render();
	}
}

void ItemManager::SetFire(D3DXVECTOR3 angle, D3DXVECTOR3 pos)
{
	if (m_index == m_vecItem.size())
		m_index = 0;

	m_vecItem[m_index]->Create(angle, pos);
	m_vecItem[m_index]->SetUse(true);
	m_index++;
}

void ItemManager::SetActorGroup(NxActor * actor, NxCollisionGroup group)
{
	NxU32 nbShapes = actor->getNbShapes();
	NxShape** shapes = (NxShape**)actor->getShapes();

	while (nbShapes--)
	{
		shapes[nbShapes]->setGroup(group);
	}
}

void ItemManager::InitCollisionGroup()
{
	SetActorGroup(box1, 1);
	SetActorGroup(box2, 1);
	SetActorGroup(box3, 1);
	SetActorGroup(box4, 1);

	MgrPhysXScene->setGroupCollisionFlag(1, 2, false);
	MgrPhysXScene->setGroupCollisionFlag(2, 2, false);
}

void ItemManager::FireItem(eITEM_LIST tag)
{
//	m_vecItem[m_index]->Create();
//	m_index++;
//
//	if (m_index == m_max) m_index = 0;
}

