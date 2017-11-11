#pragma once
#include "cAI.h"
class cAI_CtrlSpeed :
	public cAI
{
public:

	float F___DistRange;		//인지범위 
	float B___DistRange;		//인지범위 

	float Min_DistRange;		//무조건 유지하려는 거리
	float Min_LRDistRange;		
	//AISpeedState aiState;
	float SpeedValue;

	bool isBack;

	float BackTime;
	float ReposTime;

	bool isRepos;

public:
	cAI_CtrlSpeed(AI_DATA pData);
	~cAI_CtrlSpeed();

	void Update();
};

