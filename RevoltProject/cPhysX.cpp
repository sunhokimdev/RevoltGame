#include "stdafx.h"
#include "cPhysX.h"


cPhysX::cPhysX()
{
	m_pActor = NULL;
	m_pUserData = NULL;
}


cPhysX::~cPhysX()
{
}

void cPhysX::SetPosition(NxVec3 pos)
{
	m_pActor->setGlobalPosition(pos);
}
void cPhysX::SetPosition(D3DXVECTOR3 vec3)
{
	SetPosition(NxVec3(vec3.x, vec3.y, vec3.z));
}

void cPhysX::SetRotation(D3DXMATRIX mat16)
{
	NxF32 nxf[9] = { 1,0,0,0,1,0,0,0,1 };

	nxf[0] = mat16._11;
	nxf[1] = mat16._12;
	nxf[2] = mat16._13;
	nxf[3] = mat16._21;
	nxf[4] = mat16._22;
	nxf[5] = mat16._23;
	nxf[6] = mat16._31;
	nxf[7] = mat16._32;
	nxf[8] = mat16._33;

	SetRotation(nxf);


	//	m_pActor->desc
}
void cPhysX::SetRotation(NxF32* nxf32)
{
	NxMat33 mat33;
	mat33.setColumnMajor(nxf32);
	SetRotation(mat33);
}
void cPhysX::SetRotation(NxMat33 mat33)
{
	m_pActor->getGlobalPose().M = mat33;
}

void cPhysX::SetLocalRotation(D3DXMATRIX mat16)
{
	NxF32 nxf[9] = { 1,0,0,0,1,0,0,0,1 };

	nxf[0] = mat16._11;
	nxf[1] = mat16._12;
	nxf[2] = mat16._13;
	nxf[3] = mat16._21;
	nxf[4] = mat16._22;
	nxf[5] = mat16._23;
	nxf[6] = mat16._31;
	nxf[7] = mat16._32;
	nxf[8] = mat16._33;

	SetLocalRotation(nxf);
}
NxVec3 cPhysX::GetPositionToNxVec3()
{
	return m_pActor->getGlobalPose().t;
}
D3DXVECTOR3 cPhysX::GetPositionToD3DXVec3()
{
	NxVec3 pos = m_pActor->getGlobalPose().t;
	return D3DXVECTOR3(pos.x, pos.y, pos.z);
}
NxMat33 cPhysX::GetRotationToNxMat33()
{
	return m_pActor->getGlobalPose().M;
}
D3DXMATRIXA16 cPhysX::GetRotationToD3DXMat16()
{
	D3DXMATRIXA16 mat16;
	D3DXMatrixIdentity(&mat16);

	NxF32 mat[9] = { 1,0,0,0,1,0,0,0,1 };
	m_pActor->getGlobalPose().M.getColumnMajor(mat);

	mat16._11 = mat[0];
	mat16._12 = mat[1];
	mat16._13 = mat[2];
	mat16._21 = mat[3];
	mat16._22 = mat[4];
	mat16._23 = mat[5];
	mat16._31 = mat[6];
	mat16._32 = mat[7];
	mat16._33 = mat[8];

	return mat16;
}

void cPhysX::Destroy()
{
	if (m_pActor) MgrPhysXScene->releaseActor(*m_pActor);
	m_pActor = NULL;

	SAFE_DELETE(m_pUserData);
}