#include "stdafx.h"
#include "cAI_CtrlSpeed.h"
#include "cPhysXManager.h"
#include "cCar.h"

cAI_CtrlSpeed::cAI_CtrlSpeed()
{
	rayHitFront = NULL;

	pMesh = new LPD3DXMESH;

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

}


cAI_CtrlSpeed::~cAI_CtrlSpeed()
{

}

void cAI_CtrlSpeed::Update()
{
	NxVec3 raypos = m_pAICar->GetPhysXData()->GetPositionToNxVec3() + NxVec3(0, 1, 0);
	NxVec3 dirFront = m_pAICar->WheelArrow(0, false); dirFront.y = 0;
	NxVec3 dirBack = m_pAICar->WheelArrow(180, true); dirBack.y = 0;
	std::cout << dirBack.x << std::endl;

	dirFront.normalize();
	dirBack.normalize();

	rayHitFront = &RAYCAST(raypos, dirFront, 100);//,ePhysXTag::E_PHYSX_TAG_RAYCAST_TO_AI);
	rayHitBack = &RAYCAST(raypos, dirBack, 100);

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
			//			std::cout << "Front" << std::endl;
		}
	}


	//	std::cout << aiState << std::endl;

		//
	frontDistPrev = frontDistCurr;
	backDistPrev = backDistCurr;

	if (g_pKeyManager->isStayKeyDown(VK_TAB))
	{
		SetBitKey(eBIT_KEY::E_BIT_UP, aiState == E_SpeedStateFront);
		SetBitKey(eBIT_KEY::E_BIT_DOWN, aiState == E_SpeedStateBack);
	}
}

void cAI_CtrlSpeed::Render()
{
	D3DXCreateSphere(g_pD3DDevice, 0.5, 8, 8, pMesh, NULL);
	D3DXMATRIXA16 mat16;
	D3DXMatrixTranslation(&mat16, FrontPos.x, FrontPos.y, FrontPos.z);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat16);
	(*pMesh)->DrawSubset(0);

	D3DXMatrixTranslation(&mat16, BackPos.x, BackPos.y, BackPos.z);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat16);
	(*pMesh)->DrawSubset(0);
}
