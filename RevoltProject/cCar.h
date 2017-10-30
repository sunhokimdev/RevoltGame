#pragma once
#include "Object.h"

class cWheel;
enum cWheel_ID
{
	fl,	//자동차 바튀 위치
	fr,	//
	bl,	//
	br,	//
};

class cCar :public Object
{
	std::vector<cWheel*> mapWheels;

public:
	cCar();
	~cCar();

	void RegisteWheel(cWheel_ID id, cWheel* pWheel);
	void LoadMesh(std::string carName);
};

