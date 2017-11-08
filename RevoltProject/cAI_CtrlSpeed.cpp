#include "stdafx.h"
#include "cAI_CtrlSpeed.h"
#include "cPhysXManager.h"
#include "cCar.h"

cAI_CtrlSpeed::cAI_CtrlSpeed()
{
	rayHitFront = NULL;

	goFront = true;
	goback = false;
}


cAI_CtrlSpeed::~cAI_CtrlSpeed()
{

}

void cAI_CtrlSpeed::Update()
{
	NxVec3 raypos = m_pAICar->GetPhysXData()->GetPositionToNxVec3() + NxVec3(0, 0.2, 0);
	NxVec3 dirFront = m_pAICar->WheelArrow(0, false); dirFront.y = 0;
	NxVec3 dirBack= m_pAICar->WheelArrow(0, true); dirBack.y = 0;
	dirFront.normalize();
	dirBack.normalize();

	rayHitFront = &RAYCAST(raypos, dirFront, 100);
	rayHitBack = &RAYCAST(raypos, dirBack, 100);

	if (rayHitFront->shape)
	{
		frontPointCurr = rayHitFront->distance;
		frontDelta = frontPointCurr - frontPointPrev;
	}
	if (rayHitFront->shape)
	{
		backPointCurr = rayHitBack->distance;
		backDelta = backPointCurr - backPointPrev;
	}

	if (rayHitBack->distance < AI_distance || AI_distanceMin)
	{
		if (backDelta < -AI_value)
		{
			goFront = true;
			goback = false;
		}
		std::cout << "Up" << std::endl;
	}
	else if (rayHitFront->distance < AI_distance)
	{
		if (frontDelta < -AI_value || AI_distanceMin)
		{
			goFront = false;
			goback = true;
		}
		std::cout << "Down" << std::endl;
	}




	

	frontPointPrev = frontPointCurr;
	backPointPrev = backPointCurr;

	SetBitKey(eBIT_KEY::E_BIT_DOWN, goback);
	SetBitKey(eBIT_KEY::E_BIT_UP, goFront);
}
