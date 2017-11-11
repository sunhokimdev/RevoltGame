#include "stdafx.h"
#include "cAI_Ray.h"

#include "cCar.h"
#include "cCheckBox.h"
#include "cTrack.h"

cAI_Ray::cAI_Ray(AI_DATA pData)
{
	cAI::AI_Data = pData;
	familyAI = NULL;

	RayDist = 100.f;
}


cAI_Ray::~cAI_Ray()
{
}

void cAI_Ray::Update()
{
	//레이 시작 지점
	NxVec3 raypos = AI_Data.pCar->GetPhysXData()->GetPositionToNxVec3() + NxVec3(0, 0.3, 0);

	//체크박스의 방향
	float dirY = RayDirY();

	//차의 진행상태
	float back = 0.0f;
	NxVec3 dirF_ = NxVec3(0, 0, 0);
	NxVec3 dirB_ = NxVec3(0, 0, 0);
	if (0 > AI_Data.pCar->GetRpm())
	{
		//후진
		back = 180.f;
		dirF_ = AI_Data.pCar->CarArrow(0);				dirF_.y = dirY;
		dirB_ = AI_Data.pCar->WheelArrow(180, true);	dirB_.y = -dirY;
	}
	else
	{
		//전진
		back = 0.0;
		dirF_ = AI_Data.pCar->WheelArrow(0);			dirF_.y = dirY;
		dirB_ = AI_Data.pCar->CarArrow(180);			dirB_.y = -dirY;
	}

	//정면/후면 레이 발사
	Ray_F__.RayShot(raypos, dirF_, RayDist);
	Ray_B__.RayShot(raypos, dirB_, RayDist);
	//

	float F_Value = 0;	//front value : 최대(RayDist) 측정거리와현재 거리의 비율 
	F_Value = 1.0f - fmin(Ray_F__.DistanceRate(RayDist), 1.0f);
	//F_Value *= F_Value;
	//측면 측정  (F_Value 에 따라 측정각도 조절(거리가 가까울 수록 각도를 늘려준다.))
	NxVec3 dirLF = AI_Data.pCar->WheelArrow((0 - 0) - 30 * F_Value);		dirLF.y = dirY;
	NxVec3 dirRF = AI_Data.pCar->WheelArrow((0 + 0) + 30 * F_Value);		dirRF.y = dirY;
	NxVec3 dirL_ = AI_Data.pCar->WheelArrow((0 - 30) - 30 * F_Value);		dirL_.y = dirY;
	NxVec3 dirR_ = AI_Data.pCar->WheelArrow((0 + 30) + 30 * F_Value);		dirR_.y = dirY;

	Ray_LF_.RayShot(raypos, dirLF, RayDist);
	Ray_RF_.RayShot(raypos, dirRF, RayDist);
	Ray_L__.RayShot(raypos, dirL_, RayDist);
	Ray_R__.RayShot(raypos, dirR_, RayDist);
}

void cAI_Ray::Render()
{
	D3DXMATRIXA16 mat16;
	D3DXVECTOR3 pos;
	D3DMATERIAL9 material;

	if (!AI_Mesh)
	{
		D3DXCreateSphere(g_pD3DDevice, 0.5, 16, 16, &AI_Mesh, NULL);
	}


	ZeroMemory(&material, sizeof(D3DMATERIAL9));
	material.Ambient = CX_GREEN;
	material.Diffuse = CX_GREEN;
	material.Specular = CX_GREEN;
	material.Emissive = CX_GREEN;
	g_pD3DDevice->SetMaterial(&material);

	pos = Ray_F__.GetPosition_Dx();
	D3DXMatrixTranslation(&mat16, pos.x, pos.y, pos.z);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat16);
	(AI_Mesh)->DrawSubset(0);

	pos = Ray_B__.GetPosition_Dx();
	D3DXMatrixTranslation(&mat16, pos.x, pos.y, pos.z);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat16);
	(AI_Mesh)->DrawSubset(0);

	ZeroMemory(&material, sizeof(D3DMATERIAL9));
	material.Ambient = CX_YELLOW;
	material.Diffuse = CX_YELLOW;
	material.Specular = CX_YELLOW;
	material.Emissive = CX_YELLOW;
	g_pD3DDevice->SetMaterial(&material);

	pos = Ray_LF_.GetPosition_Dx();
	D3DXMatrixTranslation(&mat16, pos.x, pos.y, pos.z);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat16);
	(AI_Mesh)->DrawSubset(0);

	pos = Ray_RF_.GetPosition_Dx();
	D3DXMatrixTranslation(&mat16, pos.x, pos.y, pos.z);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat16);
	(AI_Mesh)->DrawSubset(0);

	ZeroMemory(&material, sizeof(D3DMATERIAL9));
	material.Ambient = CX_RED;
	material.Diffuse = CX_RED;
	material.Specular = CX_RED;
	material.Emissive = CX_RED;
	g_pD3DDevice->SetMaterial(&material);

	pos = Ray_L__.GetPosition_Dx();
	D3DXMatrixTranslation(&mat16, pos.x, pos.y, pos.z);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat16);
	(AI_Mesh)->DrawSubset(0);

	pos = Ray_R__.GetPosition_Dx();
	D3DXMatrixTranslation(&mat16, pos.x, pos.y, pos.z);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat16);
	(AI_Mesh)->DrawSubset(0);

	//
	return;
	//pos = Ray_6__.GetPosition_Dx();
	//D3DXMatrixTranslation(&mat16, pos.x, pos.y, pos.z);
	//g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat16);
	//(AI_Mesh)->DrawSubset(0);
	//
	//pos = Ray_7__.GetPosition_Dx();
	//D3DXMatrixTranslation(&mat16, pos.x, pos.y, pos.z);
	//g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat16);
	//(AI_Mesh)->DrawSubset(0);
	//
	//pos = Ray_8__.GetPosition_Dx();
	//D3DXMatrixTranslation(&mat16, pos.x, pos.y, pos.z);
	//g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat16);
	//(AI_Mesh)->DrawSubset(0);
	//
	//pos = Ray_9__.GetPosition_Dx();
	//D3DXMatrixTranslation(&mat16, pos.x, pos.y, pos.z);
	//g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat16);
	//(AI_Mesh)->DrawSubset(0);
}

float cAI_Ray::RayDirY()
{
	cCheckBox* box = (cCheckBox*)(*(AI_Data.pCar)->m_pTrack->GetCheckBoxsPt())[AI_Data.pCar->GetAICheckBoxID()];
	D3DXVECTOR3 nextPos = box->GetNextCheckBox()->GetPosition() - D3DXVECTOR3(0, 0.1, 0);
	D3DXVECTOR3 carpos = AI_Data.pCar->GetPhysXData()->GetPositionToD3DXVec3();
	D3DXVECTOR3 dirCheck(0, 0, 0);
	D3DXVec3Normalize(&dirCheck, &(nextPos - carpos));
	return dirCheck.y;
}
