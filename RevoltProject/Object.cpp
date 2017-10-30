#include "stdafx.h"
#include "Object.h"

Object::Object()
{
	m_pMeshData = new cMesh;
	m_PhysXData = new cPhysX;
}

Object::~Object()
{
}

void Object::Setup()
{
}

void Object::Destroy()
{
	if (m_pMeshData) m_pMeshData->Destory(); m_pMeshData = NULL;
	if (m_PhysXData) m_PhysXData->Destory(); m_PhysXData = NULL;
}

void Object::Update()
{
}

void Object::LastUpdate()
{
	if (GetPhysXData())
	{
		//물리데이터와 메쉬 데이터동기화

		cTransform::SetPosition(GetPhysXData()->m_pActor->getGlobalPosition());

		NxF32 NxMat[9] = { 1,0,0,0,1,0,0,0,1 };
		GetPhysXData()->m_pActor->getGlobalPose().M.getColumnMajor(NxMat);

		cTransform::SetQuaternion(NxMat);

	}
}

void Object::Render()
{
	if (GetPhysXData()) GetPhysXData()->m_pUserData->Init();

	MgrD3DDevice->SetTransform(D3DTS_WORLD, &cTransform::GetMatrix());
	if (GetMeshData()) GetMeshData()->Render();
}
