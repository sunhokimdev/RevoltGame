#include "stdafx.h"
#include "cCar.h"
#include "cWheel.h"
#include "cAI.h"
#include "cPhysXManager.h"
#include "cTrack.h"

#include <fstream>

cCar::cCar()
{
	countTrack = -1;
	countTrack = -1;
	m_rapTimeCount = 0.f;
	m_totlaTimeCount = 0.f;

	isFliping = false;
}

cCar::~cCar()
{

}

void cCar::LoadCar(std::string carName)
{
	std::string FullPath = "Cars/" + carName + "/" + carName + ".car";

	std::fstream LOAD;
	LOAD.open(FullPath);

	if (LOAD.is_open())
	{
		char szTemp[1024];

		while (1)
		{
			if (LOAD.eof()) break;

			LOAD >> szTemp;


			if (strcmp(szTemp, " ") == 0 || strcmp(szTemp, "\n") == 0)
			{
				continue;
			}
			else if (strcmp(szTemp, "NAME") == 0)
			{
				LOAD >> szTemp;

				LoadMesh(szTemp);
				LoadWheel(szTemp);
			}
			else if (strcmp(szTemp, "SPECIFICATION") == 0)
			{
				float maxRpm;
				float moterPower;
				float moterAcc;
				float breakPower;
				float wheelAngle;
				float wheelAcc;

				while (1)
				{
					LOAD >> szTemp;

					if (strcmp(szTemp, "MaxRPM") == 0)
					{
						LOAD >> szTemp;
						maxRpm = atof(szTemp);
					}
					else if (strcmp(szTemp, "MoterPower") == 0)
					{
						LOAD >> szTemp;
						moterPower = atof(szTemp);
					}
					else if (strcmp(szTemp, "MoterAcc") == 0)
					{
						LOAD >> szTemp;
						moterAcc = atof(szTemp);
					}
					else if (strcmp(szTemp, "BreakPower") == 0)
					{
						LOAD >> szTemp;
						breakPower = atof(szTemp);
					}
					else if (strcmp(szTemp, "WheelAngle") == 0)
					{
						LOAD >> szTemp;
						wheelAngle = NxPi*atof(szTemp);
					}
					else if (strcmp(szTemp, "WheelAcc") == 0)
					{
						LOAD >> szTemp;
						wheelAcc = atof(szTemp);
					}
					else if (strcmp(szTemp, "#") == 0)
					{
						break;
					}
				} // while
				SetCarValue(maxRpm, moterPower, moterAcc, breakPower, wheelAngle, wheelAcc);
			}
			else if (strcmp(szTemp, "MODEL") == 0)
			{
				stCARSPEC spec;
				ZeroMemory(&spec, sizeof(stCARSPEC));
				while (1)
				{
					LOAD >> szTemp;

					if (strcmp(szTemp, "BOX") == 0)
					{
						NxBoxShapeDesc boxDesc;
						while (1)
						{

							LOAD >> szTemp;

							if (strcmp(szTemp, "Dimensions") == 0)
							{
								LOAD >> szTemp;
								float x = atof(szTemp);
								LOAD >> szTemp;
								float y = atof(szTemp);
								LOAD >> szTemp;
								float z = atof(szTemp);

								boxDesc.dimensions.set(x, y, z);
							}
							else if (strcmp(szTemp, "LocalPose") == 0)
							{
								LOAD >> szTemp;
								float x = atof(szTemp);
								LOAD >> szTemp;
								float y = atof(szTemp);
								LOAD >> szTemp;
								float z = atof(szTemp);

								boxDesc.localPose.t.set(x, y, z);
							}
							else if (strcmp(szTemp, "MaterialIndex") == 0)
							{
								LOAD >> szTemp;

								boxDesc.materialIndex = atoi(szTemp);
							}
							else if (strcmp(szTemp, "#") == 0)
							{
								spec.vecBoxDesc.push_back(boxDesc);
								break;
							}
						} // while
					}
					else if (strcmp(szTemp, "WHEEL") == 0)
					{
						D3DXVECTOR3 pos;
						while (1)
						{
							LOAD >> szTemp;
							if (strcmp(szTemp, "Position") == 0)
							{
								LOAD >> szTemp;
								pos.x = atof(szTemp);
								LOAD >> szTemp;
								pos.y = atof(szTemp);
								LOAD >> szTemp;
								pos.z = atof(szTemp);

								spec.vecWheelPos.push_back(pos);
							}
							else if (strcmp(szTemp, "#") == 0)
							{
								break;
							}
						} // while;
					}
					else if (strcmp(szTemp, "#") == 0)
					{
						break;
					}
				} // while

				CreatePhsyX(spec);
			}
		} // << while
	}
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
	m_eHoldItem = ITEM_NONE;
	m_nItemCount = 0;
	m_isAI = isAI;

	m_vecAI.clear();
	if (isAI)
	{
		m_vecAI.push_back(new cAI);
	}
}
void cCar::CreateItem()
{
	if (!m_eHoldItem)
	{
		while (1)
		{
			m_eHoldItem = eITEM_LIST(rand() % (eITEM_LIST::ITEM_LAST));
			if (m_eHoldItem) break;
		}
		m_nItemCount = 1;
	}
}
void cCar::CreatePhsyX(stCARSPEC carspec)
{
	USERDATA* pUserdata = new USERDATA(E_PHYSX_TAG_CAR);
	m_carNxVehicle = MgrPhysX->createCarWithDesc(NxVec3(0, 1, 0), carspec, pUserdata, true, true);
	if (m_carNxVehicle)
	{
		cPhysX* physX = new cPhysX;
		physX->m_pActor = m_carNxVehicle->getActor();
		physX->m_pUserData = (USERDATA*)m_carNxVehicle->getActor()->userData;

		SetPhysXData(physX);
		physX->SetPosition(NxVec3(0, 0, 0));
	}
}
void cCar::LoadMesh(std::string carName)
{
	GetMeshData()->LoadCarMesh("Cars/" + carName, carName + ".obj");
}

