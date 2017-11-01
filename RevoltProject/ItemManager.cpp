#include "stdafx.h"
#include "ItemManager.h"
#include "cItem.h"
#include "ObjectLoader.h"
#include "cContactUser.h"
#include "cImpact.h"

ItemManager::ItemManager()
	: box1(NULL)
	, box2(NULL)
	, box3(NULL)
{
}

ItemManager::~ItemManager()
{
}

void ItemManager::Init()
{
	MgrPhysXScene->setUserTriggerReport(new TriggerCallback());

	USERDATA* user1 = new USERDATA;
	user1->ID = 1;

	box1 = MgrPhysX->CreateActor(NX_SHAPE_BOX, NxVec3(6, 0, 5), NULL, NxVec3(3.0f, 3.0f, 3.0f), user1);
	box2 = MgrPhysX->CreateActor(NX_SHAPE_BOX, NxVec3(5, 0, 0), NULL, NxVec3(3.0f, 3.0f, 3.0f), user1);
	box3 = MgrPhysX->CreateActor(NX_SHAPE_BOX, NxVec3(4, 0, 3), NULL, NxVec3(1.0f, 1.0f, 1.0f), user1);
	
	InitCollisionGroup();
}

void ItemManager::Update()
{
	for (int i = 0;i < m_vecItem.size();++i)
	{
		m_vecItem[i]->Update();
	}
	for (int i = 0;i < m_vecItem.size();++i)
	{
		m_vecItem[i]->LastUpdate();
	}

	if (g_pKeyManager->isOnceKeyDown(VK_CONTROL))
	{	
		
	}
}

void ItemManager::Render()
{
	for (int i = 0;i < m_vecItem.size();++i)
	{
		m_vecItem[i]->Render();
	}
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

	MgrPhysXScene->setGroupCollisionFlag(1, 2, false);
	MgrPhysXScene->setGroupCollisionFlag(2, 2, false);
}

