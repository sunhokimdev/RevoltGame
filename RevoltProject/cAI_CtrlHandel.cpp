#include "stdafx.h"
#include "cAI_CtrlHandel.h"
#include "cAI_CtrlSpeed.h"
#include "cCar.h"
#include "cTrack.h"
#include "cCheckBox.h"

cAI_CtrlHandel::cAI_CtrlHandel()
{
	F__Hit = NULL;
	LF_Hit = NULL;
	RF_Hit = NULL;
	L__Hit = NULL;
	R__Hit = NULL;

	F__Pos = D3DXVECTOR3(0, 0, 0);
	LF_Pos = D3DXVECTOR3(0, 0, 0);
	RF_Pos = D3DXVECTOR3(0, 0, 0);
	L__Pos = D3DXVECTOR3(0, 0, 0);
	R__Pos = D3DXVECTOR3(0, 0, 0);

	aiState = E_AIHandle_F;

	AITag = AI_TAG_HANDLE;
	HandleValue = 0.0f;


	FindDirNum = 2;


	F___DistRange = 50.f;
	LRF_DistRange = 50.f;
	LR__DistRange = 50.f;

	//F___DistValue = 1.0f;
	LRF_DistValue = 1.0f;
	LR__DistValue = 1.0f;
}


cAI_CtrlHandel::~cAI_CtrlHandel()
{
}

void cAI_CtrlHandel::Update()
{
	NxVec3 raypos = m_pAICar->GetPhysXData()->GetPositionToNxVec3() + NxVec3(0, 0.3, 0);

	cCheckBox* box = (cCheckBox*)(*m_pAICar->m_pTrack->GetCheckBoxsPt())[m_pAICar->GetAICheckBoxID()];
	D3DXVECTOR3 nextPos = box->GetNextCheckBox()->GetPosition() - D3DXVECTOR3(0, 0.1, 0);
	D3DXVECTOR3 carpos = m_pAICar->GetPhysXData()->GetPositionToD3DXVec3();
	D3DXVECTOR3 dirCheck;
	D3DXVec3Normalize(&dirCheck, &(nextPos - carpos));
	float dirY = dirCheck.y;

	cAI_CtrlSpeed* pAiSpeed = (cAI_CtrlSpeed*)FindMaster()->FindAITag(AI_TAG::AI_TAG_SPEED);
	float back = 0.0f;
	if (0 > m_pAICar->GetRpm()) back = 180.f;

	//정면체크
	NxVec3 dirF_ = m_pAICar->WheelArrow(back + 0);	dirF_.y = dirY;
	F__Hit = &RAYCAST(raypos, dirF_);
	RayHitPos(F__Hit, &F__Pos);
	RayHitDist(F__Hit, &F__Dist);

	//정면 거리에 따른 측면 측정각 조절
	float frontValue = 0;
	if (F__Dist < F___DistRange) frontValue = ((F___DistRange - F__Dist) / F___DistRange);

	//측면 측정
	NxVec3 dirLF = m_pAICar->WheelArrow((back - 30) * frontValue);		dirLF.y = dirY;
	NxVec3 dirRF = m_pAICar->WheelArrow((back + 30) * frontValue);		dirRF.y = dirY;
	NxVec3 dirL_ = m_pAICar->WheelArrow((back - 30) * 1.f);				dirL_.y = dirY;
	NxVec3 dirR_ = m_pAICar->WheelArrow((back + 30) * 1.f);				dirR_.y = dirY;

	LF_Hit = &RAYCAST(raypos, dirLF);
	RF_Hit = &RAYCAST(raypos, dirRF);
	L__Hit = &RAYCAST(raypos, dirL_);
	R__Hit = &RAYCAST(raypos, dirR_);

	RayHitPos(LF_Hit, &LF_Pos);
	RayHitPos(RF_Hit, &RF_Pos);
	RayHitPos(L__Hit, &L__Pos);
	RayHitPos(R__Hit, &R__Pos);

	RayHitDist(LF_Hit, &LF_Dist);
	RayHitDist(RF_Hit, &RF_Dist);
	RayHitDist(L__Hit, &L__Dist);
	RayHitDist(R__Hit, &R__Dist);

	float LRFScale = LF_Dist + RF_Dist;
	if (LF_Dist < LRF_DistRange * (frontValue + 1.414))
	{
		float add = CheckBoxPoint(dirLF) + ScaleValue(LF_Dist, LRFScale) * LRF_DistValue;
		HandleValue += add;
	}
	else
	{
		HandleValue += CheckBoxPoint(dirLF);
	}
	if (RF_Dist < LRF_DistRange * (frontValue + 1.414))
	{
		float add = CheckBoxPoint(dirRF) + ScaleValue(RF_Dist, LRFScale) * LRF_DistValue;
		HandleValue -= add;
	}
	else
	{
		HandleValue -= CheckBoxPoint(dirRF);
	}

	float LRScale = L__Dist + R__Dist;
	if (L__Dist < LR__DistRange)
	{
		float add = CheckBoxPoint(dirL_) + ScaleValue(L__Dist, LRScale) * LR__DistValue;
		HandleValue += add;
	}
	else
	{
		HandleValue += CheckBoxPoint(dirL_);
	}
	if (R__Dist < LR__DistRange)
	{
		float add = CheckBoxPoint(dirR_) + ScaleValue(R__Dist, LRScale)* LR__DistValue;
		HandleValue -= add;
	}
	else
	{
		HandleValue -= CheckBoxPoint(dirR_);
	}


	std::cout << HandleValue << std::endl;

	if (abs(HandleValue) < HandleDistance)
	{
		float add = 0;
		add += CheckBoxPoint(dirL_) + ScaleValue(L__Dist, LRScale);
		add -= CheckBoxPoint(dirR_) + ScaleValue(R__Dist, LRScale);
		HandleValue += add;
		//	std::cout << add << std::endl;
	}

	aiState = E_AIHandle_F;
	//	if (back > 90.f) HandleValue *= -1;
	if (HandleValue < -HandleDistance) aiState = E_AIHandle_L;
	if (HandleValue > +HandleDistance) aiState = E_AIHandle_R;


	SetBitKey(eBIT_KEY::E_BIT_LEFT, aiState == E_AIHandle_L);
	SetBitKey(eBIT_KEY::E_BIT_RIGHT, aiState == E_AIHandle_R);
	HandleValue = 0.0f;
}

