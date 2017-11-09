#include "stdafx.h"
#include "cAI.h"
#include "cCar.h"

#include "cAI_CtrlHandel.h"
#include "cAI_CtrlSpeed.h"
#include "cAI_CtrlFlip.h"

cAI::cAI()
{
	AITag = AI_TAG_MASTER;
	pParent = NULL;
}


cAI::~cAI()
{
}

void cAI::SetCar(cCar * pAICar)
{
	//pMesh = new ID3DXMesh;
	D3DXCreateSphere(g_pD3DDevice, 0.5, 8, 8, &pMesh, NULL);

	m_pAICar = pAICar;
	m_pAICarActor = m_pAICar->GetPhysXData()->m_pActor;

	{
		cAI_CtrlSpeed* p = new cAI_CtrlSpeed;
		this->AddAICtrl(p);
	}
	{
		cAI_CtrlHandel* p = new cAI_CtrlHandel;
		this->AddAICtrl(p);
	}
	{
		cAI_CtrlFlip* p = new cAI_CtrlFlip;
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
	pAI->pMesh = this->pMesh;
	pAI->pParent = this;
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

void cAI::RayHitPos(NxRaycastHit* Ray, D3DXVECTOR3* pos)
{
	if (Ray->shape)
	{
		NxVec3 Nx = Ray->worldImpact;
		*pos = D3DXVECTOR3(Nx.x, Nx.y, Nx.z);
	}
	else
	{
	//	*pos = D3DXVECTOR3(0, 0, 0);
	}
}

void cAI::RayHitDist(NxRaycastHit * Ray, float * dist)
{
	if (Ray->shape)
	{
		*dist = Ray->distance;
	}
	else
	{
		//	*pos = D3DXVECTOR3(0, 0, 0);
	}
}

cAI * cAI::FindMaster()
{
	if (this->pParent == NULL)
	{
		return this;
	}
	else
	{
		return this->pParent->FindMaster();
	}
}

cAI * cAI::FindAITag(AI_TAG tag)
{
	for each(cAI* p in chiledAI)
	{
		if (p->AITag == tag)
			return p;
	}
	return nullptr;
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
