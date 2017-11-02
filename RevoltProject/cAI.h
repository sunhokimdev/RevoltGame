#pragma once
#include "cPhysX.h"

class cCar;

class cAI
{
public:
	cCar* m_pAICar;
	NxMat34* m_pAICarPose;

	cAI();
	~cAI();

	virtual void SetCar(cCar* m_pAICar);
	virtual void Update();
	virtual void Render();

	void TEST()
	{
		
	}
};

