#pragma once
#include "cPlayerData.h"

#define g_pDataManager cDataManager::GetInstance()
class cDataManager
{
public:
	SINGLETONE(cDataManager);
private:
public:
	std::string mapName;
	std::vector<cPlayerData*> vecPlayerData;

	void TEST()
	{

	}

	void Destory()
	{

	}

};

