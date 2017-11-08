#pragma once
#include "cAI.h"
class cAI_CtrlSpeed :
	public cAI
{
private:
//	cPhysX* pCollider;

	NxRaycastHit* rayHit;

	NxVec3 center;
	
public:
	cAI_CtrlSpeed();
	~cAI_CtrlSpeed();

	void Update();
};

