#include "stdafx.h"
#include "Pyramid.h"


Pyramid::Pyramid()
{
}


Pyramid::~Pyramid()
{
}

void Pyramid::Setup(D3DXCOLOR c, D3DXMATRIXA16 & mat)
{
	/*   사각뿔을 그리기 위한 매질 작업   */
	{
		ZeroMemory(&m_stMtl, sizeof(D3DMATERIAL9));
		m_stMtl.Ambient = c;
		m_stMtl.Diffuse = c;
		m_stMtl.Specular = c;
	}

	m_matR = mat;

	/*   사각뿔을 그리기 위한 버텍스 작업   */
	ST_PN_VERTEX v;

	std::vector<ST_PN_VERTEX>	vecVertex;
	// : 1
	v.p = D3DXVECTOR3(0, 0, 0); vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1, -1, -1); vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1, -1, -1); vecVertex.push_back(v);
	// : 2
	v.p = D3DXVECTOR3(0, 0, 0); vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1, -1, 1); vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1, -1, -1); vecVertex.push_back(v);
	// : 3
	v.p = D3DXVECTOR3(0, 0, 0); vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1, -1, 1); vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1, -1, 1); vecVertex.push_back(v);
	// : 4
	v.p = D3DXVECTOR3(0, 0, 0); vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1, -1, -1); vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1, -1, 1); vecVertex.push_back(v);
	// : 5
	v.p = D3DXVECTOR3(-1, -1, -1); vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1, -1, -1); vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1, -1, 1); vecVertex.push_back(v);
	// : 6
	v.p = D3DXVECTOR3(1, -1, -1); vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1, -1, 1); vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1, -1, 1); vecVertex.push_back(v);

	/*   사각뿔을 그리기 위한 노말 벡터 작업   */
	for (int i = 0; i < vecVertex.size(); i += 3)
	{
		D3DXVECTOR3 V01 = vecVertex[i + 1].p -
			vecVertex[i + 0].p;

		D3DXVECTOR3 V02 = vecVertex[i + 2].p -
			vecVertex[i + 0].p;

		D3DXVECTOR3 n;
		D3DXVec3Cross(&n, &V01, &V02);
		D3DXVec3Normalize(&n, &n);

		vecVertex[i + 0].n = n;
		vecVertex[i + 1].n = n;
		vecVertex[i + 2].n = n;
	}

	/*   사각뿔을 그리기 위한 버텍스 버퍼 작업   */
	{
		m_nNumTri = vecVertex.size() / 3;
		g_pD3DDevice->CreateVertexBuffer(
			vecVertex.size() * sizeof(ST_PN_VERTEX),
			0,
			ST_PN_VERTEX::FVF,
			D3DPOOL_MANAGED,
			&m_pVB,
			NULL);

		ST_PN_VERTEX * pV = NULL;
		m_pVB->Lock(0, 0, (LPVOID*)&pV, 0);
		memcpy(pV, &vecVertex[0],
			vecVertex.size() * sizeof(ST_PN_VERTEX));
		m_pVB->Unlock();
	}
}

/*   사각뿔 그리기   */
void Pyramid::Render()
{
	D3DXMATRIXA16 matWorld, matS;
	D3DXMatrixScaling(&matS, 0.1f, 2.0f, 0.1f);
	matWorld = matS * m_matR;
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetMaterial(&m_stMtl);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetFVF(ST_PN_VERTEX::FVF);

	g_pD3DDevice->SetStreamSource(0, m_pVB,
		0, sizeof(ST_PN_VERTEX));
	g_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST,
		0,
		m_nNumTri);
}
