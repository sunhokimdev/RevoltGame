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
}

void cSkidMark::Render()
{
	D3DMATERIAL9 material;
	material.Ambient = CX_BLACK;
	material.Diffuse = CX_BLACK;
	material.Specular = CX_BLACK;
	material.Emissive = CX_BLACK;
	g_pD3DDevice->SetMaterial(&material);

	for each(auto rubber in m_vecRubbers)
	{
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &rubber.matLocal);
		rubber.mesh->DrawSubset(0);
	}
	
}

void cSkidMark::Destory()
{
	m_vecRubbers.clear();
}

void cSkidMark::DrawSkidMark()
{
	stRubber rubber;
	rubber.position = m_pCar->GetPosition();
	rubber.position.y += 0.5f;
	rubber.matR = m_pCar->GetCarRotMatrix();
	//rubber.matLocal = m_pCar->GetMatrix();
	D3DXMATRIXA16 mat, matT;
	D3DXMatrixIdentity(&rubber.matLocal);
	//rubber.Setup();
	D3DXMatrixTranslation(&matT, rubber.position.x, rubber.position.y, rubber.position.z);
	rubber.matLocal = rubber.matR * matT;
	
	D3DXCreateSphere(g_pD3DDevice, 0.1f, 20, 20, &rubber.mesh, 0);
	//D3DXCreateBox(g_pD3DDevice, 0.3f, 0, 0.1f, &rubber.mesh, 0);
	m_vecRubbers.push_back(rubber);
}