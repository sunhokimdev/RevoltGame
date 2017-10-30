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
	cItem* pItem = new cItem;
	cMesh* pMesh = new cMesh;
	cPhysX* pPhysx = new cPhysX;
	ObjectLoader::LoadMesh(pMesh, "Objects/wbomb", "wbomb.obj");
	pItem->SetMeshData(pMesh);
	pItem->SetPhysXData(pPhysx);

	pPhysx->m_pActor = MgrPhysX->CreateActor(NX_SHAPE_SPHERE, NxVec3(0, 0, 0), NULL, NxVec3(1.0f, 0, 0), NULL);

	m_vecItem.push_back(pItem);
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
}

void ItemManager::Render()
{
	for (int i = 0;i < m_vecItem.size();++i)
	{
		m_vecItem[i]->Render();
	}
}
