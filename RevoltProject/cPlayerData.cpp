#include "stdafx.h"
#include "cPlayerData.h"


cPlayerData::cPlayerData()
{
	IP = "";
	ID = "";
	CAR_NAME = "";
	IsAI = true;

	ITEM_ID = -1;
}

cPlayerData::~cPlayerData()
{
}

cPlayerData::cPlayerData(std::string IP, std::string ID, std::string CAR_NAME, bool IsAI, bool isUser)
{
	this->IP = IP;
	this->ID = ID;
	this->CAR_NAME = CAR_NAME;
	this->IsAI = IsAI;
	this->isUser = isUser;

	ITEM_ID = -1;
}
