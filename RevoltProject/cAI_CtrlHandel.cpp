#include "stdafx.h"
#include "cAI_CtrlHandel.h"
#include "cPhysXManager.h"
#include "cCar.h"

cAI_CtrlHandel::cAI_CtrlHandel()
{
	//rayHitFront = NULL;
	rayHitFront.shape = NULL;
	rayHitBack.shape = NULL;

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

cAI_CtrlHandel::~cAI_CtrlHandel()
{
}

void cAI_CtrlHandel::Update()
{
	NxVec3 raypos = m_pAICar->GetPhysXData()->GetPositionToNxVec3() + NxVec3(0, 1, 0);
	//NxVec3 dirFront = m_pAICar->WheelArrow(0, false); dirFront.y = 0;

	D3DXMATRIXA16 matR;
	matR = m_pAICar->GetMatrix(false, true, false); 

	D3DXVECTOR3 dirFr = { 1,0,0 };
	D3DXVec3TransformNormal(&dirFr, &dirFr, &matR);
	
	NxVec3 dirFront = dirFr;
	NxVec3 dirBack = -dirFr;

	//rayHitFront = &RAYCAST(raypos, dirFront, 100);
	//rayHitBack = &RAYCAST(raypos, dirBack, 100);
	
	//RAYCAST(rayHitFront, raypos, dirFront, 100);
	MgrPhysX->RaycastClosestShapePt(&rayHitFront, raypos, dirFront, 100);
	MgrPhysX->RaycastClosestShapePt(&rayHitBack, raypos, dirBack, 100);

	//g_pPhysXScene->raycastClosestShape(RayCamVertical, NxShapesType::NX_ALL_SHAPES, RayCamVerticalHit, 0xffffffff, Height);
	

	//if (rayHitFront.shape)
	//{
	//	std::string strFkName = rayHitBack.shape->getActor().getName();
	//	if (strFkName == "map")
	//	{
	//		frontDistCurr = rayHitFront.distance;
	//		frontDelta = frontDistCurr - frontDistPrev;

	//		NxVec3 pos = rayHitFront.worldImpact;
	//		FrontPos = D3DXVECTOR3(pos.x, pos.y, pos.z);
	//	}
	//}
	//else
	//{
	//	FrontPos = { rayHitFront.worldImpact.x,rayHitFront.worldImpact.y,rayHitFront.worldImpact.z };
	//}
	//if (rayHitBack.shape)
	//{
	//	std::string strBkName = rayHitBack.shape->getActor().getName();
	//	if (strBkName == "map")
	//	{
	//		backDistCurr = rayHitBack.distance;
	//		backDelta = backDistCurr - backDistPrev;

	//		NxVec3 pos = rayHitFront.worldImpact;
	//		BackPos = D3DXVECTOR3(pos.x, pos.y, pos.z);

	//	}
	//}
	//else
	//{
	//	BackPos = { rayHitBack.worldImpact.x,rayHitBack.worldImpact.y,rayHitBack.worldImpact.z };
	//}


	//if (rayHitBack->shape->getActor().getName() == "map")
	//{
	//	backDistCurr = rayHitBack->distance;
	//	backDelta = backDistCurr - backDistPrev;

	//	NxVec3 pos = rayHitFront->worldImpact;
	//	BackPos = D3DXVECTOR3(pos.x, pos.y, pos.z);

	//}
	//if (rayHitFront->shape->getActor().getName() == "map")
	//{
	//	frontDistCurr = rayHitFront->distance;
	//	frontDelta = frontDistCurr - frontDistPrev;

	//	NxVec3 pos = rayHitFront->worldImpact;
	//	FrontPos = D3DXVECTOR3(pos.x, pos.y, pos.z);
	//}

	//
	//aiHandleState = E_HanStateFront;

	if ((frontDelta < AI_value) || (frontDistCurr < AI_distanceMin))
	{
		if (frontDistCurr < AI_distanceFront)
		{
			aiState = E_SpeedStateBack;
			//			std::cout << "Back" << std::endl;
		}

		//std::cout << "Up" << std::endl;
	}

	if ((backDelta < AI_value) || (backDistCurr < AI_distanceMin))
	{
		if (backDistCurr < AI_distanceBack)
		{
			aiState = E_SpeedStateFront;
			//			std::cout << "Front" << std::endl;
		}

		//std::cout << "Down" << std::endl;

	}
	//	std::cout << aiState << std::endl;

	frontDistPrev = frontDistCurr;
	backDistPrev = backDistCurr;

	//FrontPos = { rayHitFront->worldImpact.x,rayHitFront->worldImpact.y,rayHitFront->worldImpact.z };
	//BackPos = { rayHitBack->worldImpact.x,rayHitBack->worldImpact.y,rayHitBack->worldImpact.z };

	FrontPos = { rayHitFront.worldImpact.x,rayHitFront.worldImpact.y,rayHitFront.worldImpact.z };
	BackPos = { rayHitBack.worldImpact.x,rayHitBack.worldImpact.y,rayHitBack.worldImpact.z };

	//SetBitKey(eBIT_KEY::E_BIT_LEFT, aiHandleState == E_HandleStateLeft);
	//SetBitKey(eBIT_KEY::E_BIT_RIGHT, aiHandleState == E_HandleStateRight);
}

void cAI_CtrlHandel::Render()
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
