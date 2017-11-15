#include "stdafx.h"
#include "cCar.h"
#include "cWheel.h"
#include "cAI_Master.h"
#include "cPhysXManager.h"
#include "cTrack.h"
#include "cSkidMark.h"
#include "cCheckBox.h"
#include "InGameUI.h"

#include <fstream>

/// 프러스텀에 정확하게 포함되지 않더라도, 약간의 여분을 주어서 프러스텀에 포함시키기 위한 값
#define PLANE_EPSILON	5.0f

cCar::cCar()
	:m_pSkidMark(NULL)
{
	m_countRapNum = -1;
	m_currCheckBoxID = -1;
	m_aICheckBoxID = 0;
	m_rapTimeCount = 0.f;
	m_totlaTimeCount = 0.f;
	m_bastRapTimeCount = -1.0f;
	isFliping = false;
	m_nextCheckBoxID = 0;
	m_eHoldItem = ITEM_NONE;

	familyAI = NULL;

	m_isCtl = false;
	m_isDrift = false;
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
						wheelAcc = atof(szTemp) * 0.8f;
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
	else
	{
		MessageBoxA(g_hWnd, "*.car 파일을 찾을 수 없습니다.", "파일 없음", MB_OK);
	}

	m_pSkidMark = new cSkidMark;
	m_pSkidMark->LinkCar(this);

	m_strMotorKey = "moto." + std::to_string(m_nPlayerID);
	m_strDriftKey = "skid_normal." + std::to_string(m_nPlayerID);

	g_pSoundManager->Play(m_strMotorKey, 0.0f, GetPosition());
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

}

void cCar::SetAI(bool isAI, AI_DATA aidata)
{
	m_isAI = isAI;

	if (isAI)
	{

		if (familyAI)
		{
			familyAI->Destory();
			SAFE_DELETE(familyAI);
		}

		familyAI = new cAI_Master;
		familyAI->Setup(aidata);
	}
}

