#include "stdafx.h"
#include "Grid.h"
#include "Pyramid.h"

Grid::Grid()
	: m_pVB(NULL)
	, m_nNumLine(0)
{
}


Grid::~Grid()
{
	SAFE_RELEASE(m_pVB);

	for each(auto p in m_vecPyramid)
		SAFE_DELETE(p);
	m_vecPyramid.clear();
}

void Grid::Setup(int nNumHalfTile, float fInterval)
{
	float fMax = nNumHalfTile * fInterval;
	float fMin = -nNumHalfTile * fInterval;

	ST_PC_VERTEX v;

	std::vector<ST_PC_VERTEX>	vecVertex;


	for (int i = 1; i <= nNumHalfTile; ++i)
	{
		if (i % 5 == 0)
			v.c = D3DCOLOR_XRGB(255, 255, 255);
		else
			v.c = D3DCOLOR_XRGB(128, 128, 128);

		v.p = D3DXVECTOR3(fMin, 0, i*fInterval); vecVertex.push_back(v);
		v.p = D3DXVECTOR3(fMax, 0, i*fInterval); vecVertex.push_back(v);

		v.p = D3DXVECTOR3(fMin, 0, -i*fInterval); vecVertex.push_back(v);
		v.p = D3DXVECTOR3(fMax, 0, -i*fInterval); vecVertex.push_back(v);

		v.p = D3DXVECTOR3(i*fInterval, 0, fMin); vecVertex.push_back(v);
		v.p = D3DXVECTOR3(i*fInterval, 0, fMax); vecVertex.push_back(v);

		v.p = D3DXVECTOR3(-i*fInterval, 0, fMin); vecVertex.push_back(v);
		v.p = D3DXVECTOR3(-i*fInterval, 0, fMax); vecVertex.push_back(v);
	}

	v.c = D3DCOLOR_XRGB(255, 0, 0);
	v.p = D3DXVECTOR3(fMin, 0, 0); vecVertex.push_back(v);
	v.p = D3DXVECTOR3(fMax, 0, 0); vecVertex.push_back(v);

	v.c = D3DCOLOR_XRGB(0, 255, 0);
	v.p = D3DXVECTOR3(0, fMin, 0); vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0, fMax, 0); vecVertex.push_back(v);

	v.c = D3DCOLOR_XRGB(0, 0, 255);
	v.p = D3DXVECTOR3(0, 0, fMin); vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0, 0, fMax); vecVertex.push_back(v);

	{
		m_nNumLine = vecVertex.size() / 2;
		g_pD3DDevice->CreateVertexBuffer(
			vecVertex.size() * sizeof(ST_PC_VERTEX),
			0,
			ST_PC_VERTEX::FVF,
			D3DPOOL_MANAGED,
			&m_pVB,
			NULL);
		ST_PC_VERTEX *pV = NULL;
		m_pVB->Lock(0, 0, (LPVOID*)&pV, 0);
		memcpy(pV, &vecVertex[0],
			vecVertex.size() * sizeof(ST_PC_VERTEX));
		m_pVB->Unlock();

	} 

	Pyramid * pPyramid = NULL;
	D3DXMATRIXA16 matR;

	pPyramid = new Pyramid;
	D3DXMatrixRotationZ(&matR, D3DX_PI / 2.0f);
	pPyramid->Setup(D3DCOLOR_XRGB(255, 0, 0), matR);
	m_vecPyramid.push_back(pPyramid);

	pPyramid = new Pyramid;
	D3DXMatrixRotationZ(&matR, D3DX_PI);
	pPyramid->Setup(D3DCOLOR_XRGB(0, 255, 0), matR);
	m_vecPyramid.push_back(pPyramid);

	pPyramid = new Pyramid;
	D3DXMatrixRotationX(&matR, -D3DX_PI / 2.0f);
	pPyramid->Setup(D3DCOLOR_XRGB(0, 0, 255), matR);
	m_vecPyramid.push_back(pPyramid);
}

void Grid::Render()
{
	g_pD3DDevice->SetTexture(0, NULL);
	D3DXMATRIXA16 matl;
	D3DXMatrixIdentity(&matl);

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matl);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);

	{
		g_pD3DDevice->SetStreamSource(0, m_pVB,
			0, sizeof(ST_PC_VERTEX));
		g_pD3DDevice->DrawPrimitive(D3DPT_LINELIST,
			0, m_nNumLine);
	}

	for each(auto p  in m_vecPyramid)
		p->Render();
}
