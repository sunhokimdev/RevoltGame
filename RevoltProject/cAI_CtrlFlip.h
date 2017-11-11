#pragma once
#include "cAI.h"
class cAI_CtrlFlip :
	public cAI
{
public:
	cAI_CtrlFlip(AI_DATA pData);
	~cAI_CtrlFlip();
	
	float flipTime;
	float flipTrueTime;

	bool isFlip;

	void Update();
	void Render();
};

