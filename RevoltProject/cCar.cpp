#include "stdafx.h"
#include "cCar.h"
#include "cWheel.h"

cCar::cCar()
{
	
}


cCar::~cCar()
{
	
}

void cCar::RegisteWheel(cWheel_ID id, cWheel* pWheel)
{
	if(mapWheels.size()!=4) mapWheels.resize(4);

	if (pWheel)
	{
		mapWheels[id] = pWheel;
		pWheel->SetBody(this);
	}
}

void cCar::LoadMesh(std::string carName)
{
	GetMeshData()->LoadMesh("Cars/" + carName, carName + ".obj");
}
