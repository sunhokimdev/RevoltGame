#pragma once
#include "cAI.h"
class cAI_CtrlHandel :
	public cAI
{
public:

	float LRF_F_RateValue;
	float LRF_D_RateVAlue;
	float LR__F_RateValue;
	float LR__D_RateVAlue;

	// ~ -1 ~ 0 ~ 1 ~
	float HandleValue;
	
	//CheckBoxPoint() 애서 한번에 방향을 체크할 체크박스의 수 (1~3) 그 외의 값은 (return 0)
	int FindDirNum;

	//핸들 체크의 세밀도
	float HandleDistance;

	//체크박스 터치를 감지하기 위한 변수

	D3DXVECTOR3 BoxDir;
	D3DXVECTOR3 RealDir;

	bool isPoint;


	cAI_CtrlHandel(AI_DATA pData);
	~cAI_CtrlHandel();

	void Update();
	void Render();

	//ray 거리에 따른 비율값

	float CheckBoxPoint(D3DXVECTOR3 dir );
	float CheckBoxPoint(NxVec3 dir );
};

