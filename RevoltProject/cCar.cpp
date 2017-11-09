#include "stdafx.h"
#include "cCar.h"
#include "cWheel.h"
#include "cAI.h"
#include "cPhysXManager.h"
#include "cTrack.h"
#include "cSkidMark.h"
#include "cCheckBox.h"
#include "InGameUI.h"

#include <fstream>

cCar::cCar()
	:m_pSkidMark(NULL)
{
	m_countRapNum = -1;
	m_currCheckBoxID = -1;
	m_rapTimeCount = 0.f;
	m_totlaTimeCount = 0.f;
	m_bastRapTimeCount = -1.0f;
	isFliping = false;
	m_nextCheckBoxID = 0;
	m_eHoldItem = ITEM_NONE;
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
	else
	{
		MessageBoxA(g_hWnd, "*.car 파일을 찾을 수 없습니다.", "파일 없음", MB_OK);
	}

	m_pSkidMark = new cSkidMark;
	m_pSkidMark->LinkCar(this);

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

void cCar::SetAI(bool isAI)
{
	m_isAI = isAI;

	m_vecAI.clear();
	if (isAI)
	{
		cAI* pAI = new cAI;
		pAI->SetCar(this);
		m_vecAI.push_back(pAI);
	}
}

void cCar::CreateItem()
{
	if (!m_eHoldItem)
	{
		while (1)
		{
			//m_eHoldItem = eITEM_LIST(rand() % (eITEM_LIST::ITEM_LAST));
			m_eHoldItem = eITEM_LIST::ITEM_WBOMB;
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
	//차가 땅에 박히는 걸 망지
	m_carNxVehicle->getActor()->addForce(NxVec3(0, 0.001, 0));
	INPUT_KEY.reset();

	CtrlPlayer();

	if (g_pKeyManager->isStayKeyDown(VK_TAB))
	{
		if (m_isAI) CtrlAI();
		else CtrlPlayer();
	}

	//이하 AI, PLAYER 의 동일 사용 함수

	//자동차 움직임
	CarMove();

	//자동차 리포지션
	if (INPUT_KEY[E_BIT_REPOS]) RePosition();

	// PickUp 충돌
	if (INPUT_KEY[E_BIT_FLIP]) CollidePickUp();

	//아이템 사용
	if (INPUT_KEY[E_BIT_ITEM]) UsedItem();

	//차 뒤집기
	if (INPUT_KEY[E_BIT_FLIP]) CarFlip();

	m_szPrevPos[0] = GetPhysXData()->GetPositionToD3DXVec3();

	//스피드 계산
	SpeedMath();

	//트랙 체크
	TrackCheck();

	//바퀴 자국
	CreateSkidMark();
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


	if (m_isAI)
	{
		for each (cAI* pAI in m_vecAI)
		{
			pAI->Render();
		}
	}

	if (m_pSkidMark)
	{
		m_pSkidMark->Render();
	}
}

void cCar::Destory()
{
	if (m_pSkidMark) m_pSkidMark->Destory();
	SAFE_DELETE(m_pSkidMark);
	Object::Destroy();
}

void cCar::CtrlPlayer()
{
	if (m_carNxVehicle)
	{
		INPUT_KEY[E_BIT_UP] = g_pKeyManager->isStayKeyDown(KEY_ACCELERATOR);
		INPUT_KEY[E_BIT_DOWN] = g_pKeyManager->isStayKeyDown(KEY_REVERSE);
		INPUT_KEY[E_BIT_LEFT] = g_pKeyManager->isStayKeyDown(KEY_MOVE_LEFT);
		INPUT_KEY[E_BIT_RIGHT] = g_pKeyManager->isStayKeyDown(KEY_MOVE_RIGHT);
		INPUT_KEY[E_BIT_ITEM] = g_pKeyManager->isOnceKeyDown(KEY_FIRE_ITEM);
		INPUT_KEY[E_BIT_REPOS] = g_pKeyManager->isOnceKeyDown(KEY_REPOSITION);
		INPUT_KEY[E_BIT_FLIP] = g_pKeyManager->isOnceKeyDown(KEY_CAR_FLIP);
	}
}

void cCar::CtrlAI()
{
	for each (cAI* pAI in m_vecAI)
	{
		if (m_carNxVehicle) pAI->Update();
	}
}

//void cCar::GetRpm()
//{
//	float rpm;
//}

void cCar::TrackCheck()
{
	//체크박스 및 트랙 카운터
	int checkId = GetPhysXData()->m_pUserData->CheckBoxID;
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

			if (!m_isAI) m_pInGameUI->SetLabCnt(m_countRapNum);
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

		if (m_currCheckBoxID == 0)
		{
			m_countRapNum++;
			if (!m_isAI) m_pInGameUI->SetLabCnt(m_countRapNum);
			if (!m_isAI) m_pInGameUI->UpdateLastTime();
			if (!m_isAI) m_pInGameUI->SetLabElapseTime(0);
			if (!m_isAI) m_pInGameUI->SetLabMinOneth(FONT2_NUM0);
			if (!m_isAI) m_pInGameUI->SetLabMinTenth(FONT2_NUM0);


			if (m_bastRapTimeCount > m_rapTimeCount || m_bastRapTimeCount < 0.0f)
			{
				m_bastRapTimeCount = m_rapTimeCount;

			}
			std::cout << "Rap::" << m_countRapNum
				<< "\t rapTime::" << m_rapTimeCount
				<< "\t bastRapTime::" << m_bastRapTimeCount
				<< std::endl;
			m_rapTimeCount = 0.f;
		}

		std::cout << "Track::" << m_countRapNum
			<< "\t CcheckBox::" << m_currCheckBoxID
			<< "\t NcheckBox::" << m_nextCheckBoxID
			<< std::endl;
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
		if (RayCarHit.distance < 0.2f
			&& RayCarHit.shape->getActor().getName() == "map")
		{
			m_pSkidMark->DrawSkidMark();
		}
	}

	//	테스트용
	if (g_pKeyManager->isStayKeyDown(VK_SHIFT))
	{
		if (RayCarHit.distance < 0.2f)
		{
			m_pSkidMark->DrawSkidMark();
		}
	}
	if (g_pKeyManager->isStayKeyDown(VK_SPACE))
	{
		m_pSkidMark->Destory();
	}
}

void cCar::SpeedMath()
{
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
			std::cout << m_eHoldItem << " - " << m_nItemCount << std::endl;
			//GetPhysXData()->m_pUserData->IsPickUp == NX_FALSE;
		}
	}
}

