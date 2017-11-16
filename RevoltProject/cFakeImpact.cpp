#include "stdafx.h"
#include "cFakeImpact.h"


cFakeImpact::cFakeImpact()
	: m_currentX(0)
	, m_currentY(0)
	, m_index(0)
	, m_fTime(0)
{
}


cFakeImpact::~cFakeImpact()
{
}

void cFakeImpact::Setup()
{
	cImpact::Setup();

	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

	D3DXIMAGE_INFO stImageInfo;

	m_pTexture = g_pTextureManager->GetTexture("Objects/fakebomb/firebomb.png", &stImageInfo);

	m_stSize.nWitdh = stImageInfo.Width;
	m_stSize.nHeight = stImageInfo.Height;
}

void cFakeImpact::Update()
{
	cImpact::Update();

	if (m_isUse)
	{
		m_fTime++;
		if (m_fTime % UPDATE_TIME == 0)
		{
			m_currentX++;
			m_index++;
		}

		if (m_currentX > 4)
		{
			m_currentX = 0;
			m_currentY++;
		}
		printf("ads\n");
	}

	if (m_index == MAX_XSIZE)
	{
		m_isUse = false;
		m_fTime = 0;
		m_index = 0;
		m_currentX = 0;
		m_currentY = 0;
	}
}

void cFakeImpact::Render()
{
	D3DXMATRIXA16 matWorld;
	D3DXMATRIXA16 matView;
	D3DXMATRIXA16 matS;
	D3DXMATRIXA16 matR;
	D3DXMATRIXA16 matT;

	D3DXMatrixTranslation(&matT, m_itemPos.x, m_itemPos.y + 5.0f, m_itemPos.z);
	D3DXMatrixScaling(&matS, 0.05f, 0.05f, 0.05f);
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixRotationZ(&matR, D3DX_PI);

	matWorld = matS * matR * matT;
	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
	m_pSprite->SetWorldViewLH(NULL, &matView);

	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE | D3DXSPRITE_BILLBOARD);
	m_pSprite->SetTransform(&matWorld);

	RECT rc;
	SetRect(&rc, m_currentX * 192, m_currentY * 192, (m_currentX + 1) * 192, (m_currentY + 1) * 192);

	m_pSprite->Draw(m_pTexture, &rc, &D3DXVECTOR3(81, 0, 0), &D3DXVECTOR3(0, 0, 0), D3DCOLOR_ARGB(255, 255, 255, 255));
	m_pSprite->End();

	cImpact::Render();
}

void cFakeImpact::Destroy()
{
	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_pTexture);
}
