#include "stdafx.h"
#include "cSkyBox.h"


cSkyBox::cSkyBox()
{
}

cSkyBox::~cSkyBox()
{
}

void cSkyBox::Setup()
{
	Object::Setup();
	m_pMeshData->LoadMesh("Maps/SkyBox", "SkyBox.obj");
}

void cSkyBox::Update()
{

}

void cSkyBox::Destroy()
{
	m_pMeshData->m_pMesh->Release();
}

void cSkyBox::Render()
{
	D3DXMATRIXA16 matS;
	D3DXMatrixIdentity(&matS);
	D3DXMatrixScaling(&matS, 10, 10, 10);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matS);
	m_pMeshData->Render();

}
