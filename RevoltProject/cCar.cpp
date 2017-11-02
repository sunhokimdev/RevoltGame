#include "stdafx.h"
#include "cCar.h"
#include "cWheel.h"
#include "cAI.h"

cCar::cCar()
{

}


cCar::~cCar()
{

}

void cCar::SetCarValue(float maxRpm, float moterPower, float moterAcc, float breakPower, float wheelAngle, float wheelAcc, bool isAI)
{
	m_maxRpm = maxRpm;
	m_maxMoterPower = moterPower;
	m_moterAcc = moterAcc;
	//	m_breakPower = breakPower;
	m_maxWheelAngle = wheelAngle;
	m_wheelAcc = wheelAcc;

	m_wheelAngle = 0;
	m_moterPower = 0;

	m_isAI = isAI;

	m_vecAI.clear();
	if (isAI)
	{
		m_vecAI.push_back(new cAI);
	}
}
void cCar::CreatePhsyX()
{
	USERDATA* pUserdata = new USERDATA(E_PHYSX_TAG_CAR);
	m_carNxVehicle = MgrPhysX->createCarWithDesc(NxVec3(0, 1, 0), pUserdata, true, true);
	if (m_carNxVehicle)
	{
		cPhysX* physX = new cPhysX;
		physX->m_pActor = m_carNxVehicle->getActor();
		physX->m_pUserData = (USERDATA*)m_carNxVehicle->userData;

		SetPhysXData(physX);
		physX->SetPosition(NxVec3(0, 0, 0));
	}

}

void cCar::LoadMesh(std::string carName)
{
	GetMeshData()->LoadCarMesh("Cars/" + carName, carName + ".obj");


}

void cCar::Update()
{
	if (m_isAI)
	{
		CtrlAI();
	}
	else
	{
		CtrlPlayer();
	}
}

void cCar::LastUpdate()
{
	if (GetPhysXData())
	{
		//물리데이터와 메쉬 데이터동기화

		NxVec3 pos = GetPhysXData()->m_pActor->getGlobalPosition();
		D3DXVECTOR3 dPos;
		dPos.x = pos.x;
		dPos.y = pos.y;
		dPos.z = pos.z;

		NxF32 NxMat[9] = { 1,0,0,0,1,0,0,0,1 };
		GetPhysXData()->m_pActor->getGlobalPose().M.getColumnMajor(NxMat);

		cTransform::SetQuaternion(NxMat);
		cTransform::SetPosition(dPos + cTransform::GetUpVec() * 0.2f);
	}
}

void cCar::Render()
{
	Object::Render();
	if (m_isAI)
	{
		for each (cAI* pAI in m_vecAI)
		{
			pAI->Update();
		}
	}
}

void cCar::Destory()
{

	Object::Destroy();
}

void cCar::CtrlPlayer()
{
	if (m_carNxVehicle)
	{
		NxVec3 pos = m_carNxVehicle->getGlobalPose().t;
		m_carNxVehicle->getActor()->addForce(NxVec3(0, -0.001, 0));

		float targetPower = 0.f;
		bool power = false;
		m_breakPower = 0.f;
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
			m_breakPower = m_maxMoterPower;
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
			if (abs(m_wheelAngle) <= m_wheelAcc * 2) m_wheelAngle = 0.0f;
			else if (m_wheelAngle > 0) m_wheelAngle -= m_wheelAcc * 2;
			else if (m_wheelAngle < 0) m_wheelAngle += m_wheelAcc * 2;

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
			if (wheel->getRpm() < m_maxRpm)	wheel->tick(false, targetPower, m_breakPower, 1.f / 60.f);
			else wheel->tick(false, 0, m_breakPower, 1.f / 60.f);
		}

	}
}

void cCar::CtrlAI()
{
	for each (cAI* pAI in m_vecAI)
	{
		pAI->Update();
	}
}

void cCar::GetRpm()
{
	float rpm;
}
