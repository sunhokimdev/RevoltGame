#include "stdafx.h"
#include "cPhysX.h"


cPhysX::cPhysX()
{
	m_pActor = NULL;
	m_pUserData = new USERDATA;

	actorName = "";
	m_position = NxVec3(0, 0, 0);
	m_sizeValue = NxVec3(0.5, 0.5, 0.5);
	m_dirValue = NxVec3(0, 0, 1);

//	m_localPos = NxVec3(0, 0, 0);
	m_localPose.t = NxVec3(0,0,0);
	m_worldPose.t = NxVec3(0, 0, 0);
	NxF32 mat[9] = { 1,0,0,0,1,0,0,0,1 };
	m_localPose.M.setColumnMajor(mat);
	m_worldPose.M.setColumnMajor(mat);
	m_type = NX_SHAPE_SPHERE;
}


cPhysX::~cPhysX()
{
}
