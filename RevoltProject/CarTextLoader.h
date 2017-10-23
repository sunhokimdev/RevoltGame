#pragma once
class CarTextLoader
{
public:
	CarTextLoader();
	~CarTextLoader();

	void Load(ST_CAR& szCar,char* szFolder, char* szFile);
};

