#include "stdafx.h"
#include "ItemManager.h"
#include "cItem.h"
#include "ObjectLoader.h"
#include "cImpact.h"
#include "cGravityball.h"
#include "cWbomb.h"
#include "cFirework.h"
#include "cCar.h"
#include "cMyBomb.h"

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
	MgrPhysXScene->setUserContactReport(new ContactCallBack());

	if (MgrPhysXScene->getUserContactReport() == NULL)
		printf("report error");

	USERDATA* user1 = new USERDATA;
	user1->USER_TAG = E_PHYSX_TAG_NONE;

	box1 = MgrPhysX->CreateActor(NX_SHAPE_BOX, NxVec3(6, 0, 5), NULL, NxVec3(3.0f, 3.0f, 3.0f), E_PHYSX_MATERIAL_CAR, user1);
	box2 = MgrPhysX->CreateActor(NX_SHAPE_BOX, NxVec3(5, 0, 0), NULL, NxVec3(3.0f, 3.0f, 3.0f), E_PHYSX_MATERIAL_CAR, user1);
	box3 = MgrPhysX->CreateActor(NX_SHAPE_BOX, NxVec3(4, 0, 3), NULL, NxVec3(1.0f, 1.0f, 1.0f), E_PHYSX_MATERIAL_CAR, user1);
	box4 = MgrPhysX->CreateActor(NX_SHAPE_BOX, NxVec3(20, 0, 3), NULL, NxVec3(1.0f, 1.0f, 1.0f), E_PHYSX_MATERIAL_CAR, user1);

	//for (int i = 0;i < 10;i++)
	//{
	//	cItem* pItem = new cWbomb;
	//	pItem->Setup();
	//	pItem->SetItemTag(ITEM_WBOMB);
	//	m_vecItem.push_back(pItem);
	//}

	//for (int i = 0;i < 10;i++)
	//{
	//	cGravityball* pItem = new cGravityball;
	//	pItem->Setup();
	//	pItem->SetIsUse(true);
	//	m_vecItem.push_back(pItem);
	//}

	//for (int i = 0;i < 10;i++)
	//{
	//	cMyBomb* pItem = new cMyBomb;
	//	pItem->Setup();
	//	pItem->SetIsUse(false);
	//	pItem->SetItemTag(ITEM_MYBOMB);
	//	m_vecItem.push_back(pItem);
	//}

	for (int i = 0; i < 10; i++)
	{
		cItem* pItem = new cFirework;
		pItem->Setup();
		pItem->SetItemTag(ITEM_FIREWORK);
		m_vecItem.push_back(pItem);
	}

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
	//임시 박스
	SetActorGroup(box1, 1);
	SetActorGroup(box2, 2);
	SetActorGroup(box3, 2);
	SetActorGroup(box4, 2);

	box1->setGroup(1);
	box2->setGroup(2);
	box3->setGroup(2);
	box4->setGroup(2);

	MgrPhysXScene->setGroupCollisionFlag(1, 2, true);
	MgrPhysXScene->setGroupCollisionFlag(2, 2, true);
	MgrPhysXScene->setGroupCollisionFlag(1, 1, true);
	MgrPhysXScene->setActorGroupPairFlags(3, 3, NX_NOTIFY_ON_END_TOUCH);

}

void ItemManager::FireItem(eITEM_LIST tag/*아이템종류*/, cCar* car/*자동차 포인터*/)
{
	D3DXVECTOR3 carPos = car->GetPosition(); // 자동차 위치
	D3DXMATRIXA16 matR;
	D3DXMatrixIdentity(&matR);
	matR = car->GetCarRotMatrix();
	D3DXVECTOR3 carDir = { 1,0,0 }; // 자동차 정면 방향벡터
	D3DXVec3TransformNormal(&carDir, &carDir, &matR);
	
	if (m_index == m_vecItem.size())
		m_index = 0;

	switch (tag)
	{
		case ITEM_WBOMB:
		{
			m_vecItem[m_index]->Create(carDir, carPos);
			m_vecItem[m_index]->SetIsUse(true);
		}
		break;
		case ITEM_FIREWORK:
		{
			m_vecItem[m_index]->Create(carDir, carPos);
			m_vecItem[m_index]->SetIsUse(true);
		}
		break;
		case ITEM_GRAVITY:
		{
			//m_vecItem[m_index]->Create(carDir, carPos);
			//m_vecItem[m_index]->SetUse(true);
		}
		case ITEM_MYBOMB:
		{
			m_vecItem[m_index]->SetCar(car);
			m_vecItem[m_index]->Create(carDir, carPos);
			m_vecItem[m_index]->SetIsUse(true);
		}
		break;
		default: break;
	}

	//	m_vecItem[m_index]->Create();
		m_index++;
	//
		if (m_index == m_vecItem.size()) m_index = 0;
}
