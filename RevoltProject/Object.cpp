#include "stdafx.h"
#include "Object.h"

Object::Object()
{
	//m_pMeshData = new cMesh;
	//m_PhysXData = new cPhysX;
	m_pMeshData = NULL;
	m_PhysXData = NULL;
}

Object::~Object()
{
}

void Object::Setup()
{
}

void Object::Destroy()
{
	if (m_pMeshData)
	{
		m_pMeshData->Destroy();
		delete(m_pMeshData);
	}
	if (m_PhysXData)
	{
		m_PhysXData->Destroy();
		delete(m_PhysXData);
	}
}

void Object::Update()
{
}

void Object::LastUpdate()
{
	if (GetPhysXData())
	{
		//물리데이터와 메쉬 데이터동기화

	
		cTransform::SetPosition(GetPhysXData()->m_pActor->getGlobalPosition() - GetPhysXData()->m_localPos);

		NxF32 NxMat[9] = { 1,0,0,0,1,0,0,0,1 };
		GetPhysXData()->m_pActor->getGlobalPose().M.getColumnMajor(NxMat);

		cTransform::SetQuaternion(NxMat);
	}
}

void Object::Render()
{
	if (GetPhysXData()) if(GetPhysXData()->m_pUserData) GetPhysXData()->m_pUserData->Reset();

	MgrD3DDevice->SetTransform(D3DTS_WORLD, &cTransform::GetMatrix());
	if (GetMeshData()) GetMeshData()->Render();
}

void Object::SetMeshData(cMesh* pMesh) {
	if (pMesh)
	{
		//if (m_pMeshData)
		//{
		//	m_pMeshData->Destroy();
		//}
		m_pMeshData = pMesh;
	}
}

void Object::SetPhysXData(cPhysX* pPhysX)
{
	if (pPhysX)
	{
		//if (m_PhysXData)
		//{
		//	m_PhysXData->Destroy();
		//	delete(m_PhysXData);
		//}
		m_PhysXData = pPhysX;

		//if (m_PhysXData)
		//{
		//	m_PhysXData->Destroy();
		//}

		/*m_PhysXData->m_pActor = pPhysX->m_pActor;
		m_PhysXData->m_pUserData = pPhysX->m_pUserData;*/
	}
}