void cAI_CtrlHandel::Render()
{
	D3DMATERIAL9 material;
	material.Ambient = CX_RED;
	material.Diffuse = CX_RED;
	material.Specular = CX_RED;
	material.Emissive = CX_RED;
	g_pD3DDevice->SetMaterial(&material);
	D3DXMATRIXA16 mat16;
	D3DXMatrixIdentity(&mat16);


	D3DXMatrixTranslation(&mat16, L__Pos.x, L__Pos.y, L__Pos.z);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat16);
	(pMesh)->DrawSubset(0);

	D3DXMatrixTranslation(&mat16, LF_Pos.x, LF_Pos.y, LF_Pos.z);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat16);
	(pMesh)->DrawSubset(0);

	D3DXMatrixTranslation(&mat16, F__Pos.x, F__Pos.y, F__Pos.z);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat16);
	(pMesh)->DrawSubset(0);

	D3DXMatrixTranslation(&mat16, RF_Pos.x, RF_Pos.y, RF_Pos.z);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat16);
	(pMesh)->DrawSubset(0);

	D3DXMatrixTranslation(&mat16, R__Pos.x, R__Pos.y, R__Pos.z);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat16);
	(pMesh)->DrawSubset(0);
}

float cAI_CtrlHandel::ScaleValue(float dist, float Scale)
{
	return ((Scale - dist) / Scale);
}

//0~1 점
float cAI_CtrlHandel::CheckBoxPoint(D3DXVECTOR3 dir)
{
	D3DXVec3Normalize(&dir, &dir);
	cCheckBox* box = (cCheckBox*)(*m_pAICar->m_pTrack->GetCheckBoxsPt())[m_pAICar->GetAICheckBoxID()];
	D3DXVECTOR3 dir1 = box->ToNextCheckBoxDir();
	if (FindDirNum == 1)
		return -(D3DXVec3Dot(&dir1, &dir) * 0.5f + 0.5f);

	D3DXVECTOR3 dir2 = box->GetNextCheckBox()->ToNextCheckBoxDir();
	if (FindDirNum == 2)
	{
		D3DXVec3Normalize(&dir2, &(dir1 + (dir2*0.5f)));
		return -(D3DXVec3Dot(&dir2, &dir) * 0.5f + 0.5f);
	}

	D3DXVECTOR3 dir3 = box->GetNextCheckBox()->GetNextCheckBox()->ToNextCheckBoxDir();
	if (FindDirNum == 3)
	{
		D3DXVec3Normalize(&dir3, &(dir1 + (dir2*0.5f) + (dir3*0.25f)));
		return -(D3DXVec3Dot(&dir3, &dir) * 0.5f + 0.5f);
	}

	return 0;
	//	return -D3DXVec3Dot(&dir1, &dir) * 0.5f + 0.5f;
}

float cAI_CtrlHandel::CheckBoxPoint(NxVec3 dir)
{
	return CheckBoxPoint(D3DXVECTOR3(dir.x, dir.y, dir.z));
}
