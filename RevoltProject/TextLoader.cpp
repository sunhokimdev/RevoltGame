#include "stdafx.h"
#include "TextLoader.h"


TextLoader::TextLoader()
{
}


TextLoader::~TextLoader()
{
}

void TextLoader::LanguageTextLoad(OUT std::vector<std::string>& vecString, IN char * szFolder, IN char * szFile)
{
	std::string fileStr;
	FILE* fp;

	fileStr = std::string(szFolder) + std::string("/") + std::string(szFile);

	fopen_s(&fp, fileStr.c_str(), "r");

	while (true)
	{
		if (feof(fp)) break;

		char szTemp[1024];
		fgets(szTemp, 1024, fp);

		vecString.push_back(szTemp);
	}
}
