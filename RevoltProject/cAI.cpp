#include "stdafx.h"
#include "cAI.h"
#include "cCar.h"

#include "cAI_CtrlHandel.h"
#include "cAI_CtrlSpeed.h"[]

cAI::cAI()
{
}


cAI::~cAI()
{
}

void cAI::SetCar(cCar * pAICar)
{
	m_pAICar = pAICar;
	m_pAICarActor = m_pAICar->GetPhysXData()->m_pActor;

	{
		cAI_CtrlSpeed* p = new cAI_CtrlSpeed;
		this->AddAICtrl(p);
	}
//	{
//		cAI_CtrlHandel* p = new cAI_CtrlHandel;
//		this->AddAICtrl(p);
//	}
//	{
//		cAI_CtrlHandel* p = new cAI_CtrlHandel;
//		this->AddAICtrl(p);
//	}
//	{
//		cAI_CtrlHandel* p = new cAI_CtrlHandel;
//		this->AddAICtrl(p);
//	}
//	{
//		cAI_CtrlHandel* p = new cAI_CtrlHandel;
//		this->AddAICtrl(p);
//	}
//	{
//		cAI_CtrlHandel* p = new cAI_CtrlHandel;
//		this->AddAICtrl(p);
//	}


}
void cAI::Destory()
{
	for each(cAI* p in chiledAI)
	{
		p->Destory();
	}
}
void cAI::AddAICtrl(cAI * pAI)
{
	pAI->m_pAICar = this->m_pAICar;
	pAI->m_pAICarActor = this->m_pAICarActor;
	chiledAI.push_back(pAI);
}

void cAI::Update()
{
	for each(cAI* p in chiledAI)
	{
		p->Update();
	}
}

void cAI::Render()
{
	for each(cAI* p in chiledAI)
	{
		p->Render();
	}
}
