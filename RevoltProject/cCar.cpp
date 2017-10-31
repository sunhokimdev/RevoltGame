#include "stdafx.h"
#include "cCar.h"
#include "cWheel.h"

cCar::cCar()
{

}


cCar::~cCar()
{

}

void cCar::SetCarValue(float moterPower, float moterAcc, float breakPower, float wheelAngle, float wheelAcc)
{
	m_maxMoterPower = moterPower;
	m_moterAcc = moterAcc;
	//	m_breakPower = breakPower;
	m_maxWheelAngle = wheelAngle;
	m_wheelAcc - wheelAcc;

	m_wheelAngle = 0;
	m_moterPower = 0;
}
void cCar::CreatePhsyX()
{
	m_carNxVehicle = MgrPhysX->createCarWithDesc(NxVec3(0, 0, 0), true, true);
	if (m_carNxVehicle)
	{
		cPhysX* physX = new cPhysX;
		physX->m_pActor = m_carNxVehicle->getActor();
		physX->m_pUserData = new USERDATA();

		SetPhysXData(physX);
	}
}

void cCar::LoadMesh(std::string carName)
{
	//GetMeshData()->LoadMesh("Cars/" + carName, carName + ".obj");
	GetMeshData()->LoadCarMesh("Cars/" + carName, carName + ".obj");
}

void cCar::Update()
{
	if (m_carNxVehicle)
	{
		NxVec3 pos = m_carNxVehicle->getGlobalPose().t;

		float targetAngle = 0;
		if (g_pKeyManager->isStayKeyDown(VK_LEFT))
		{
			m_wheelAngle -= m_wheelAcc;
			if (m_wheelAngle < -1.f) m_wheelAngle = -1.f;

			targetAngle -= m_maxWheelAngle;
		}
		if (g_pKeyManager->isStayKeyDown(VK_RIGHT))
		{
			m_wheelAngle += m_wheelAcc;
			if (m_wheelAngle > 1.f) m_wheelAngle = 1.f;

			targetAngle += m_maxWheelAngle;
		}
		targetAngle = m_wheelAngle * targetAngle;


		float targetPower = 0;
		if (g_pKeyManager->isStayKeyDown(VK_UP))
		{
			m_moterPower += m_moterAcc;
			if (m_moterPower > 1.f) m_moterPower = 1.f;

			targetPower += m_maxMoterPower;
		}
		if (g_pKeyManager->isStayKeyDown(VK_DOWN))
		{
			m_moterPower -= m_moterAcc;
			if (m_moterPower < -1.f) m_moterPower = -1.f;

			targetPower -= m_maxMoterPower;
		}
		targetPower = m_moterPower * targetPower;

		m_carNxVehicle->getActor()->addForce(NxVec3(0, -0.001, 0));

		for (int i = 0; i < 4; i++)
		{
			NxWheel* wheel = m_carNxVehicle->getWheel(i);
			if (i < 2)
			{
				wheel->setAngle(targetAngle);
			}
			wheel->tick(false, targetPower, 0, 1.f / 60.f);


			if (i == 0 || i == 2)//ÁÂÃø
			{
			//	m_carNxVehicle->getActor()->addLocalTorque(NxVec3(10, 0, 0));
			}
			else//¿ìÃø
			{

			}
		}

	}
}

void cCar::LastUpdate()
{
	Object::LastUpdate();
}

void cCar::Render()
{

	Object::Render();
}

void cCar::Destory()
{

	Object::Destroy();
}
