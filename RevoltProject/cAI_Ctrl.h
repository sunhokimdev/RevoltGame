#pragma once
#include "cAI.h"

class cAI_Ctrl :
	public cAI
{
public:
	cAI_Ctrl(AI_DATA pData);
	~cAI_Ctrl();

	const int vecSize = 1;
	int handleIndex;
	std::vector<float> vecHandleValue;

	int speedIndex;
	std::vector<float> vecSpeedValue;

	void Update();

	void Speed();
	void Handle();
	void Flip();
	void Repos();

	float VecHandleValue();
	float VecSpeedValue();
};

