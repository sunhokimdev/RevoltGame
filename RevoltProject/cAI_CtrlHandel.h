#pragma once
#include "cAI.h"
class cAI_CtrlHandel :
	public cAI
{
public:

	//LPD3DXMESH* pMesh;
	


	//Ray
	NxRaycastHit* F__Hit;
	NxRaycastHit* LF_Hit;
	NxRaycastHit* RF_Hit;
	NxRaycastHit* L__Hit;
	NxRaycastHit* R__Hit;

	//Pos
	D3DXVECTOR3 F__Pos;
	D3DXVECTOR3 LF_Pos;
	D3DXVECTOR3 RF_Pos;
	D3DXVECTOR3 L__Pos;
	D3DXVECTOR3 R__Pos;

	//Dist
	float F__Dist;
	float LF_Dist;
	float RF_Dist;
	float L__Dist;
	float R__Dist;

	//distRange;
	const float F___DistRange = 30.f;
	const float LRF_DistRange = 30.f;
	const float LR__DistRange = 20.f;

	//회전값에 적용시킬 비율
	const float F___DistValue = 1.0f;
	const float LRF_DistValue = 1.7f;
	const float LR__DistValue = 1.3f;


	// -1 ~ 0 ~ 1
	float HandleValue;

	AIHandleState aiState;


	cAI_CtrlHandel();
	~cAI_CtrlHandel();

	void Update();
	void Render();


	float ScaleValue(float dist, float Scale);
	float CheckBoxPoint(D3DXVECTOR3 dir);
	float CheckBoxPoint(NxVec3 dir);
};

