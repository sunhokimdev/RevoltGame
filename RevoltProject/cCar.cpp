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
	m_wheelAcc = wheelAcc;

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
	GetMeshData()->LoadCarMesh("Cars/" + carName, carName + ".obj");
}

void cCar::Update()
{
	if (m_carNxVehicle)
	{
		NxVec3 pos = m_carNxVehicle->getGlobalPose().t;
		m_carNxVehicle->getActor()->addForce(NxVec3(0, -0.001, 0));

		float targetPower = 0.f;
		bool power = false;
		if (g_pKeyManager->isStayKeyDown(VK_UP))
		{
			m_moterPower += m_moterAcc;
			if (m_moterPower > 1.f) m_moterPower = 1.f;
			targetPower = m_moterPower * m_maxMoterPower;
			power = true;
		}
		if (g_pKeyManager->isStayKeyDown(VK_DOWN))
		{
			m_moterPower -= m_moterAcc;
			if (m_moterPower < -1.f) m_moterPower = -1.f;
			targetPower = m_moterPower * m_maxMoterPower;
			power = true;
		}
		if (!power)
		{
			m_moterPower = 0.f;
			targetPower = m_moterPower * m_maxMoterPower;
		}

		float targetAngle = m_wheelAngle * m_maxWheelAngle;
		bool handle = false;
		if (g_pKeyManager->isStayKeyDown(VK_LEFT))
		{
			m_wheelAngle += (m_wheelAcc);
			if (m_wheelAngle > 1.f) m_wheelAngle = 1.f;
			targetAngle = m_wheelAngle * m_maxWheelAngle;
			handle = true;
		}
		if (g_pKeyManager->isStayKeyDown(VK_RIGHT))
		{
			m_wheelAngle -= (m_wheelAcc);
			if (m_wheelAngle < -1.f) m_wheelAngle = -1.f;
			targetAngle = m_wheelAngle * (m_maxWheelAngle);
			handle = true;
		}
		if (!handle)
		{
			if (abs(m_wheelAngle) <= m_wheelAcc*2) m_wheelAngle = 0.0f;
			else if (m_wheelAngle > 0) m_wheelAngle -= m_wheelAcc*2;
			else if (m_wheelAngle < 0) m_wheelAngle += m_wheelAcc*2;

			targetAngle = m_wheelAngle * m_maxWheelAngle;
		}


		for (int i = 0; i < 4; i++)
		{
			NxWheel* wheel = m_carNxVehicle->getWheel(i);
			if (i < 2)
			{
				float value = (1 - (wheel->getRpm() / m_maxRpm));
				if (value < 0.5) value = 0.5f;
				wheel->setAngle(targetAngle * value);
			}
			if (wheel->getRpm() < m_maxRpm)
				wheel->tick(false, targetPower, 100.f, 1.f / 60.f);
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
