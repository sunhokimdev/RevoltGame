#pragma once
#include "cAI.h"
class cAI_CtrlSpeed :
	public cAI
{
private:
	//	cPhysX* pCollider;
	LPD3DXMESH* pMesh;

	NxRaycastHit* rayHitFront;
	NxRaycastHit* rayHitBack;

	D3DXVECTOR3 FrontPos;
	D3DXVECTOR3 BackPos;

	float frontDistPrev;
	float frontDistCurr;
	float frontDelta;

	float backDistPrev;
	float backDistCurr;
	float backDelta;


	enum AISpeedState { E_SpeedStateFront, E_SpeedStateBack };
	AISpeedState aiState;


	float AI_distanceFront;// = 5;		//인지범위 
	float AI_distanceBack;// = 3;		//인지범위 
	float AI_value;// = 0.2f;		//delta 의 인지범위
	float AI_distanceMin;// = 2.f;	//무조건 유지하려는 거리


public:
	cAI_CtrlSpeed();
	~cAI_CtrlSpeed();

	void Update();
	void Render();
};

