#include "stdafx.h"
#include "cBillBoardEffect.h"


cBillBoardEffect::cBillBoardEffect()
	: m_pTexture(NULL)
	, m_pMesh(NULL)
{
}


cBillBoardEffect::~cBillBoardEffect()
{
	SAFE_DELETE(m_pTexture);
	SAFE_DELETE(m_pMesh);
}

void cBillBoardEffect::Setup()
{
}

void cBillBoardEffect::Update()
{
}

void cBillBoardEffect::Render()
{
}

void cBillBoardEffect::SetFileTexture(char * szFile)
{
	m_pTexture = g_pTextureManager->GetTexture(szFile);

	ST_PNT_VERTEX* vertices;
	m_pMesh->LockVertexBuffer(0, (LPVOID*)&vertices);

	vertices[0].p = D3DXVECTOR3(-0.3831, 0.3831, 0.0f);
	vertices[0].t = D3DXVECTOR2(0.0f, 0.0f);

	vertices[1].p = D3DXVECTOR3(0.8000, 0.3831, 0.0f);
	vertices[1].t = D3DXVECTOR2(1.0f, 0.0f);

	vertices[2].p = D3DXVECTOR3(-0.3831, -0.6831, 0.0f);
	vertices[2].t = D3DXVECTOR2(0.0f, 1.0f);

	vertices[3].p = D3DXVECTOR3(-0.3831, -0.6831, 0.0f);
	vertices[3].t = D3DXVECTOR2(0.0f, 1.0f);

	vertices[4].p = D3DXVECTOR3(0.8000, 0.3831, 0.0f);
	vertices[4].t = D3DXVECTOR2(1.0f, 0.0f);

	vertices[5].p = D3DXVECTOR3(0.8000, -0.6831, 0.0f);
	vertices[5].t = D3DXVECTOR2(1.0f, 1.0f);
	m_pMesh->UnlockVertexBuffer();

	WORD * pI = NULL;
	m_pMesh->LockIndexBuffer(0, (LPVOID*)& pI);
	for (int i = 0; i < 6; i++)
	{
		pI[i] = i;
	}
	m_pMesh->UnlockIndexBuffer();

	DWORD* pA = NULL;
	m_pMesh->LockAttributeBuffer(0, &pA);
	m_pMesh->UnlockAttributeBuffer();
}
