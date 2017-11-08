#include "stdafx.h"
#include "cAI_CtrlSpeed.h"
#include "cPhysXManager.h"
#include "cCar.h"

cAI_CtrlSpeed::cAI_CtrlSpeed()
{
	rayHit = NULL;
}


cAI_CtrlSpeed::~cAI_CtrlSpeed()
{

}

void cAI_CtrlSpeed::Update()
{
	rayHit = &RAYCAST(m_pAICar->GetPhysXData()->GetPositionToNxVec3() + NxVec3(0,0.3,0) , NxVec3(1, 0, 0));

	if (rayHit->shape)
	{
		float distance = rayHit->distance;
		std::cout << distance << std::endl;

		if (distance < 5.f)
		{

		}
	}
}
