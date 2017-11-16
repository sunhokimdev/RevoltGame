#include "stdafx.h"
#include "cAI_Master.h"
#include "cCar.h"

cAI_Master::cAI_Master()
{

}


cAI_Master::~cAI_Master()
{
}

void cAI_Master::Setup(AI_DATA pData)
{
	AIData = pData;
	familyAI.resize(AI_TAG_END___);

	//AI 선언 클래스
	familyAI[AI_TAG_RAY] = new cAI_Ray();
	familyAI[AI_TAG_SPEED] = new cAI_CtrlSpeed();
	familyAI[AI_TAG_HANDLE] = new cAI_CtrlHandel();
	familyAI[AI_TAG_USEITEM] = new cAI_CtrlUseItem();
	familyAI[AI_TAG_FLIP] = new cAI_CtrlFlip();
	familyAI[AI_TAG_COMPET] = new cAI_CtrlCompete();

	//AI 동작 클래스
	familyAI[AI_TAG_CTRL] = new cAI_Ctrl();

	//AI 클래스 연결
	for each(cAI*p in familyAI)
	{
		p->AI_Data = &AIData;
		p->familyAI = &familyAI;
	}
}

void cAI_Master::Destroy()
{
	for each(cAI*p in familyAI)
	{
		p->Destroy();
		SAFE_DELETE(p);
	}
	familyAI.clear();
}

void cAI_Master::Update()
{
	AIData.pCar->INPUT_KEY.reset();

	for each(cAI*p in familyAI)
	{
		p->Update();
	}
}

void cAI_Master::Render()
{
	if (!IS_DEBUG_RENDER) return;
	for each(cAI*p in familyAI)
	{
		p->Render();
	}
}
