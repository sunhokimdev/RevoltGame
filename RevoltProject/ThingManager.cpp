#include "stdafx.h"
#include "ThingManager.h"

#include "Thing.h"


ThingManager::ThingManager()
{
}


ThingManager::~ThingManager()
{
}

void ThingManager::AddThing(std::string strKey, char * szFolder, char * szFile, bool isMove, bool isRot, float angle)
{
	m_mapThing[strKey] = new Thing;
	m_mapThing[strKey]->SetMesh(szFolder, szFile);
}

void ThingManager::Render(std::string strKey)
{
	m_mapThing[strKey]->Render();
}