void cCar::LoadWheel(std::string carName)
{
	if (vecWheels.empty())
	{
		vecWheels.push_back(new cMesh);
		vecWheels.push_back(new cMesh);
		vecWheels.push_back(new cMesh);
		vecWheels.push_back(new cMesh);
	}
	else
	{
		for each(cMesh* p in vecWheels)
		{
			p->Destory();
		}
		vecWheels.clear();
	}

	vecWheels[0]->LoadMesh("Cars/" + carName, carName + "fl.obj");
	vecWheels[1]->LoadMesh("Cars/" + carName, carName + "fr.obj");
	vecWheels[2]->LoadMesh("Cars/" + carName, carName + "bl.obj");
	vecWheels[3]->LoadMesh("Cars/" + carName, carName + "br.obj");
}

void cCar::Update()
{
	if (m_isAI) CtrlAI();
	else CtrlPlayer();

	//이하 AI, PLAYER 의 동일 사용 함수

	// PickUp 충돌
	if (GetPhysXData()->m_pUserData->IsPickUp == NX_TRUE)
	{
		if (m_eHoldItem == ITEM_NONE)
		{
			CreateItem();
			std::cout << m_eHoldItem << " - " << m_nItemCount << std::endl;
			//GetPhysXData()->m_pUserData->IsPickUp == NX_FALSE;
		}
	}

	//스피드 계산
	// : >>
	float Dist = 0;

	// 과거 위치값
	for (int i = 3; i >= 0; i--)
	{
		D3DXVECTOR3 pos1 = m_szPrevPos[i];
		D3DXVECTOR3 pos2 = m_szPrevPos[i + 1];

		D3DXVECTOR3 vecDist = pos1 - pos2;
		Dist += D3DXVec3Length(&vecDist);

		m_szPrevPos[i + 1] = m_szPrevPos[i];
	}
	m_position = {
		GetNxVehicle()->getGlobalPose().t.x,
		GetNxVehicle()->getGlobalPose().t.y,
		GetNxVehicle()->getGlobalPose().t.z };
	m_szPrevPos[0] = m_position;

	m_fCurrentSpeed = (Dist * 0.25f) * 200.f;

	TrackCheck();

	CarFlip();


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

	//바퀴 동기화
	for (int i = 0; i < vecWheels.size(); i++)
	{
		D3DXMATRIXA16 matW, matR, matT;
		D3DXMatrixIdentity(&matW);
		D3DXMatrixIdentity(&matR);
		D3DXMatrixIdentity(&matT);

		NxWheel* pWheel = m_carNxVehicle->getWheel(i);
		NxVec3 NxWheelPos = pWheel->getWheelPos();// +pWheel->getWheelShape()->getActor().getGlobalPosition();

		if (NxWheelPos.z < 0) NxWheelPos.z += 0.1f;
		else NxWheelPos.z -= 0.1f;
		NxWheelPos.y -= 0.2;

		D3DXMatrixTranslation(&matT, NxWheelPos.x, NxWheelPos.y, NxWheelPos.z);

		//NxF32 mat9[9] = { 1,0,0,0,1,0,0,0,1 };
		//NxMat33 NxWheelMat = pWheel->getWheelShape()->getActor().getGlobalOrientation();
		//NxWheelMat.getColumnMajor(mat9);
		//
		//matR._11 = mat9[0];
		//matR._12 = mat9[1];
		//matR._13 = mat9[2];
		//matR._21 = mat9[3];
		//matR._22 = mat9[4];
		//matR._23 = mat9[5];
		//matR._31 = mat9[6];
		//matR._32 = mat9[7];
		//matR._33 = mat9[8];

		if(i<2)	D3DXMatrixRotationY(&matR, -(D3DX_PI*0.5 + (m_wheelAngle * m_maxWheelAngle)));
		else D3DXMatrixRotationY(&matR, -D3DX_PI*0.5);
		matW = matR * matT;

		MgrD3DDevice->SetTransform(D3DTS_WORLD, &(matW * cTransform::GetMatrix(false,true,true)));
		vecWheels[i]->Render();
	}


	if (m_isAI)
	{
		for each (cAI* pAI in m_vecAI)
		{
			pAI->Render();
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

		//엑셀
		float targetPower = 0.f;
		bool power = false;
		m_breakPower = 0.f;
		if (g_pKeyManager->isStayKeyDown(KEY_ACCELERATOR))
		{
			m_moterPower += m_moterAcc;
			if (m_moterPower > 1.f) m_moterPower = 1.f;
			targetPower = m_moterPower * m_maxMoterPower;
			power = true;
		}
		if (g_pKeyManager->isStayKeyDown(KEY_REVERSE))
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
			m_breakPower = m_maxMoterPower*0.5f;
		}

		//핸들
		float targetAngle = m_wheelAngle * m_maxWheelAngle;
		bool handle = false;
		if (g_pKeyManager->isStayKeyDown(KEY_MOVE_LEFT))
		{
			m_wheelAngle += (m_wheelAcc);
			if (m_wheelAngle > 1.f) m_wheelAngle = 1.f;
			targetAngle = m_wheelAngle * m_maxWheelAngle;
			handle = true;
		}
		if (g_pKeyManager->isStayKeyDown(KEY_MOVE_RIGHT))
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

		//이동
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

		//아이템사용
		if (g_pKeyManager->isOnceKeyDown(KEY_FIRE_ITEM))
		{
			if (m_eHoldItem != ITEM_NONE)
			{
				//아이템 사용 함수 호츨
				g_pItemManager->FireItem(m_eHoldItem);
				m_nItemCount--;
				if (m_nItemCount == 0)
				{
					m_eHoldItem = ITEM_NONE;
					GetPhysXData()->m_pUserData->IsPickUp = NX_FALSE;
				}
				std::cout << "FIRE!" << std::endl;
			}
		}

		//RePosition
		if (g_pKeyManager->isOnceKeyDown(KEY_REPOSITION))
		{
			CarRunStop();
			if (countTrack == -1)
			{
				GetPhysXData()->SetPosition(D3DXVECTOR3(0, 1, 0));
			}
			else
			{
				if (countCheckBox != 0)
				{
					int count = 0;
					MAP_STR_OBJ_iter iterBegin;
					MAP_STR_OBJ_iter iterEnd;
					//std::map<std::string, Object*>::iterator 
					//std::map<std::string, Object*>::iterator iterEnd;
					iterBegin = m_pTrack->GetCheckBoxsPt()->begin();
					iterEnd = m_pTrack->GetCheckBoxsPt()->end();
					for (; iterBegin != iterEnd; iterBegin++)
					{
						if ((countCheckBox - 1) == count)
						{
							D3DXVECTOR3 pos = iterBegin->second->GetPosition();
							pos.y = 1;
							GetPhysXData()->SetPosition(pos);
							break;
						}
						count++;
					}
				}
				else // 마지막 체크박스
				{
					MAP_STR_OBJ_iter iterEnd = m_pTrack->GetCheckBoxsPt()->end();
					iterEnd--;

					D3DXVECTOR3 pos = iterEnd->second->GetPosition();
					pos.y = 1;
					GetPhysXData()->SetPosition(pos);
				}
			}
		}

		//Fliping
		NxQuat quat = GetPhysXData()->m_pActor->getGlobalOrientationQuat();
		NxVec3 carUp = quat.transform(NxVec3(0, 1, 0), NxVec3(0, 0, 0));
		if (carUp.y < 0.0f)
		{
			if (g_pKeyManager->isOnceKeyDown(KEY_CAR_FLIP) && isFliping == false)
			{
				isFliping = true;
				CarRunStop();
			}
		}
	}
}

