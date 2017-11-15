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

void Car::Destroy()
{

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
	std::string tStr;
	ObjectLoader load;

	{
		Thing* tWheel = new Car;
		tStr = std::string(szName) + std::string("fl.obj");
		tWheel->SetPosition(-0.209999993, 0.0399999991, 0.340000004);
		tWheel->SetMesh(szFolder, const_cast<char*>(tStr.c_str()));
		AddChild(tWheel);
	}

	{
		Thing* tWheel = new Thing;
		tStr = std::string(szName) + std::string("fr.obj");
		tWheel->SetPosition(0.209999993, 0.0399999991, 0.340000004);
		tWheel->SetMesh(szFolder, const_cast<char*>(tStr.c_str()));
		AddChild(tWheel);
	}

	{
		Thing* tWheel = new Thing;
		tStr = std::string(szName) + std::string("bl.obj");
		tWheel->SetPosition(-0.209999993, 0.0399999991, -0.444999993);
		tWheel->SetMesh(szFolder, const_cast<char*>(tStr.c_str()));
		AddChild(tWheel);
	}

	{
		Thing* tWheel = new Thing;
		tStr = std::string(szName) + std::string("br.obj");
		tWheel->SetPosition(0.209999993, 0.0399999991, -0.444999993);
		tWheel->SetMesh(szFolder, const_cast<char*>(tStr.c_str()));
		AddChild(tWheel);
	}
}

void Car::WheelRender()
{
	
}

void Car::KeyEvent()
{
}
