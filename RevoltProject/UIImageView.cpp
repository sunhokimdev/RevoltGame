#include "stdafx.h"
#include "UIImageView.h"

UIImageView::UIImageView()
	: m_pTexture(NULL)
	, m_isBoard(false)
{
}

UIImageView::~UIImageView()
{
}

void UIImageView::SetTexture(char * szFullPath)
{
	D3DXIMAGE_INFO stImageInfo;

	m_pTexture = g_pTextureManager->GetTexture(szFullPath, &stImageInfo);

	m_stSize.nWitdh = stImageInfo.Width;
	m_stSize.nHeight = stImageInfo.Height;
}

void UIImageView::Render(LPD3DXSPRITE pSprite)
{
	D3DXMATRIXA16 tMat = m_matWorld;

	int tXPos;
	int tYPos;

	if (m_isHidden) return;
	if (pSprite == NULL) return;

	pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	if (m_isBoard)
	{
		RECT rc;

		pSprite->SetTransform(&tMat);
		SetRect(&rc, 0, 0, 21, 23);
		pSprite->Draw(m_pTexture, &rc, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0), D3DCOLOR_ARGB(220, 255, 255, 255));

		tMat = m_matWorld;
		tMat._11 = m_xSize;
		tMat._22 = 1.0f;
		tMat._41 = tMat._41 + 21;
		tXPos = tMat._41 + (15 * tMat._11);
		pSprite->SetTransform(&tMat);
		SetRect(&rc, 22, 0, 37, 24);
		pSprite->Draw(m_pTexture, &rc, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0), D3DCOLOR_ARGB(220, 255, 255, 255));

		tMat = m_matWorld;
		tMat._41 = tXPos;
		pSprite->SetTransform(&tMat);
		SetRect(&rc, 38, 0, 64, 24);
		pSprite->Draw(m_pTexture, &rc, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0), D3DCOLOR_ARGB(220, 255, 255, 255));

		tMat = m_matWorld;
		tMat._11 = 1.0f;
		tMat._22 = m_ySize;
		tMat._42 = tMat._42 + 23;
		tYPos = tMat._42 + ((15 * tMat._22));
		pSprite->SetTransform(&tMat);
		SetRect(&rc, 0, 24, 21, 39);
		pSprite->Draw(m_pTexture, &rc, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0), D3DCOLOR_ARGB(220, 255, 255, 255));

		tMat = m_matWorld;
		tMat._11 = m_xSize;
		tMat._22 = m_ySize;
		tMat._41 = tMat._41 + 21;
		tMat._42 = tMat._42 + 23;
		pSprite->SetTransform(&tMat);
		SetRect(&rc, 22, 24, 37, 39);
		pSprite->Draw(m_pTexture, &rc, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0), D3DCOLOR_ARGB(220, 255, 255, 255));

		tMat = m_matWorld;
		tMat._11 = 1.0f;
		tMat._22 = m_ySize;
		tMat._41 = tXPos;
		tMat._42 = tMat._42 + 23;
		pSprite->SetTransform(&tMat);
		SetRect(&rc, 38, 24, 64, 39);
		pSprite->Draw(m_pTexture, &rc, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0), D3DCOLOR_ARGB(220, 255, 255, 255));

		tMat = m_matWorld;
		tMat._42 = tYPos;
		pSprite->SetTransform(&tMat);
		SetRect(&rc, 0, 40, 21, 64);
		pSprite->Draw(m_pTexture, &rc, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0), D3DCOLOR_ARGB(220, 255, 255, 255));

		tMat = m_matWorld;
		tMat._11 = m_xSize;
		tMat._41 = tMat._41 + 21;
		tMat._42 = tYPos;
		pSprite->SetTransform(&tMat);
		SetRect(&rc, 22, 40, 37, 64);
		pSprite->Draw(m_pTexture, &rc, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0), D3DCOLOR_ARGB(220, 255, 255, 255));

		tMat = m_matWorld;
		tMat._11 = 1.0f;
		tMat._22 = 1.0f;
		tMat._41 = tXPos;
		tMat._42 = tYPos;
		pSprite->SetTransform(&tMat);
		SetRect(&rc, 38, 40, 64, 64);
		pSprite->Draw(m_pTexture, &rc, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0), D3DCOLOR_ARGB(220, 255, 255, 255));

		/*
		m_matWorld._11 = 1.0f;
		m_matWorld._22 = 1.0f;
		*/
	}

	else
	{
		RECT rc;
		pSprite->SetTransform(&tMat);
		SetRect(&rc, 0, 0, m_stSize.nWitdh, m_stSize.nWitdh);
		pSprite->Draw(m_pTexture, &rc, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0), D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	pSprite->End();

	UIObject::Render(pSprite);
}