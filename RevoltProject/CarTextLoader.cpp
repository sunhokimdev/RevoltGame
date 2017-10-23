#include "stdafx.h"
#include "CarTextLoader.h"


CarTextLoader::CarTextLoader()
{
}


CarTextLoader::~CarTextLoader()
{
}

void CarTextLoader::Load(ST_CAR& szCar, char * szFolder, char * szFile)
{
	std::string sFullPath(szFolder);
	sFullPath += (std::string("/") + std::string(szFile));

	FILE* fp;
	fopen_s(&fp, sFullPath.c_str(), "r");

	while (true)
	{
		if (feof(fp)) break;

		char szTemp[1024];
		char* pch;
		std::string str;
		fgets(szTemp, 1024, fp);

		pch = strtok(szTemp, "\t ;");
		str = pch;

		if (str == "Name")
		{
			pch = strtok(NULL, "\t ;");
			szCar.name = pch;
		}
		else if (str == "Class")
		{
			pch = strtok(NULL, "\t ;");
			std::string s = pch;

			if (s == "0")
				szCar.car_class = "Electronic";
			if(s=="1")
				szCar.car_class = "Glow";
			if(s=="2")
				szCar.car_class = "Other";
		}
		else if (str == "Rating")
		{
			pch = strtok(NULL, "\t ;");
			std::string s = pch;

			if (s == "0")
				szCar.car_skill_level = "rookie";
			if (s == "1")
				szCar.car_skill_level = "amateur";
			if (s == "2")
				szCar.car_skill_level = "pro";
		}
		else if (str == "Acc")
		{
			pch = strtok(NULL, "\t ;");

			szCar.acc = atof(pch);
		}
		else if (str == "Weight")
		{
			pch = strtok(NULL, "\t ;");
			szCar.weight = atof(pch);
		}
		else if (str == "Trans")
		{
			pch = strtok(NULL, "\t ;");
			szCar.weight = atoi(pch);
		}
	}
}
