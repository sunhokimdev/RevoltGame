#include "stdafx.h"
#include "cAI_CtrlSpeed.h"
#include "cPhysXManager.h"
#include "cCar.h"

cAI_CtrlSpeed::cAI_CtrlSpeed()
{

	if (pCollider->m_pUserData == NULL)pCollider->m_pUserData = new USERDATA;
	pCollider->m_pActor = MgrPhysX->CreateActor(NX_SHAPE_BOX, NxVec3(0, 0, 0), NULL, NxVec3(0.5f, 0.5f, 0.5f), E_PHYSX_MATERIAL_NONE, pCollider->m_pUserData, true, true, false);

}


cAI_CtrlSpeed::~cAI_CtrlSpeed()
{

}

void cAI_CtrlSpeed::Update()
{
//	NxReal speed = m_pAICar->GetNxVehicle()->;

	NxMat34 boxPose = *m_pAICarPose;
	boxPose.t += center;
	pCollider->m_pActor->setGlobalPose(boxPose); //위치 초기화


}
