#include "stdafx.h"
#include "cAI.h"
#include "cCar.h"

#include "cAI_CtrlHandel.h"
#include "cAI_CtrlSpeed.h"[]

cAI::cAI()
{
	AITag = AI_TAG_MASTER;
}


cAI::~cAI()
{
}

void cAI::SetCar(cCar * pAICar)
{
	m_pAICar = pAICar;
	m_pAICarActor = m_pAICar->GetPhysXData()->m_pActor;

	//{
	//	cAI_CtrlSpeed* p = new cAI_CtrlSpeed;
	//	this->AddAICtrl(p);
	//}
	{
		cAI_CtrlHandel* p = new cAI_CtrlHandel;
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


}
void cAI::Destroy()
{
	for each(cAI* p in chiledAI)
	{
		p->Destroy();
	}
}
void cAI::AddAICtrl(cAI * pAI)
{
	pAI->m_pAICar = this->m_pAICar;
	pAI->m_pAICarActor = this->m_pAICarActor;
	chiledAI.push_back(pAI);
}

void cAI::SetBitKey(eBIT_KEY keySet, bool onoff)
{
	m_pAICar->INPUT_KEY[keySet] = onoff;
}

bool cAI::GetBytKey(eBIT_KEY keyGet)
{
	return m_pAICar->INPUT_KEY[keyGet];
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
