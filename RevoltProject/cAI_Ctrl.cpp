#include "stdafx.h"
#include "cAI_Ctrl.h"
#include "cAI_Master.h"

#include "cCar.h"


cAI_Ctrl::cAI_Ctrl()
{
	vecHandleValue.resize(vecSize);
	vecSpeedValue.resize(vecSize);
	handleIndex = 0;
	speedIndex = 0;
}


cAI_Ctrl::~cAI_Ctrl()
{
}

void cAI_Ctrl::Update()
{
	Speed();
	Handle();
	UseItem();
	Flip();
	Repos();
}

void cAI_Ctrl::Speed()
{
	cAI_CtrlSpeed* pSpeed = ((cAI_CtrlSpeed*)(*familyAI)[AI_TAG_SPEED]);

	vecSpeedValue[speedIndex++] = pSpeed->SpeedValue;
	if (speedIndex == vecSize) speedIndex = 0;
	float value = VecSpeedValue();

//	std::cout << value << std::endl;

	AI_Data->pCar->INPUT_KEY[eBIT_KEY::E_BIT_UP___] = (value >= 0.0f);
	AI_Data->pCar->INPUT_KEY[eBIT_KEY::E_BIT_DOWN_] = !(value >= 0.0f);
}

void cAI_Ctrl::Handle()
{
	cAI_CtrlHandel* pHandle = ((cAI_CtrlHandel*)(*familyAI)[AI_TAG_HANDLE]);
	cAI_CtrlCompete* pCompete = ((cAI_CtrlCompete*)(*familyAI)[AI_TAG_COMPET]);
	float HandleValue = 0.0f;

	if (AI_Data->pCar->GetRpm() < 0) pHandle->HandleValue *= -1;

	vecHandleValue[handleIndex++] = pHandle->HandleValue;
	if (handleIndex == vecSize) handleIndex = 0;

	HandleValue = VecHandleValue();
	HandleValue += pCompete->HandleValue;

	float speedValue = VecSpeedValue();
	speedValue = fmin(0.f, abs(speedValue));


	if (HandleValue < -pHandle->HandleDistance * speedValue) AI_Data->pCar->INPUT_KEY[eBIT_KEY::E_BIT_LEFT_] = true;
	if (HandleValue > +pHandle->HandleDistance * speedValue) AI_Data->pCar->INPUT_KEY[eBIT_KEY::E_BIT_RIGHT] = true;
}


void cAI_Ctrl::Flip()
{
	AI_Data->pCar->INPUT_KEY[eBIT_KEY::E_BIT_FLIP_] = ((cAI_CtrlFlip*)(*familyAI)[AI_TAG_FLIP])->isFlip;
}

void cAI_Ctrl::Repos()
{
	if(((cAI_CtrlSpeed*)(*familyAI)[AI_TAG_SPEED])->isRepos)
	{
		AI_Data->pCar->INPUT_KEY[eBIT_KEY::E_BIT_REPOS] = true;
		((cAI_CtrlSpeed*)(*familyAI)[AI_TAG_SPEED])->isBack = false;
		((cAI_CtrlSpeed*)(*familyAI)[AI_TAG_SPEED])->isRepos = false;
		((cAI_CtrlHandel*)(*familyAI)[AI_TAG_HANDLE])->isPoint = false;
	}
}

void cAI_Ctrl::UseItem()
{
	if (((cAI_CtrlUseItem*)(*familyAI)[AI_TAG_USEITEM])->m_isFire)
	{
		AI_Data->pCar->INPUT_KEY[eBIT_KEY::E_BIT_ITEM_] = true;
		((cAI_CtrlUseItem*)(*familyAI)[AI_TAG_USEITEM])->m_isFire = false;
	}
}

float cAI_Ctrl::VecHandleValue()
{
	float value = 0.0f;
	for each(float f in vecHandleValue)
	{
		value += f;
	}
	return (float)((float)value / (float)vecHandleValue.size());
}

float cAI_Ctrl::VecSpeedValue()
{
	float value = 0.0f;
	for each(float f in vecSpeedValue)
	{
		value += f;
	}
	return (float)((float)value / (float)vecSpeedValue.size());

}
