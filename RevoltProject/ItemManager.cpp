#include "stdafx.h"
#include "ItemManager.h"
#include "cItem.h"
#include "ObjectLoader.h"

ItemManager::ItemManager()
{
}

ItemManager::~ItemManager()
{
}

void ItemManager::Init()
{
	/*   Áß·ÂÅº ¼³Á¤   */
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
		cItem* pItem = new cItem;
		cMesh* pMesh = new cMesh;
		cPhysX* pPhysx = new cPhysX;
		ObjectLoader::LoadMesh(pMesh, "Objects/gravityball", "gravityball.obj");
		pItem->SetMeshData(pMesh);
		pItem->SetPhysXData(pPhysx);

		pPhysx->m_pActor = MgrPhysX->CreateActor(NX_SHAPE_SPHERE, NxVec3(5, 0, 3), NULL, NxVec3(1.0f, 0, 0), E_PHYSX_MATERIAL_CAR, NULL,false);
		pPhysx->m_pActor->addLocalForce(NxVec3(40000, 0, 0));
		
		m_vecItem.push_back(pItem);
	}
}

void ItemManager::Render()
{
	for (int i = 0;i < m_vecItem.size();++i)
	{
		m_vecItem[i]->Render();
	}
}
