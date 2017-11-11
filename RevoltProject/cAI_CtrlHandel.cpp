#include "stdafx.h"
#include "cCar.h"
#include "cTrack.h"
#include "cCheckBox.h"
#include "cAI_Master.h"


cAI_CtrlHandel::cAI_CtrlHandel(AI_DATA pData)
{
	cAI::AI_Data = pData;
	familyAI = NULL;

	LRF_F_RateValue = 1.5f;
	LRF_D_RateVAlue = 2.0f;
	LR__F_RateValue = 1.0f;
	LR__D_RateVAlue = 1.5f;

	FindDirNum = 3;

	HandleDistance = 1.f;


	RealDir = D3DXVECTOR3(1, 0, 0);

	isPoint = false;
}

cAI_CtrlHandel::~cAI_CtrlHandel()
{
}

void cAI_CtrlHandel::Update()
{
	//	NxVec3 raypos = m_pCar->GetPhysXData()->GetPositionToNxVec3() + NxVec3(0, 0.3, 0);
	//
	//	float dirY = RayDirY();
	//
	//	cAI_CtrlSpeed* pAiSpeed = (cAI_CtrlSpeed*)FindMaster()->FindAITag(AI_TAG::AI_TAG_SPEED);
	//	float back = 0.0f;
	//	if (0 > m_pCar->GetRpm()) back = 180.f;
	//
	//	//정면체크
	//	NxVec3 dirF_ = m_pCar->WheelArrow(back + 0);	dirF_.y = dirY;
	//	F__Hit = &RAYCAST(raypos, dirF_);
	//	RayHitPos(F__Hit, &F__Pos);
	//	RayHitDist(F__Hit, &F__Dist);
	//
	//	//정면 거리에 따른 측면 측정각 조절
	//	float frontValue = 0;
	//	frontValue = 1.0f - ((F__Dist / F___DistRange) > 1.0f ? 1.f : F__Dist / F___DistRange);
	//
	//	//측면 측정
	//	NxVec3 dirLF = m_pCar->WheelArrow((back -  5) - 30 * frontValue);		dirLF.y = dirY;
	//	NxVec3 dirRF = m_pCar->WheelArrow((back +  5) + 30 * frontValue);		dirRF.y = dirY;
	//	NxVec3 dirL_ = m_pCar->WheelArrow((back - 35) - 50 * frontValue);				dirL_.y = dirY;
	//	NxVec3 dirR_ = m_pCar->WheelArrow((back + 35) + 50 * frontValue);				dirR_.y = dirY;
	//
	//	LF_Hit = &RAYCAST(raypos, dirLF);
	//	RF_Hit = &RAYCAST(raypos, dirRF);
	//	L__Hit = &RAYCAST(raypos, dirL_);
	//	R__Hit = &RAYCAST(raypos, dirR_);
	//
	//	RayHitPos(LF_Hit, &LF_Pos);
	//	RayHitPos(RF_Hit, &RF_Pos);
	//	RayHitPos(L__Hit, &L__Pos);
	//	RayHitPos(R__Hit, &R__Pos);
	//
	//	RayHitDist(LF_Hit, &LF_Dist);
	//	RayHitDist(RF_Hit, &RF_Dist);
	//	RayHitDist(L__Hit, &L__Dist);
	//	RayHitDist(R__Hit, &R__Dist);
	//


	HandleValue = 0.0f;

	float F__Dist = ((cAI_Ray*)(*familyAI)[AI_TAG_RAY])->Ray_F__.Distance();
	float LF_Dist = ((cAI_Ray*)(*familyAI)[AI_TAG_RAY])->Ray_LF_.Distance();
	float RF_Dist = ((cAI_Ray*)(*familyAI)[AI_TAG_RAY])->Ray_RF_.Distance();
	float L__Dist = ((cAI_Ray*)(*familyAI)[AI_TAG_RAY])->Ray_L__.Distance();
	float R__Dist = ((cAI_Ray*)(*familyAI)[AI_TAG_RAY])->Ray_R__.Distance();

	D3DXVECTOR3 F__Dir = ((cAI_Ray*)(*familyAI)[AI_TAG_RAY])->Ray_F__.GetDir_Dx();
	D3DXVECTOR3 LF_Dir = ((cAI_Ray*)(*familyAI)[AI_TAG_RAY])->Ray_LF_.GetDir_Dx();
	D3DXVECTOR3 RF_Dir = ((cAI_Ray*)(*familyAI)[AI_TAG_RAY])->Ray_RF_.GetDir_Dx();
	D3DXVECTOR3 L__Dir = ((cAI_Ray*)(*familyAI)[AI_TAG_RAY])->Ray_L__.GetDir_Dx();
	D3DXVECTOR3 R__Dir = ((cAI_Ray*)(*familyAI)[AI_TAG_RAY])->Ray_R__.GetDir_Dx();

	float LRFScale = LF_Dist + RF_Dist;
	float LRScale = L__Dist + R__Dist;

	//isPoint == true	추적 방식을 차와 체크박스로 변경
	//isPoint == false	추적 방식을 체크박스와 체크박스로 변경 (defalut)
	if (isPoint)
	{
		//해당 조건 만족 후 추적 변경
		//일정 방향과 일정 속도 도달시
		if (CheckBoxPoint(F__Dir) > 0.75f)
		{
			if (AI_Data.pCar->GetRpm() / AI_Data.pCar->m_maxRpm > 0.4f)
			{
				isPoint = false;
			}
		}
	}
	else 
		isPoint = ((cAI_CtrlSpeed*)(*familyAI)[AI_TAG_SPEED])->isBack;

	//isPoint = true;
	//std::cout << CheckBoxPoint(F__Dir, isPoint) << std::endl;

	{
		float add = 1.0
			* ScaleValue(L__Dist, F__Dist, LR__F_RateValue)
			* ScaleValue(L__Dist, LRScale, LR__F_RateValue)
			* CheckBoxPoint(L__Dir) * LR__D_RateVAlue
			;
		HandleValue -= add;
//		std::cout << -add << " + ";
	}
	{
		float add = 1.0
			* ScaleValue(LF_Dist, F__Dist, LRF_F_RateValue)
			* ScaleValue(LF_Dist, LRFScale, LRF_F_RateValue)
			* CheckBoxPoint(LF_Dir) * LRF_D_RateVAlue
			;
		HandleValue -= add;
//		std::cout << -add << " + ";
	}
	{
		float add = 1.0
			* ScaleValue(RF_Dist, F__Dist, LRF_F_RateValue)
			* ScaleValue(RF_Dist, LRFScale, LRF_F_RateValue)
			* CheckBoxPoint(RF_Dir) * LRF_D_RateVAlue
			;
		HandleValue += add;
//		std::cout << add << " + ";
	}
	{
		float add = 1.0
			* ScaleValue(R__Dist, F__Dist, LR__F_RateValue)
			* ScaleValue(R__Dist, LRScale, LR__F_RateValue)
			* CheckBoxPoint(R__Dir) * LR__D_RateVAlue
			;
		HandleValue += add;
//				std::cout << add << " = ";
	}

}

