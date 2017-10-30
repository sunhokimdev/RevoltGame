#include "stdafx.h"
#include "Car.h"
#include "MtlTex.h"
#include "ObjectLoader.h"

Car::Car()
{
}

Car::~Car()
{

}

void Car::Setup()
{

}

void Car::Update()
{
	Thing::Update();
}

void Car::Render()
{
	Thing::Render();

	for each(auto p in m_vecChild)
	{
		p->Render();
	}
}

void Car::MirrorRender()
{
	Thing::MirrorRender();

	for each(auto p in m_vecChild)
	{
		p->MirrorRender();
	}
}

void Car::SetSTCar(ST_CAR car)
{
	m_stCar = car;
}

void Car::SetMeshWheel(char * szFolder, char * szName)
{
//	std::string tStr;
//	ObjectLoader load;
//
//	{
//		Thing* tWheel = new Car;
//		tStr = std::string(szName) + std::string("fl.obj");
//		tWheel->SetPosition(m_stCar.fl.x, m_stCar.fl.y, m_stCar.fl.z);
//		tWheel->SetMesh(szFolder, const_cast<char*>(tStr.c_str()));
//		AddChild(tWheel);
//	}
//
//	{
//		Thing* tWheel = new Thing;
//		tStr = std::string(szName) + std::string("fr.obj");
//		tWheel->SetPosition(m_stCar.fr.x, m_stCar.fr.y, m_stCar.fr.z);
//		tWheel->SetMesh(szFolder, const_cast<char*>(tStr.c_str()));
//		AddChild(tWheel);
//	}
//
//	{
//		Thing* tWheel = new Thing;
//		tStr = std::string(szName) + std::string("bl.obj");
//		tWheel->SetPosition(m_stCar.bl.x, m_stCar.bl.y, m_stCar.bl.z);
//		tWheel->SetMesh(szFolder, const_cast<char*>(tStr.c_str()));
//		AddChild(tWheel);
//	}
//
//	{
//		Thing* tWheel = new Thing;
//		tStr = std::string(szName) + std::string("br.obj");
//		tWheel->SetPosition(m_stCar.br.x, m_stCar.br.y, m_stCar.br.z);
//		tWheel->SetMesh(szFolder, const_cast<char*>(tStr.c_str()));
//		AddChild(tWheel);
//	}

}

void Car::WheelRender()
{
	
}

void Car::KeyEvent()
{
}
