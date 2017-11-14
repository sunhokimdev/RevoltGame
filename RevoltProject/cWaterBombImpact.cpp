#include "stdafx.h"
#include "cWaterBombImpact.h"


cWaterBombImpact::cWaterBombImpact()
	: m_fTime(0)
	, m_index(0)
	, m_currentX(0)
	, m_currentY(0)
{
	cImpact::cImpact();
}


cWaterBombImpact::~cWaterBombImpact()
{
}

void cWaterBombImpact::Setup()
{
	cImpact::Setup();
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);
	
	D3DXIMAGE_INFO stImageInfo;

	m_pTexture = g_pTextureManager->GetTexture("Objects/wbomb/bombsprite.png", &stImageInfo);

	m_stSize.nWitdh = stImageInfo.Width;
	m_stSize.nHeight = stImageInfo.Height;
}

void cWaterBombImpact::Update()
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

		if (m_currentX > 8)
		{
			m_currentX = 0;
			m_currentY++;
		}
	}

	if (m_index == MAX_XSIZE)
	{
		m_isUse = false;
		m_fTime = 0;
		m_index = 0;
		m_currentX = 0;
		m_currentY = 0;

		printf("asdf\n");
	}
}

void cWaterBombImpact::Render()
{
	D3DXMATRIXA16 matWorld;
	D3DXMATRIXA16 matView;
	D3DXMATRIXA16 matS;
	D3DXMATRIXA16 matR;
	D3DXMATRIXA16 matT;

	D3DXMatrixTranslation(&matT, m_itemPos.x, m_itemPos.y + 3.0f, m_itemPos.z);
	D3DXMatrixScaling(&matS, 0.05f, 0.05f, 0.05f);
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixRotationZ(&matR, D3DX_PI);

	matWorld = matS * matR * matT;
	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
	m_pSprite->SetWorldViewLH(NULL, &matView);

	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE | D3DXSPRITE_BILLBOARD);
	m_pSprite->SetTransform(&matWorld);

	RECT rc;
	SetRect(&rc, m_currentX * 100, m_currentY * 100, (m_currentX +1) * 100, (m_currentY+1)*100);

	m_pSprite->Draw(m_pTexture, &rc, &D3DXVECTOR3(50,0,0), &D3DXVECTOR3(0, 0, 0), D3DCOLOR_ARGB(255, 255, 255, 255));
	m_pSprite->End();

	cImpact::Render();
}

void cWaterBombImpact::Destroy()
{
	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_pTexture);
}
