#pragma once
class MapLoader
{
public:
	MapLoader();
	~MapLoader();

	void Load(ST_MAP* stMap, char* szFolder, const char* szFile);
};