void cCar::CreateItem()
{
	if (!m_eHoldItem)
	{
		while (1)
		{
			srand(time(NULL));
			m_eHoldItem = eITEM_LIST(rand() % (eITEM_LIST::ITEM_LAST));

			/*TEST*///m_eHoldItem = eITEM_LIST::ITEM_WBOMB;

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

		physX->m_pUserData->CheckBoxID = -1;

		SetPhysXData(physX);
		physX->SetPosition(NxVec3(0, 0, 0));
		physX->m_pActor->setGroup(3);
		physX->m_pUserData->isMyBomb = false;
		physX->m_pUserData->m_pCarPosion = &physX->m_pActor->getGlobalPosition();
	}
}

void cCar::LoadMesh(std::string carName)
{
	SetMeshData(new cMesh);
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
			p->Destroy();
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
	//차가 땅에 박히는 걸 방지
	m_carNxVehicle->getActor()->addForce(NxVec3(0, 0.001, 0));

	if (m_isCtl)
	{
		if (m_isAI) CtrlAI();
		else CtrlPlayer();
		//if (g_pKeyManager->isStayKeyDown(VK_TAB))
		//{
		//	CtrlPlayer();
		//}
		//이하 AI, PLAYER 의 동일 사용 함수

		//자동차 움직임
		CarMove();

		//자동차 리포지션
		if (INPUT_KEY[E_BIT_REPOS]) RePosition();

		//아이템 사용
		if (INPUT_KEY[E_BIT_ITEM_]) UsedItem();

		//차 뒤집기
		if (INPUT_KEY[E_BIT_FLIP_]) CarFlip();
	}

	// PickUp 충돌
	CollidePickUp();

	//스피드 계산
	SpeedMath();

	//트랙 체크
	TrackCheck();

	//바퀴 자국
	CreateSkidMark();

	UpdateSound();
}

void cCar::LastUpdate()
{
	if (GetPhysXData())
	{
		//물리데이터와 자동차 동기화
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

	//물리데이터와 바퀴 동기화
	for (int i = 0; i < vecWheels.size(); i++)
	{
		D3DXMATRIXA16 matW, matR, matT;
		D3DXMatrixIdentity(&matW);
		D3DXMatrixIdentity(&matR);
		D3DXMatrixIdentity(&matT);

		NxWheel* pWheel = m_carNxVehicle->getWheel(i);
		NxVec3 NxWheelPos = pWheel->getWheelPos();

		if (NxWheelPos.z < 0) NxWheelPos.z += 0.1f;
		else NxWheelPos.z -= 0.1f;
		NxWheelPos.y -= 0.2;

		D3DXMatrixTranslation(&matT, NxWheelPos.x, NxWheelPos.y, NxWheelPos.z);

		if (i < 2)	D3DXMatrixRotationY(&matR, -(D3DX_PI*0.5 + (m_wheelAngle * m_maxWheelAngle)));
		else D3DXMatrixRotationY(&matR, -D3DX_PI*0.5);
		matW = matR * matT;

		MgrD3DDevice->SetTransform(D3DTS_WORLD, &(matW * cTransform::GetMatrix(false, true, true)));
		vecWheels[i]->Render();
	}


	//if (m_isAI)
	//{
	if (familyAI) familyAI->Render();
	//}

	if (m_pSkidMark)
	{
		m_pSkidMark->Render();
	}
}

void cCar::Destroy()
{
	if (m_pSkidMark) m_pSkidMark->Destroy();
	SAFE_DELETE(m_pSkidMark);
	SAFE_DELETE(m_carNxVehicle);

	for each(cMesh* p in vecWheels)
	{
		p->Destroy();
		SAFE_DELETE(p);
	}
	vecWheels.clear();

	if (familyAI)
	{
		familyAI->Destory();
		SAFE_DELETE(familyAI);
	}

	Object::Destroy();
	m_pInGameUI = NULL;
	m_pTrack = NULL;
	g_pSoundManager->AllSoundIsStop();
}

void cCar::CtrlPlayer()
{
	if (m_carNxVehicle)
	{
		if (!m_isUser)
		{
			INPUT_KEY.reset();
			INPUT_KEY[E_BIT_UP___] = g_pKeyManager->isStayKeyDown(KEY_ACCELERATOR);
			INPUT_KEY[E_BIT_DOWN_] = g_pKeyManager->isStayKeyDown(KEY_REVERSE);
			INPUT_KEY[E_BIT_LEFT_] = g_pKeyManager->isStayKeyDown(KEY_MOVE_LEFT);
			INPUT_KEY[E_BIT_RIGHT] = g_pKeyManager->isStayKeyDown(KEY_MOVE_RIGHT);
			INPUT_KEY[E_BIT_ITEM_] = g_pKeyManager->isOnceKeyDown(KEY_FIRE_ITEM);
			INPUT_KEY[E_BIT_REPOS] = g_pKeyManager->isOnceKeyDown(KEY_REPOSITION);
			INPUT_KEY[E_BIT_FLIP_] = g_pKeyManager->isOnceKeyDown(KEY_CAR_FLIP);
		}
	}
}

void cCar::CtrlAI()
{
	if (m_carNxVehicle)
		if (familyAI)
			familyAI->Update();
}

float cCar::GetRpm()
{
	float p1 = GetNxVehicle()->getWheel(0)->getRpm();
	float p2 = GetNxVehicle()->getWheel(1)->getRpm();
	float p3 = GetNxVehicle()->getWheel(2)->getRpm();
	float p4 = GetNxVehicle()->getWheel(3)->getRpm();

	float pValue = p1 + p2 + p3 + p4;
	return pValue * 0.25;
}

float cCar::GetRpmRate()
{
	return GetRpm() / m_maxRpm;
}

void cCar::TrackCheck()
{
	//체크박스 및 트랙 카운터
	int checkId = GetPhysXData()->m_pUserData->CheckBoxID;
	m_aICheckBoxID = (checkId == -1) ? 0 : checkId;
	//	m_nextDir = ((cCheckBox*)(m_pTrack->GetCheckBoxs()[m_aICheckBoxID]))->ToNextCheckBoxDir();

		//시작 체크
	if (m_currCheckBoxID == -1)
	{
		if (checkId == (*m_pTrack->GetCheckBoxsPt())[0]->GetPhysXData()->m_pUserData->CheckBoxID)
		{
			std::cout << "START" << std::endl;
			m_nextCheckBoxID = 1;
			m_currCheckBoxID = 0;	//체크 시작
			m_countRapNum = 0;
			m_rapTimeCount = 0.f;

			if (!m_isAI)
			{
				std::cout << m_isAI << std::endl;
				m_pInGameUI->SetLabCnt(m_countRapNum);
			}
			cCheckBox* nextCheckBox = (cCheckBox*)m_pTrack->GetCheckBoxs()[GetCurrCheckBoxID()];

		}
		return;
	}

	cCheckBox* pCheckBox = (cCheckBox*)(*m_pTrack->GetCheckBoxsPt())[m_nextCheckBoxID];
	int checkNextId = pCheckBox->GetPhysXData()->m_pUserData->CheckBoxID;

	//충돌한 정보와 다음 체크박스 정보가 일치하는 지 확인
	if (checkId == checkNextId)
	{

		cCheckBox* pCheckBox = (cCheckBox*)(*m_pTrack->GetCheckBoxsPt())[m_nextCheckBoxID];
		m_currCheckBoxID = m_nextCheckBoxID;
		m_nextCheckBoxID = pCheckBox->GetNextCheckBox()->GetPhysXData()->m_pUserData->CheckBoxID;

		//	m_nextDir = ((cCheckBox*)(*m_pTrack->GetCheckBoxsPt())[GetCurrCheckBoxID()])->ToNextCheckBoxDir();

		if (m_currCheckBoxID == 0)
		{
			m_countRapNum++;
			if (!m_isAI)
			{
				m_pInGameUI->SetLabCnt(m_countRapNum);
				m_pInGameUI->UpdateLastTime();
				m_pInGameUI->CompareBestTime();
				m_pInGameUI->SetLabElapseTime(0);
				m_pInGameUI->SetLabMinOneth(FONT2_NUM0);
				m_pInGameUI->SetLabMinTenth(FONT2_NUM0);
			}

			if (m_bastRapTimeCount > m_rapTimeCount || m_bastRapTimeCount < 0.0f)
			{
				m_bastRapTimeCount = m_rapTimeCount;

			}
			m_rapTimeCount = 0.f;
		}
	}
	//시간을 더해 나간다.
	if (m_countRapNum < 3)
	{
		m_rapTimeCount += g_pTimeManager->GetElapsedTime();
		m_totlaTimeCount += g_pTimeManager->GetElapsedTime();
	}
}

void cCar::RunEnd()
{
	for (int i = 0; i < 4; i++)
	{
		NxWheel* wheel = m_carNxVehicle->getWheel(i);
		if (wheel->getRpm() < m_maxRpm)	wheel->tick(false, 0, m_maxMoterPower, 1.f / 60.f);
	}
	UpdateSound();
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

void cCar::DrawSkidMark()
{
	//레이초기화
	NxRay RayCar;
	//RayCar.orig = NxVec3(m_position);
	RayCar.orig = GetPhysXData()->GetPositionToNxVec3();
	RayCar.orig.y += 0.2f;
	RayCar.dir = NxVec3(0, -1, 0);

	NxRaycastHit RayCarHit;
	RayCarHit.shape = NULL;
	g_pPhysXScene->raycastClosestShape(RayCar, NxShapesType::NX_ALL_SHAPES, RayCarHit);

	float rpm = GetNxVehicle()->getWheel(0)->getRpm() / m_maxRpm;
	if (fabsf(rpm) > 0.8f && fabs(m_wheelAngle) > 0.9f)
	{
		if (RayCarHit.shape)
		{
			if (RayCarHit.shape->getActor().getName())
			{
				std::string str = RayCarHit.shape->getActor().getName();
				if (RayCarHit.distance < 0.2f && str == "map")
				{
					m_pSkidMark->DrawSkidMark();
					if (!m_isDrift)
					{
						g_pSoundManager->Play(m_strDriftKey, 0.5f, GetPosition());
						m_isDrift = true;
					}
				}
			}
		}
	}

	else
	{
		m_isDrift = false;
	}
}

void cCar::SpeedMath()
{
	m_szPrevPos[0] = GetPhysXData()->GetPositionToD3DXVec3();
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

	m_szPrevPos[0] = m_position;

	m_fCurrentSpeed = (Dist * 0.25f) * 200.f;
}

void cCar::CreateSkidMark()
{
	if (m_pSkidMark)
	{
		DrawSkidMark();
		m_pSkidMark->Update();
	}
}

void cCar::CollidePickUp()
{
	if (GetPhysXData()->m_pUserData->IsPickUp == NX_TRUE)
	{
		if (m_eHoldItem == ITEM_NONE)
		{
			CreateItem();
			g_pItemManager->SetItemID(m_eHoldItem);
		}
	}
}

void cCar::CarMove()
{
	//엑셀
	float targetPower = 0.f;
	bool power = false;
	m_breakPower = 0.f;
	if (INPUT_KEY[E_BIT_UP___])
	{
		m_moterPower += m_moterAcc;
		if (m_moterPower > 1.f) m_moterPower = 1.f;
		targetPower = m_moterPower * m_maxMoterPower;
		if (GetRpm() < 0) m_breakPower = targetPower;
		power = true;
	}
	if (INPUT_KEY[E_BIT_DOWN_])
	{
		m_moterPower -= m_moterAcc;
		if (m_moterPower < -1.f) m_moterPower = -1.f;
		targetPower = m_moterPower * m_maxMoterPower;
		if (GetRpm() > 0) m_breakPower = -targetPower;
		power = true;
	}
	if (!power)
	{
		m_moterPower = 0.f;
		targetPower = m_moterPower * m_maxMoterPower;
		m_breakPower = targetPower;
	}
	//핸들
	float targetAngle = m_wheelAngle * m_maxWheelAngle;
	bool handle = false;
	if (INPUT_KEY[E_BIT_LEFT_])
	{
		m_wheelAngle += (m_wheelAcc);
		if (m_wheelAngle > 1.f) m_wheelAngle = 1.f;
		targetAngle = m_wheelAngle * m_maxWheelAngle;
		handle = true;
	}
	if (INPUT_KEY[E_BIT_RIGHT])
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
		if (wheel->getRpm() < m_maxRpm)	wheel->tick(false, targetPower, m_breakPower, g_pTimeManager->GetElapsedTime());
		else wheel->tick(false, 0, m_breakPower, g_pTimeManager->GetElapsedTime());
	}
}

void cCar::UsedItem()
{
	if (m_eHoldItem != ITEM_NONE)
	{
		//아이템 사용 함수 호츨

		m_nItemCount--;
		if (m_nItemCount == 0)
		{
			g_pItemManager->FireItem(m_eHoldItem, this);

			m_eHoldItem = ITEM_NONE;
			GetPhysXData()->m_pUserData->IsPickUp = NX_FALSE;
			g_pItemManager->SetItemID(m_eHoldItem);
		}
		std::cout << "FIRE!" << std::endl;
	}
}

void cCar::RePosition()
{
	CarFlip();
	CarRunStop();
	if (m_countRapNum == -1)
	{
		GetPhysXData()->SetPosition(D3DXVECTOR3(0, 1, 0));
	}
	else
	{
		std::vector<Object*>* chexkBox = m_pTrack->GetCheckBoxsPt();
		D3DXVECTOR3 pos(0, 0, 0);
		pos = (*chexkBox)[m_currCheckBoxID]->GetPosition();
		pos.y = 1;
		GetPhysXData()->SetPosition(pos);
	}
}

void cCar::CarFlip()
{
	NxQuat quat = GetPhysXData()->m_pActor->getGlobalOrientationQuat();
	NxVec3 carUp = quat.transform(NxVec3(0, 1, 0), NxVec3(0, 0, 0));
	if (carUp.y > 0.0f) { return; }

	CarRunStop();

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
}

//void cCar::SetFrustum()
//{
//	// : near 
//	m_vecProjVertex.push_back(D3DXVECTOR3(-1, -1, 0)); //
//	m_vecProjVertex.push_back(D3DXVECTOR3(-1, 1, 0)); //
//	m_vecProjVertex.push_back(D3DXVECTOR3(1, 1, 0)); //
//	m_vecProjVertex.push_back(D3DXVECTOR3(1, -1, 0)); //
//	// : far
//	m_vecProjVertex.push_back(D3DXVECTOR3(-1, -1, 1)); //
//	m_vecProjVertex.push_back(D3DXVECTOR3(-1, 1, 1)); //
//	m_vecProjVertex.push_back(D3DXVECTOR3(1, 1, 1)); //
//	m_vecProjVertex.push_back(D3DXVECTOR3(1, -1, 1)); //
//
//	m_vecPlane.resize(6);
//	m_vecWorldVertex.resize(8);
//
//	int a = 1;
//}

void cCar::UpdateFrustum()
{
	D3DXMATRIXA16	matView, matProj;
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION,
		&matProj);
	g_pD3DDevice->GetTransform(D3DTS_VIEW,
		&matView);

	for (size_t i = 0; i < m_vecProjVertex.size(); i++)
	{
		D3DXVec3Unproject(&m_vecWorldVertex[i],
			&m_vecProjVertex[i],
			NULL,
			&matProj,
			&matView,
			NULL
		);
	}

	// Front
	D3DXPlaneFromPoints(&m_vecPlane[0],
		&m_vecWorldVertex[0],
		&m_vecWorldVertex[1],
		&m_vecWorldVertex[2]
	);

	// Back
	D3DXPlaneFromPoints(&m_vecPlane[1],
		&m_vecWorldVertex[6],
		&m_vecWorldVertex[5],
		&m_vecWorldVertex[4]
	);

	// Top
	D3DXPlaneFromPoints(&m_vecPlane[2],
		&m_vecWorldVertex[1],
		&m_vecWorldVertex[5],
		&m_vecWorldVertex[6]
	);

	// Bottom
	D3DXPlaneFromPoints(&m_vecPlane[3],
		&m_vecWorldVertex[0],
		&m_vecWorldVertex[3],
		&m_vecWorldVertex[7]
	);

	// Left
	D3DXPlaneFromPoints(&m_vecPlane[4],
		&m_vecWorldVertex[1],
		&m_vecWorldVertex[0],
		&m_vecWorldVertex[4]
	);

	// Rihgt
	D3DXPlaneFromPoints(&m_vecPlane[5],
		&m_vecWorldVertex[2],
		&m_vecWorldVertex[6],
		&m_vecWorldVertex[7]
	);
}

bool cCar::IsIn(D3DXVECTOR3* pv)
{
	float fDist;

	fDist = D3DXPlaneDotCoord(&m_vecPlane[0], pv);
	if (fDist > PLANE_EPSILON) return FALSE;	// plane의 normal벡터가 Front로 향하고 있으므로 양수이면 프러스텀의 바깥쪽

	fDist = D3DXPlaneDotCoord(&m_vecPlane[1], pv);
	if (fDist > PLANE_EPSILON) return FALSE;	// plane의 normal벡터가 Back로 향하고 있으므로 양수이면 프러스텀의 오른쪽

	fDist = D3DXPlaneDotCoord(&m_vecPlane[2], pv);
	if (fDist > PLANE_EPSILON) return FALSE;	// plane의 normal벡터가 Up로 향하고 있으므로 양수이면 프러스텀의 오른쪽

	fDist = D3DXPlaneDotCoord(&m_vecPlane[3], pv);
	if (fDist > PLANE_EPSILON) return FALSE;	// plane의 normal벡터가 Down로 향하고 있으므로 양수이면 프러스텀의 오른쪽

	fDist = D3DXPlaneDotCoord(&m_vecPlane[4], pv);
	if (fDist > PLANE_EPSILON) return FALSE;	// plane의 normal벡터가 left로 향하고 있으므로 양수이면 프러스텀의 왼쪽

	fDist = D3DXPlaneDotCoord(&m_vecPlane[5], pv);
	if (fDist > PLANE_EPSILON) return FALSE;	// plane의 normal벡터가 right로 향하고 있으므로 양수이면 프러스텀의 오른쪽

	return true;
}
void cCar::UpdateSound()
{
	NxWheel* wheel = m_carNxVehicle->getWheel(0);
	float rpmRatio = fabsf(wheel->getRpm()) / m_maxRpm;

	float frq = 10000 + (rpmRatio * 15000) + (rand() % 1000);
	//std::cout << rpmRatio << std::endl;
	float volume = 0.1f + rpmRatio * 0.4f;
	if(m_nPlayerID == 0) volume = 0.1f + rpmRatio * 0.3f;

	g_pSoundManager->SetPosVolPitch(
		m_strMotorKey,
		GetPosition(),
		volume,
		frq);

	if (m_isDrift)
	{
		g_pSoundManager->SetSoundPosition(m_strDriftKey, GetPosition());
	}
	else
	{
		g_pSoundManager->Stop(m_strDriftKey);
	}
}

NxVec3 cCar::CarArrow(float angle)
{
	NxQuat quat = GetPhysXData()->m_pActor->getGlobalOrientationQuat();

	NxF32 mat9[9] = { 1,0,0,0,1,0,0,0,1 };
	GetPhysXData()->m_pActor->getGlobalPose().M.getColumnMajor(mat9);

	D3DXMATRIXA16 matR;
	D3DXMatrixIdentity(&matR);
	matR._11 = mat9[0];
	matR._12 = mat9[1];
	matR._13 = mat9[2];
	matR._21 = mat9[3];
	matR._22 = mat9[4];
	matR._23 = mat9[5];
	matR._31 = mat9[6];
	matR._32 = mat9[7];
	matR._33 = mat9[8];

	D3DXMATRIXA16 matAngle;
	D3DXMatrixIdentity(&matAngle);
	D3DXMatrixRotationAxis(&matAngle, &D3DXVECTOR3(0, 1, 0), D3DXToRadian(angle));


	D3DXVECTOR3 dir(1, 0, 0);

	D3DXVec3TransformNormal(&dir, &dir, &(matR*matAngle));

	NxVec3 nxDir(dir);
	return nxDir;
}

void cCar::SetResetNetworkKey()
{
	m_keySet.up = false;
	m_keySet.down = false;
	m_keySet.left = false;
	m_keySet.right = false;
	m_keySet.ctrl = false;
	m_keySet.r_key = false;
	m_keySet.f_key = false;

	INPUT_KEY.reset();
}

void cCar::SetNetworkKey(std::string str)
{
	INPUT_KEY[E_BIT_UP___] = (str[0] == '1');	m_keySet.up = INPUT_KEY[E_BIT_UP___];
	INPUT_KEY[E_BIT_DOWN_] = (str[1] == '1');	m_keySet.down = INPUT_KEY[E_BIT_DOWN_];
	INPUT_KEY[E_BIT_LEFT_] = (str[2] == '1');	m_keySet.left = INPUT_KEY[E_BIT_LEFT_];
	INPUT_KEY[E_BIT_RIGHT] = (str[3] == '1');	m_keySet.right = INPUT_KEY[E_BIT_RIGHT];
	INPUT_KEY[E_BIT_ITEM_] = (str[4] == '1');	m_keySet.ctrl = INPUT_KEY[E_BIT_ITEM_];
	INPUT_KEY[E_BIT_REPOS] = (str[5] == '1');	m_keySet.r_key = INPUT_KEY[E_BIT_REPOS];
	INPUT_KEY[E_BIT_FLIP_] = (str[5] == '1');	m_keySet.f_key = INPUT_KEY[E_BIT_FLIP_];
}

NxVec3 cCar::WheelArrow(float angle, bool back)
{
	NxWheel* wheel = m_carNxVehicle->getWheel(0);

	NxReal hAngle = (back ? -wheel->getAngle() : wheel->getAngle());
	return CarArrow(angle + D3DXToDegree(hAngle));
}