void cCar::CtrlAI()
{
	for each (cAI* pAI in m_vecAI)
	{
		if (m_carNxVehicle) pAI->Update();
	}
}

void cCar::GetRpm()
{
	float rpm;
}

void cCar::TrackCheck()
{
	//체크박스 및 트랙 카운터
	if (GetPhysXData()->m_pUserData->CheckBoxID == 0)
	{
		m_trackOn = true;
	}
	if (GetPhysXData()->m_pUserData->CheckBoxID == 1)
	{
		if (m_trackOn)
		{
			countTrack++;
			m_rapTimeCount = 0.f;
		}
		m_trackOn = false;
	}
	if (countCheckBox == GetTotalCheckBoxNum()) GetPhysXData()->m_pUserData->CheckBoxID = 0;
	countCheckBox = GetPhysXData()->m_pUserData->CheckBoxID;

	if (countTrack > -1 && countTrack < 3)
	{
		//시간을 더해 나간다.
		m_rapTimeCount += 0;
		m_totlaTimeCount += 0;
	}
}

void cCar::RunEnd()
{
	for (int i = 0; i < 4; i++)
	{
		NxWheel* wheel = m_carNxVehicle->getWheel(i);
		if (wheel->getRpm() < m_maxRpm)	wheel->tick(false, 0, m_maxMoterPower, 1.f / 60.f);
	}
}

void cCar::CarFlip()
{
	if (isFliping)
	{
		CarRunStop();

		NxQuat quat = m_carNxVehicle->getActor()->getGlobalOrientationQuat();
		NxVec3 carFront = quat.transform(NxVec3(1, 0, 0), NxVec3(0, 0, 0));
		NxF32 angle = carFront.dot(NxVec3(1, 0, 0));
		angle = acosf(angle);

		NxVec3 arrow = carFront.cross(NxVec3(1, 0, 0));
		if (arrow.y > 0)
		{
			angle *= -1;
		}

		NxQuat quat_;
		quat.zero();
		quat.fromAngleAxisFast(angle, NxVec3(0, 1, 0));

		NxActor* p = m_carNxVehicle->getActor();
		p->setGlobalOrientationQuat(quat);

		NxVec3 carPos = p->getGlobalPose().t;
		p->getGlobalPose().t.add(carPos, NxVec3(0, 3, 0));

		isFliping = false;
	}
}

void cCar::CarRunStop()
{
	if (GetPhysXData())
	{
		GetPhysXData()->m_pActor->putToSleep();
		for (int i = 0; i < 4; i++)
		{
			m_carNxVehicle->getWheel(i)->getWheelShape()->getActor().putToSleep();
		}
	}
}
