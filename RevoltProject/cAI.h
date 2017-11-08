#pragma once
#include "cPhysX.h"

//#include "cAI_CtrlHandel.h"
//#include "cAI_CtrlSpeed.h"

class cCar;

class cAI
{
public:
	cCar* m_pAICar;
	NxActor* m_pAICarActor;

	std::vector<cAI*> chiledAI;

	cAI();
	~cAI();

	virtual void SetCar(cCar* m_pAICar);
	virtual void Destory();
	virtual void Update();
	virtual void Render();
	virtual void AddAICtrl(cAI* pAI);

	void TEST()
	{

	}
};

