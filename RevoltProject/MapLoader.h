#pragma once
class cTrack;
class MapLoader
{
public:
	MapLoader();
	~MapLoader();

	void Load(cTrack* stMap, char* szFolder, const char* szFile);
};

