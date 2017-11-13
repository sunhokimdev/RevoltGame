#include "stdafx.h"
#include "cAI_CtrlSpeed.h"
#include "cAI_Master.h"
#include "cCar.h"

cAI_CtrlSpeed::cAI_CtrlSpeed()
{
	F___DistRange = 10;		//인지범위 
	B___DistRange = 5;		//인지범위 
	Min_DistRange = 3.f;	//무조건 유지하려는 거리
	Min_LRDistRange = 1.5f;

	isBack = false;
	isRepos = false;
	ReposTimeCount = 0.0f;
	ReposTime = 5.0f;
}


cAI_CtrlSpeed::~cAI_CtrlSpeed()
{

}

void cAI_CtrlSpeed::Update()
{
	float F__Dist = ((cAI_Ray*)(*familyAI)[AI_TAG_RAY])->Ray_F__.Distance();
	float B__Dist = ((cAI_Ray*)(*familyAI)[AI_TAG_RAY])->Ray_B__.Distance();
	float LF_Dist = ((cAI_Ray*)(*familyAI)[AI_TAG_RAY])->Ray_LF_.Distance();
	float RF_Dist = ((cAI_Ray*)(*familyAI)[AI_TAG_RAY])->Ray_RF_.Distance();

	float rpmRate = GetRpmRate();
	//	rpmRate = fmax(rpmRate, 0.1f);


	if (1.0f > ScaleValue(F__Dist, F___DistRange * fmax(abs(rpmRate), 0.5f)))
	{
		//감속, 후진
		SpeedValue = -1.0f;
		if (abs(rpmRate) < 0.05)
		{
			isBack = true;
		}
	}
	else if (1.0f > ScaleValue(B__Dist, B___DistRange * fmax(abs(rpmRate), 0.5f)))
	{
		SpeedValue = 1.0f;
	}
	else
	{
		SpeedValue = 1.f;
	}

	//std::cout << SpeedValue << std::endl;
	if (LF_Dist < Min_LRDistRange || RF_Dist < Min_LRDistRange)
	{
		if (rpmRate > 0) SpeedValue = -1.f;
		if (rpmRate < 0) SpeedValue = 1.f;
	}


	//강제 후진
	if (isBack)
	{
		ReposTimeCount += g_pTimeManager->GetElapsedTime();
		SpeedValue = -1.0f;
		if (F__Dist > F___DistRange * 2.0f)
		{
			isBack = false;
		}
		else if (((B___DistRange * 0.5f / F___DistRange * 2.0f) > (B__Dist / F__Dist)))
		{
			isBack = false;
		}

	}
	else if (abs(rpmRate) < 0.1f)
	{
		ReposTimeCount+= g_pTimeManager->GetElapsedTime();
	}
	else
	{
		ReposTimeCount = 0.0f;
	}


	if (ReposTimeCount > ReposTime)
	{
		isRepos = true;
		ReposTimeCount = 0.0f;
	}
}

