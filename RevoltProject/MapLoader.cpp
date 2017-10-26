#include "stdafx.h"
#include "MapLoader.h"
#include "ObjectLoader.h"
#include "cTrack.h"

MapLoader::MapLoader()
{
}


MapLoader::~MapLoader()
{
}

void MapLoader::Load(cTrack* stMap, char * szFolder, const char * szFile)
{

	FILE* fp;
	int offsetIndex = 0;

	std::string fileName = std::string(szFolder) + std::string("/") + std::string(szFile) + std::string(".txt");

	fopen_s(&fp, fileName.c_str(), "r");

	while (true)
	{
		if (feof(fp)) break;

		char szTemp[1024];
		char* pch;
		std::string str;
		fgets(szTemp, 2048, fp);

		pch = strtok(szTemp, "\t ;");
		str = pch;

		if (str == "Map")
		{
			ObjectLoader load;
			std::string tStr = strtok(NULL, "\t ;");
			std::string tFolder = std::string(szFolder) + std::string("/") + std::string(szFile);
			tStr = std::string(szFile) + std::string(".obj");
			stMap->m_pObjMesh = load.LoadMesh(stMap->m_vecObjMtlTex, (tFolder.c_str()), tStr.c_str());
		}
	}
}
