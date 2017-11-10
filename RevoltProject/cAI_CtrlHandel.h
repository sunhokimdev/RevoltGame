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
	float F___DistRange;
	float LRF_DistRange;
	float LR__DistRange;

	//회전값에 적용시킬 비율
//	float F___DistValue;
	float LRF_DistValue;
	float LR__DistValue;


	// -1 ~ 0 ~ 1
	float HandleValue;
	//핸들 체크의 세밀도
	const float HandleDistance = 0.2f;

	AIHandleState aiState;


	cAI_CtrlHandel();
	~cAI_CtrlHandel();

	void Update();
	void Render();

	//ray 거리에 따른 비율값
	float ScaleValue(float dist, float Scale);
	float FrontValue(float dist, float value = 1.0f);

	//CheckBoxPoint() 애서 한번에 방향을 체크할 체크박스의 수 (1~3) 그 외의 값은 (return 0)
	int FindDirNum;
	float CheckBoxPoint(D3DXVECTOR3 dir);
	float CheckBoxPoint(NxVec3 dir);
};

