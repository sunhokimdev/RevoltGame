#pragma once
#include "cAI.h"

class cAI_Ctrl :
	public cAI
{
public:
	cAI_Ctrl();
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
	void UseItem();

	float VecHandleValue();
	float VecSpeedValue();
};

