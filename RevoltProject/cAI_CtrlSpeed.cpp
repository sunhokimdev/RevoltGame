#include "stdafx.h"
#include "cAI_CtrlSpeed.h"
#include "cPhysXManager.h"
#include "cCar.h"

cAI_CtrlSpeed::cAI_CtrlSpeed()
{
	rayHitFront = NULL;

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
	NxVec3 raypos = m_pAICar->GetPhysXData()->GetPositionToNxVec3() + NxVec3(0, 0.2, 0);
	NxVec3 dirFront = m_pAICar->WheelArrow(0, false); dirFront.y = 0;
	NxVec3 dirBack = m_pAICar->WheelArrow(0, true); dirBack.y = 0;
	dirFront.normalize();
	dirBack.normalize();

	rayHitFront = &RAYCAST(raypos, dirFront, AI_distanceFront);
	rayHitBack = &RAYCAST(raypos, dirBack, AI_distanceBack);

	if (rayHitFront->shape)
	{
		backDistCurr = rayHitBack->distance;
		backDelta = backDistCurr - backDistPrev;
	}
	if (rayHitFront->shape)
	{
		frontDistCurr = rayHitFront->distance;
		frontDelta = frontDistCurr - frontDistPrev;
	}

	//
	aiState = E_SpeedStateFront;

	if ((frontDelta < AI_value) || (frontDistCurr < AI_distanceMin))
	{
		if (frontDistCurr < AI_distanceFront)
		{
			aiState = E_SpeedStateBack;
		}
	}

	if ((backDelta < AI_value) || (backDistCurr < AI_distanceMin))
	{
		if (backDistCurr < AI_distanceBack)
		{
			aiState = E_SpeedStateFront;
		}
	}


//	std::cout << aiState << std::endl;

	//
	frontDistPrev = frontDistCurr;
	backDistPrev = backDistCurr;

	SetBitKey(eBIT_KEY::E_BIT_UP, aiState == E_SpeedStateFront);
	SetBitKey(eBIT_KEY::E_BIT_DOWN, aiState == E_SpeedStateBack);
}
