#include "stdafx.h"
#include "cAI.h"
#include "cCar.h"
#include "cCheckBox.h"
#include "cTrack.h"


#include "cAI_CtrlHandel.h"
#include "cAI_CtrlSpeed.h"
#include "cAI_CtrlFlip.h"

cAI::cAI()
{
	AI_Mesh = NULL;
}


cAI::~cAI()
{
}

void cAI::Setup()
{
}

void cAI::Destory()
{
	if (AI_Mesh) AI_Mesh->Release();
	AI_Data.Destory();
	familyAI = NULL;
}

void cAI::Update()
{
}

void cAI::Render()
{
}

cCheckBox * cAI::CurrentCheckBox()
{
	return (cCheckBox*)(*(AI_Data.pCar)->m_pTrack->GetCheckBoxsPt())[AI_Data.pCar->GetAICheckBoxID()];
}

float cAI::ScaleValue(float value, float Total, float multiValue)
{
	float rate = (value * multiValue / Total);
//	rate = fmin(rate, 1.0f);
//	rate = fmax(rate, -1.0f);
	return rate;
}