void cCar::SettingCarPos()
{
	//자동차 정보 업데이트
	//=================================================
	//자동차 위치 갱신
	m_position = {
		GetNxVehicle()->getGlobalPose().t.x,
		GetNxVehicle()->getGlobalPose().t.y,
		GetNxVehicle()->getGlobalPose().t.z };


	//자동차전용 회전 매트릭스
	//회전 매트릭스 받아옴
	NxF32 mat[9];
	GetNxVehicle()->getGlobalPose().M.getColumnMajor(mat);
	D3DXMatrixIdentity(&m_matCarRotation);
	m_matCarRotation._11 = mat[0];
	m_matCarRotation._12 = mat[1];
	m_matCarRotation._13 = mat[2];
	m_matCarRotation._21 = mat[3];
	m_matCarRotation._22 = mat[4];
	m_matCarRotation._23 = mat[5];
	m_matCarRotation._31 = mat[6];
	m_matCarRotation._32 = mat[7];
	m_matCarRotation._33 = mat[8];

	//=================================================
}

void cCar::CarMove()
{
	//엑셀
	float targetPower = 0.f;
	bool power = false;
	m_breakPower = 0.f;
	if (INPUT_KEY[E_BIT_UP])
	{
		m_moterPower += m_moterAcc;
		if (m_moterPower > 1.f) m_moterPower = 1.f;
		targetPower = m_moterPower * m_maxMoterPower;
		power = true;
	}
	if (INPUT_KEY[E_BIT_DOWN])
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
	if (INPUT_KEY[E_BIT_LEFT])
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
	g_pItemManager->FireItem(ITEM_MYBOMB, this);

	if (m_eHoldItem != ITEM_NONE)
	{
		//아이템 사용 함수 호츨

		m_nItemCount--;
		if (m_nItemCount == 0)
		{
			g_pItemManager->FireItem(m_eHoldItem, this);
			m_eHoldItem = ITEM_NONE;
			GetPhysXData()->m_pUserData->IsPickUp = NX_FALSE;
		}
		std::cout << "FIRE!" << std::endl;
	}
}

void cCar::RePosition()
{

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
	//	std::cout << carUp.y << std::endl;
	if (carUp.y > 0.0f)
	{
		return;
	}

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

NxVec3 cCar::WheelArrow(float angle, bool back)
{
	NxWheel* wheel = m_carNxVehicle->getWheel(0);
	NxReal hAngle = NxMath::radToDeg(wheel->getAngle());
	return CarArrow(angle + (back ? -hAngle : hAngle));
}