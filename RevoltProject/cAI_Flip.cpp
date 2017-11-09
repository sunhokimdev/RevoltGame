#include "stdafx.h"
#include "cAI_Flip.h"
#include "cCar.h"

cAI_Flip::cAI_Flip()
{
}


cAI_Flip::~cAI_Flip()
{
}

void cAI_Flip::Update()
{
	NxQuat quat = m_pAICarActor->getGlobalOrientationQuat();
	NxVec3 carUp = quat.transform(NxVec3(0, 1, 0), NxVec3(0, 0, 0));
	if (carUp.y > 0.0f)
	{
		if (m_pAICar->GetRpm() < 30.f)
		{
			
		}
	}
}

void cAI_Flip::Render()
{
}
