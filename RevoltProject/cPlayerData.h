#pragma once
#define BITESET_8_SIZE 8 * 1
class cPlayerData
{
public:
	cPlayerData();
	~cPlayerData();

	cPlayerData(std::string IP, std::string ID, std::string CAR_NAME, bool IsAI);
public:
	bool IsAI;

	std::string IP;
	std::string ID;

	std::string CAR_NAME;
	std::bitset<BITESET_8_SIZE> INPUT_KEY;

	//0~11
	int ITEM_ID;
};

