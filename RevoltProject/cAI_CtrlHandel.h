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
	const float F___DistRange = 20.f;
	const float LRF_DistRange = 20.f;
	const float LR__DistRange = 5.f;

	//회전값에 적용시킬 비율
	const float F___DistValue = 0.5f;
	const float LRF_DistValue = 0.1f;
	const float LR__DistValue = 0.5f;


	// 0.5 > 0 < 0.5
	float HandleValue;
	enum AIHandleState { E_AIHandle_L, E_AIHandle_F, E_AIHandle_R };
	AIHandleState aiState;


	cAI_CtrlHandel();
	~cAI_CtrlHandel();

	void Update();
	void Render();

};

