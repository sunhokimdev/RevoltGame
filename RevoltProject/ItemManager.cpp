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
	: m_max(50)
	, m_index(0)
	, m_eItemList(ITEM_NONE)
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

	for (int i = 0;i < 10;i++)
	{
		cWbomb* pItem = new cWbomb;
		pItem->Setup();
		pItem->SetIsUse(false);
		pItem->SetItemTag(ITEM_WBOMB);
		m_vecItem.push_back(pItem);
	}

	for (int i = 0;i < 10;i++)
	{
		cGravityball* pItem = new cGravityball;
		pItem->Setup();
		pItem->SetIsUse(false);
		m_vecItem.push_back(pItem);
	}

	for (int i = 0;i < 10;i++)
	{
		cMyBomb* pItem = new cMyBomb;
		pItem->Setup();
		pItem->SetIsUse(false);
		pItem->SetItemTag(ITEM_MYBOMB);
		m_vecItem.push_back(pItem);
	}

	for (int i = 0; i < 10; i++)
	{
		cFirework* pItem = new cFirework;
		pItem->Setup();
		pItem->SetIsUse(false);
		pItem->SetItemTag(ITEM_FIREWORK);
		m_vecItem.push_back(pItem);
	}

	for (int i = 0;i < 4;i++)
	{
		m_vecIndex[i] = 0;
	}

	InitCollisionGroup();
}

void ItemManager::Update()
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < m_vecIndex[i]; ++j)
		{
			m_vecItem[j + i * 10]->Update();
		}
	}
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < m_vecIndex[i]; ++j)
		{
			m_vecItem[j + i * 10]->LastUpdate();
		}
	}
}

void ItemManager::Render()
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < m_vecIndex[i]; ++j)
		{
			m_vecItem[j + i * 10]->Render();
		}
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

}

void ItemManager::FireItem(eITEM_LIST tag/*아이템종류*/, cCar* car/*자동차 포인터*/)
{
	D3DXVECTOR3 carPos = car->GetPosition(); // 자동차 위치
	D3DXMATRIXA16 matR;
	D3DXMatrixIdentity(&matR);
	matR = car->GetCarRotMatrix();
	D3DXVECTOR3 carDir;// = car->CarArrow(); // 자동차 정면 방향벡터
	carDir.x = car->CarArrow(0).x;
	carDir.y = car->CarArrow(0).y;
	carDir.z = car->CarArrow(0).z;
	//D3DXVec3TransformNormal(&carDir, &carDir, &matR);
	
	switch (tag)
	{
		case ITEM_WBOMB:
		{
			m_vecItem[m_vecIndex[0]]->Create(carDir, carPos);
			m_vecItem[m_vecIndex[0]]->SetIsUse(true);

			m_vecIndex[0]++;
		}
		break;
		case ITEM_GRAVITY:
		{
			m_vecItem[m_vecIndex[1] + 10]->Create(carDir, carPos);
			m_vecItem[m_vecIndex[1] + 10]->SetIsUse(true);

			m_vecIndex[1]++;
		}
		break;
		case ITEM_MYBOMB:
		{
			m_vecItem[m_vecIndex[2] + 20]->SetCar(car);
			m_vecItem[m_vecIndex[2] + 20]->Create(carDir, carPos);
			m_vecItem[m_vecIndex[2] + 20]->SetIsUse(true);

			m_vecIndex[2]++;
		}
		break;
		case ITEM_FIREWORK:
		{
			m_vecItem[m_vecIndex[3] + 30]->Create(carDir, carPos);
			m_vecItem[m_vecIndex[3] + 30]->SetIsUse(true);

			m_vecIndex[3]++;
		}
		break;
		default: break;
	}

	for (int i = 0;i < 4;i++)
	{
		if (m_vecIndex[i] == 10)
			m_vecIndex[i] = 0;
	}
}

int ItemManager::GetItemID()
{
	if (m_eItemList == ITEM_WBOMB)
		return 8;
	else if (m_eItemList == ITEM_FIREWORK)
		return 6;
	else if (m_eItemList == ITEM_MYBOMB)
		return 5;
	else if (m_eItemList == ITEM_GRAVITY)
		return 4;
	else
		return INT_MAX;
}

void ItemManager::Destroy()
{
	for each(auto p in m_vecItem)
	{
		SAFE_DELETE(p);
	}

	for (int i = 0;i < 4;i++)
		m_vecIndex[i] = 0;
}