void cAI_CtrlHandel::Render()
{

}


//0~1 점
float cAI_CtrlHandel::CheckBoxPoint(D3DXVECTOR3 dir)
{
	cCheckBox* box = CurrentCheckBox();
	if (box == NULL) return 1.0f;


	//포인팅 추적
	if (isPoint)
	{
		D3DXVECTOR3 posBox = box->GetNextCheckBox()->GetPhysXData()->GetPositionToD3DXVec3();
		D3DXVECTOR3 poscar = AI_Data.pCar->GetPhysXData()->GetPositionToD3DXVec3();
		D3DXVECTOR3 dir0 = posBox - poscar;
		D3DXVec3Normalize(&dir0, &dir0);

		D3DXVec3Normalize(&dir, &dir);

		return  (D3DXVec3Dot(&dir0, &dir));
	}


	//방향 추적
	D3DXVECTOR3 dir1 = box->ToNextCheckBoxDir();
	if (FindDirNum == 1)
	{
		D3DXVec3Normalize(&dir, &dir);
		return (D3DXVec3Dot(&dir1, &dir));
	}

	D3DXVECTOR3 dir2 = box->GetNextCheckBox()->ToNextCheckBoxDir();
	if (FindDirNum == 2)
	{
		D3DXVec3Normalize(&dir2, &(dir1 + (dir2*0.75)));
		return (D3DXVec3Dot(&dir2, &dir));
	}

	D3DXVECTOR3 dir3 = box->GetNextCheckBox()->GetNextCheckBox()->ToNextCheckBoxDir();
	if (FindDirNum == 3)
	{
		D3DXVec3Normalize(&dir3, &(dir1 + (dir2*0.5f) + (dir3*0.25f)));
		return (D3DXVec3Dot(&dir3, &dir));
	}

	return 1.0f;
	//	return -D3DXVec3Dot(&dir1, &dir) * 0.5f + 0.5f;
}

float cAI_CtrlHandel::CheckBoxPoint(NxVec3 dir)
{
	return CheckBoxPoint(D3DXVECTOR3(dir.x, dir.y, dir.z));
}
