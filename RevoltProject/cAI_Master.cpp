#include "stdafx.h"
#include "cAI_Master.h"
#include "cCar.h"

cAI_Master::cAI_Master()
{
	updateTime = 0.0f;

	fpsTime = .0f / 60.f;
}


cAI_Master::~cAI_Master()
{
}

void cAI_Master::Setup(AI_DATA pData)
{
	AIData = pData;
	familyAI.resize(AI_TAG_END___);
	familyAI[AI_TAG_RAY] = new cAI_Ray(pData);
	familyAI[AI_TAG_SPEED] = new cAI_CtrlSpeed(pData);
	familyAI[AI_TAG_HANDLE] = new cAI_CtrlHandel(pData);
	familyAI[AI_TAG_FLIP] = new cAI_CtrlFlip(pData);
	familyAI[AI_TAG_CTRL] = new cAI_Ctrl(pData);

	for each(cAI*p in familyAI)
	{
		p->familyAI = &familyAI;
	}
}

void cAI_Master::Destory()
{
	for each(cAI*p in familyAI)
	{
		p->Destory();
	}
	familyAI.clear();
}

void cAI_Master::Update()
{
	if (updateTime < fpsTime)
	{
		updateTime += g_pTimeManager->GetElapsedTime();
		return;
	}
	updateTime  = 0.f;
	AIData.pCar->INPUT_KEY.reset();

	for each(cAI*p in familyAI)
	{
		p->Update();
	}
}

void cAI_Master::Render()
{
	for each(cAI*p in familyAI)
	{
		p->Render();
	}
}
