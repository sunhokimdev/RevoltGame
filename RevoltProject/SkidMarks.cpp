#include "stdafx.h"
#include "SkidMarks.h"
#include "UIImageView.h"

SkidMarks::SkidMarks()
{
}


SkidMarks::~SkidMarks()
{
}

void SkidMarks::Setup()
{
	m_pTexture = g_pTextureManager->GetTexture("Maps/Front/Image/blueRing.png");

	//D3DXCreateTextureFromFile(g_pD3DDevice, L"Maps/Front/Image/blueRing.png", &m_pTexture);

	ZeroMemory(&m_stMtlPlane, sizeof(D3DMATERIAL9));
	m_stMtlPlane.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_stMtlPlane.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_stMtlPlane.Specular = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);


	ST_PN_VERTEX v;
	v.n = D3DXVECTOR3(0, 1, 0);
	v.p = D3DXVECTOR3(-10, 0, -10);
	m_vecPlaneVertex.push_back(v);

	v.p = D3DXVECTOR3(-10, 0, 10);
	m_vecPlaneVertex.push_back(v);

	v.p = D3DXVECTOR3(10, 0, 10);
	m_vecPlaneVertex.push_back(v);

	v.p = D3DXVECTOR3(-10, 0, -10);
	m_vecPlaneVertex.push_back(v);

	v.p = D3DXVECTOR3(10, 0, 10);
	m_vecPlaneVertex.push_back(v);

	v.p = D3DXVECTOR3(10, 0, -10);
	m_vecPlaneVertex.push_back(v);
}

void SkidMarks::Update()
{
}

void SkidMarks::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);

	D3DXMATRIXA16 matWorld, matR;
	D3DXMatrixIdentity(&matWorld);

	D3DXMatrixRotationZ(&matR, D3DX_PI);

	matWorld = matWorld * matR;

	g_pD3DDevice->SetFVF(ST_PN_VERTEX::FVF);
	g_pD3DDevice->SetMaterial(&m_stMtlPlane);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetTexture(0, m_pTexture);
	
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		2,
		&m_vecPlaneVertex[0],
		sizeof(ST_PN_VERTEX)
	);
	

}
