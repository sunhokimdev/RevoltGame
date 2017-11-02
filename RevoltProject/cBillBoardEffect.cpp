#include "stdafx.h"
#include "cBillBoardEffect.h"
#include "UIImageView.h"

cBillBoardEffect::cBillBoardEffect()
	: m_pTexture(NULL)
	, m_MaxFrameX(1)
	, m_MaxFrameY(1)
	, m_CurrentFrameX(0)
	, m_CurrentFrameY(0)
	, m_FrameTime(10)
	, m_isFrameRender(false)
	, m_isActive(false)
	, m_effectType(WATER)
{
}


cBillBoardEffect::~cBillBoardEffect()
{
	SAFE_DELETE(m_pTexture);
}

void cBillBoardEffect::SetTexture(char * szFullPath)
{
	D3DXIMAGE_INFO stImageInfo;

	m_pTexture = g_pTextureManager->GetTexture(szFullPath, &stImageInfo);

	m_stSize.nWitdh = stImageInfo.Width;
	m_stSize.nHeight = stImageInfo.Height;
}

void cBillBoardEffect::SetFrameTexture(char * szFullPath, int MaxFrameX, int MaxFrameY)
{
	D3DXIMAGE_INFO stImageInfo;

	m_pTexture = g_pTextureManager->GetTexture(szFullPath, &stImageInfo);

	m_MaxFrameX = MaxFrameX;
	m_MaxFrameY = MaxFrameY;

	stImageInfo.Width = stImageInfo.Width / MaxFrameX;
	stImageInfo.Height = stImageInfo.Height / MaxFrameY;

	m_stSize.nWitdh = stImageInfo.Width;
	m_stSize.nHeight = stImageInfo.Height;
}

void cBillBoardEffect::SetEffectType(int TypeNum)
{
	if (TypeNum == 1)
		m_effectType = WATER;
}

void cBillBoardEffect::FrameUpdate()
{
	if (m_isFrameRender)
	{
		if (m_isActive)
		{
			if (m_CurrentFrameX < m_MaxFrameX)
			{
				m_FrameTime -= 5;

				if (m_FrameTime <= 0)
				{
					m_CurrentFrameX += 1;
					m_FrameTime = 10;
				}
			}

			if (m_CurrentFrameX >= m_MaxFrameX)
			{
				m_isActive = false;
			}
		}
		else
			m_CurrentFrameX = 0;
	}
}

void cBillBoardEffect::BillboardRender(LPD3DXSPRITE Sprite,
	float posX, float posY, float posZ,
	float sizeX, float sizeY, float sizeZ)
{
	if (Sprite == NULL) return;

	D3DXMATRIXA16 matWorld;
	D3DXMATRIXA16 matView;
	D3DXMATRIXA16 matS;
	D3DXMATRIXA16 matR;
	D3DXMATRIXA16 matT;

	if (m_effectType == WATER)	D3DXMatrixTranslation(&matT, posX, posY + 3, posZ);
	else D3DXMatrixTranslation(&matT, posX, posY, posZ);

	D3DXMatrixScaling(&matS, sizeX, sizeY, sizeZ);
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixRotationZ(&matR, D3DX_PI);

	matWorld = matS * matR * matT;
	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
	Sprite->SetWorldViewLH(NULL, &matView);

	Sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE | D3DXSPRITE_BILLBOARD);
	Sprite->SetTransform(&matWorld);

	RECT rc;
	if (m_isFrameRender)
	{
		SetRect(&rc
			, m_stSize.nWitdh * m_CurrentFrameX
			, m_stSize.nHeight * m_CurrentFrameY
			, m_stSize.nWitdh * m_CurrentFrameX + 32
			, m_stSize.nWitdh * m_CurrentFrameY + 32);
	}
	else SetRect(&rc, 0, 0, m_stSize.nWitdh, m_stSize.nWitdh);

	Sprite->Draw(m_pTexture, &rc, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0), 0xFFFFFFFF);
	Sprite->End();
}
//
//void Effect::BillboardFrameRender(LPD3DXSPRITE Sprite,
//	float posX, float posY, float posZ,
//	float sizeX, float sizeY, float sizeZ)
//{
//	if (Sprite == NULL) return;
//
//	D3DXMATRIXA16 matWorld;
//	D3DXMATRIXA16 matView;
//	D3DXMATRIXA16 matS;
//	D3DXMATRIXA16 matR;
//	D3DXMATRIXA16 matT;
//
//	if (m_effectType == WATER)	D3DXMatrixTranslation(&matT, posX, posY + 5, posZ);
//	else D3DXMatrixTranslation(&matT, posX, posY, posZ);
//
//	D3DXMatrixScaling(&matS, sizeX, sizeY, sizeZ);
//	D3DXMatrixRotationZ(&matR, D3DX_PI);
//	D3DXMatrixIdentity(&matWorld);
//
//	matWorld = matS * matR * matT;
//
//	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
//	Sprite->SetWorldViewLH(NULL, &matView);
//
//	Sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE | D3DXSPRITE_BILLBOARD);
//	
//	Sprite->SetTransform(&matWorld);
//
//	RECT rc;
//	SetRect(&rc
//		, m_stSize.nWitdh * m_CurrentFrameX
//		, m_stSize.nHeight * m_CurrentFrameY
//		, m_stSize.nWitdh * m_CurrentFrameX + 32
//		, m_stSize.nWitdh * m_CurrentFrameY + 32);
//	Sprite->Draw(m_pTexture, &rc, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0), 0xFFFFFFFF);
//	Sprite->End();
//}

void cBillBoardEffect::Destroy()
{
	if (m_pTexture) SAFE_RELEASE(m_pTexture); m_pTexture = NULL;
}

