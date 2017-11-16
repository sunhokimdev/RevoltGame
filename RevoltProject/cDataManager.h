#pragma once
#include "cPlayerData.h"

#define g_pDataManager cDataManager::GetInstance()
class cDataManager
{
public:
	SINGLETONE(cDataManager);
private:
public:
	D3DXVECTOR3 m_position;
	std::string mapName;
	std::vector<cPlayerData*> vecPlayerData;

	void TEST()
	{

	}

	void Reset()
	{
		mapName = "";
		for (int i = 0; i < vecPlayerData.size(); i++)
		{
			SAFE_DELETE(vecPlayerData[i]);
		}
		vecPlayerData.clear();
	}

	void Destroy()
	{
		Reset();

	}

};

