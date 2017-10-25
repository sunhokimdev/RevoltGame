#include "stdafx.h"
#include "CarTextLoader.h"


CarTextLoader::CarTextLoader()
{
}


CarTextLoader::~CarTextLoader()
{
}

void CarTextLoader::Load(ST_CAR& szCar, const char * szFile)
{
	FILE* fp;
	int offsetIndex = 0;
	fopen_s(&fp, szFile, "r");

	while (true)
	{
		if (feof(fp)) break;

		char szTemp[1024];
		char* pch;
		std::string str;
		fgets(szTemp, 2048, fp);

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
				szCar.car_skill_level = "semi_pro";
			if (s == "3")
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
			switch (atoi(pch))
			{
				case 0:
					szCar.trans = "4WD";
					break;
				case 1:
					szCar.trans = "FWD";
					break;
				case 2:
					szCar.trans = "RWD";
					break;
			}
		}
		else if (str == "TopSpeed")
		{
			pch = strtok(NULL, "\t ;");
			szCar.speed = atof(pch);
		}
		else if (str == "Offset1")
		{
			D3DXVECTOR3 tV;

			tV.x = atof(strtok(NULL, "\t ;")) / 100;
			tV.y = -atof(strtok(NULL, "\t ;")) / 100;
			tV.z = atof(strtok(NULL, "\t ;")) / 100;

			switch (offsetIndex)
			{
				case 0:
					szCar.fl = tV;
				break;
				case 1:
					szCar.fr = tV;
				break;
				case 2:
					szCar.bl = tV;
				break;
				case 3:
					szCar.br = tV;
				break;
			}

			offsetIndex++;
		}
	}
}
