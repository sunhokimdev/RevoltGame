#pragma once

#include <fstream>
#include <iostream>
#include "cStringUtil.h"
#include "cPhysXManager.h"

class cPhysX
{
public:
	NxActor*  m_pActor;		//save/load (X)		->월드좌표 저장
	USERDATA* m_pUserData;	//save/load (X)

	NxVec3 m_localPos;

	cPhysX();
	~cPhysX();

	void SetPosition(NxVec3 pos);
	void SetPosition(D3DXVECTOR3 vec3);
	void SetRotation(D3DXMATRIX mat16);
	void SetRotation(NxF32* nxf32);
	void SetRotation(NxMat33 mat33);
	void SetLocalRotation(D3DXMATRIX mat16);
	NxVec3 GetPositionToNxVec3();
	D3DXVECTOR3 GetPositionToD3DXVec3();
	NxMat33 GetRotationToNxMat33();
	D3DXMATRIXA16 GetRotationToD3DXMat16();
	void Destroy();

#define TAB	'\t'
#define SPACE ' '
#define POPDATA Data[sI++]

};

