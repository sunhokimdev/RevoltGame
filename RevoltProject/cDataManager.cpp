#include "stdafx.h"
#include "cDataManager.h"


cDataManager::cDataManager()
{
	mapName = "Market2";
	cPlayerData* player = new cPlayerData;
	player->CAR_NAME = "tc1";
	player->IsAI = false;
	vecPlayerData.push_back(player);
}


cDataManager::~cDataManager()
{
	SAFE_DELETE(vecPlayerData[0]);
}
