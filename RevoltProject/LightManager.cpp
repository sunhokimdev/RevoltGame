#include "stdafx.h"
#include "LightManager.h"
#include "cLight.h"

LightManager::LightManager()
{
}

LightManager::~LightManager()
{
}

void LightManager::Setup()
{
}

void LightManager::Update()
{
}

void LightManager::Destroy()
{
	for each(auto p in m_mapLight)
	{
		p.second->Destroy();
		delete(p.second);
	}
	m_mapLight.clear();
}

void LightManager::AddLight(int index, cLight * light)
{
	
	if (m_mapLight.find(index) == m_mapLight.end())
	{
		//키값이 중복되지 않으면 등록한다.
		m_mapLight.insert(std::make_pair(index, light));
	}
	else
	{
		//키값이 중복되면 지우고 등록한다.
		m_mapLight[index]->Destroy();
		delete(m_mapLight[index]);
		m_mapLight.erase(index);

		m_mapLight.insert(std::make_pair(index, light));
	}
}

void LightManager::DeleteLight(int index)
{
	//찾는 키값이 있으면 지운다.
	if (m_mapLight.find(index) != m_mapLight.end())
	{
		m_mapLight[index]->Destroy();
		delete(m_mapLight[index]);
		m_mapLight.erase(index);
	}
}
