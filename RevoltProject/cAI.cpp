#include "stdafx.h"
#include "cAI.h"
#include "cCar.h"

cAI::cAI()
{
}


cAI::~cAI()
{
}

void cAI::SetCar(cCar * pAICar)
{
	m_pAICar = pAICar;
	m_pAICarPose = &m_pAICar->GetPhysXData()->m_pActor->getGlobalPose();
}

void cAI::Update()
{
}

void cAI::Render()
{

}
