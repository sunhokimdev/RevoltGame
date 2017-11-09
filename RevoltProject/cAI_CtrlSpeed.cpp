#include "stdafx.h"
#include "cAI_CtrlSpeed.h"
#include "cPhysXManager.h"
#include "cCar.h"

cAI_CtrlSpeed::cAI_CtrlSpeed()
{
	rayHitFront = NULL;
	rayHitBack = NULL;

	aiState = E_SpeedStateFront;

	frontDistPrev = 0;
	frontDistCurr = 0;
	frontDelta = 0;

	backDistPrev = 0;
	backDistCurr = 0;
	backDelta = 0;



	AI_distanceFront = 5;		//인지범위 
	AI_distanceBack = 3;		//인지범위 
	AI_value = 0.2f;		//delta 의 인지범위
	AI_distanceMin = 2.f;	//무조건 유지하려는 거리


	AITag = AI_TAG_SPEED;
}


cAI_CtrlSpeed::~cAI_CtrlSpeed()
{

}

void cAI_CtrlSpeed::Update()
{
	NxVec3 raypos = m_pAICar->GetPhysXData()->GetPositionToNxVec3() + NxVec3(0, 0.3, 0);
	NxVec3 dirFront = m_pAICar->WheelArrow(0, false); //dirFront.y = 0;
	NxVec3 dirBack = m_pAICar->WheelArrow(180, true); //dirBack.y = 0;

	dirFront.normalize();
	dirBack.normalize();

	rayHitFront = &RAYCAST(raypos, dirFront);
	rayHitBack = &RAYCAST(raypos, dirBack);

	if (rayHitBack->shape)
	{
		backDistCurr = rayHitBack->distance;
		backDelta = backDistCurr - backDistPrev;

		NxVec3 pos = rayHitBack->worldImpact;
		BackPos = D3DXVECTOR3(pos.x, pos.y, pos.z);
	}
	if (rayHitFront->shape)
	{
		frontDistCurr = rayHitFront->distance;
		frontDelta = frontDistCurr - frontDistPrev;

		NxVec3 pos = rayHitFront->worldImpact;
		FrontPos = D3DXVECTOR3(pos.x, pos.y, pos.z);
	}

	//
	aiState = E_SpeedStateFront;

	if ((frontDelta < AI_value) || (frontDistCurr < AI_distanceMin))
	{
		if (frontDistCurr < AI_distanceFront)
		{
			aiState = E_SpeedStateBack;
			//			std::cout << "Back" << std::endl;
		}
	}



	if ((backDelta < AI_value) || (backDistCurr < AI_distanceMin))
	{
		if (backDistCurr < AI_distanceBack)
		{
			aiState = E_SpeedStateFront;
		}
	}

	frontDistPrev = frontDistCurr;
	backDistPrev = backDistCurr;


	SetBitKey(eBIT_KEY::E_BIT_UP, aiState == E_SpeedStateFront);
	SetBitKey(eBIT_KEY::E_BIT_DOWN, aiState == E_SpeedStateBack);
}

void cAI_CtrlSpeed::Render()
{
//	g_pD3DDevice->SetTransform(D3DTS_WORLD);
	D3DMATERIAL9 material;
	material.Ambient = CX_YELLOW;
	material.Diffuse = CX_YELLOW;
	material.Specular = CX_YELLOW;
	material.Emissive = CX_YELLOW;
	g_pD3DDevice->SetMaterial(&material);


//	D3DXCreateSphere(g_pD3DDevice, 0.5, 8, 8, pMesh, NULL);
	D3DXMATRIXA16 mat16;
	D3DXMatrixTranslation(&mat16, FrontPos.x, FrontPos.y, FrontPos.z);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat16);
	(pMesh)->DrawSubset(0);

	D3DXMatrixTranslation(&mat16, BackPos.x, BackPos.y, BackPos.z);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat16);
	(pMesh)->DrawSubset(0);
}
