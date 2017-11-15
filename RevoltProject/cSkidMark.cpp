#include "stdafx.h"
#include "cSkidMark.h"
#include "cCar.h"

cSkidMark::cSkidMark()
{
}
cSkidMark::~cSkidMark()
{
}

void cSkidMark::Setup()
{
}

void cSkidMark::Update()
{
	for (int i = 0; i < m_vecRubbers.size(); i += 2)
	{
		float elpasedtime = g_pTimeManager->GetElapsedTime();
		m_vecRubbers[i+0].timer += elpasedtime;
		m_vecRubbers[i+1].timer += elpasedtime;

		if (m_vecRubbers[i].timer > 5)
		{
			m_vecRubbers.erase(m_vecRubbers.begin() + 1);
			m_vecRubbers.erase(m_vecRubbers.begin());
			break;
		}
	}
}

void cSkidMark::Render()
{
//	g_pD3DDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
//	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
//	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
//	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

	// Use alpha for transparency
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
//	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
//	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);



	D3DMATERIAL9 material;
	ZeroMemory(&material, sizeof(D3DMATERIAL9));
	material.Diffuse = D3DXCOLOR(0, 0, 0, 0.1);
	g_pD3DDevice->SetMaterial(&material);

	for (int i = 0; i < m_vecRubbers.size(); i++)
	{
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_vecRubbers[i].matLocal);
		m_vecRubbers[0].mesh->DrawSubset(0);
	}

	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
//	
//	g_pD3DDevice->SetRenderState(D3DRS_STENCILENABLE, false);

}

void cSkidMark::Destroy()
{
	m_vecRubbers.clear();
}

void cSkidMark::DrawSkidMark()
{
	stRubber rubberL,rubberR;

	//rubberL.matR = m_pCar->GetCarRotMatrix();
	rubberL.matR = m_pCar->GetMatrix(0, 1, 0);

	//rubberR.matR = m_pCar->GetCarRotMatrix();
	rubberR.matR = m_pCar->GetMatrix(0, 1, 0);

	D3DXVECTOR3 posWheelL = {
		m_pCar->GetNxVehicle()->getWheel(3)->getWheelPos().x,
		m_pCar->GetNxVehicle()->getWheel(3)->getWheelPos().y,
		m_pCar->GetNxVehicle()->getWheel(3)->getWheelPos().z
	};
	D3DXVECTOR3 posWheelR = {
		m_pCar->GetNxVehicle()->getWheel(2)->getWheelPos().x,
		m_pCar->GetNxVehicle()->getWheel(2)->getWheelPos().y,
		m_pCar->GetNxVehicle()->getWheel(2)->getWheelPos().z
	};

	D3DXVec3TransformCoord(&posWheelL, &posWheelL, &rubberL.matR);
	D3DXVec3TransformCoord(&posWheelR, &posWheelR, &rubberR.matR);

	D3DXVECTOR3 carpos = {
		m_pCar->GetPhysXData()->m_pActor->getGlobalPosition().x,
		m_pCar->GetPhysXData()->m_pActor->getGlobalPosition().y,
		m_pCar->GetPhysXData()->m_pActor->getGlobalPosition().z };

	rubberL.position = carpos + posWheelL;
	rubberR.position = carpos + posWheelR;

	rubberL.position.y += 0.001f;
	rubberR.position.y += 0.001f;
		
	D3DXMATRIXA16 matTL,matTR;
	D3DXMatrixIdentity(&rubberL.matLocal);
	D3DXMatrixIdentity(&rubberR.matLocal);

	//rubber.Setup();
	D3DXMatrixTranslation(&matTL, rubberL.position.x, rubberL.position.y, rubberL.position.z);
	D3DXMatrixTranslation(&matTR, rubberR.position.x, rubberR.position.y, rubberR.position.z);
	rubberL.matLocal = rubberL.matR * matTL;
	rubberR.matLocal = rubberR.matR * matTR;
	
	//D3DXCreateSphere(g_pD3DDevice, 0.05f, 20, 20, &rubberL.mesh, 0);
	//D3DXCreateSphere(g_pD3DDevice, 0.05f, 20, 20, &rubberR.mesh, 0);
	D3DXCreateBox(g_pD3DDevice, 0.1f, 0, 0.1f, &rubberL.mesh, 0);
	D3DXCreateBox(g_pD3DDevice, 0.1f, 0, 0.1f, &rubberR.mesh, 0);

	rubberL.timer = 0;
	rubberR.timer = 0;

	m_vecRubbers.push_back(rubberL);
	m_vecRubbers.push_back(rubberR);
}