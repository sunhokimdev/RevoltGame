#include "stdafx.h"
#include "UITextImageView.h"

int* UITextImageView::m_Select;

UITextImageView::UITextImageView()
	:m_pTexture(NULL)
	, m_xSize(1)
	, m_ySize(1)
	, m_color(D3DCOLOR_ARGB(255,255,255,255))
{
}

UITextImageView::~UITextImageView()
{
	SAFE_RELEASE(m_pTexture);
}


void UITextImageView::SetTexture(char * szFullPath)
{
	D3DXIMAGE_INFO stImageInfo;
	std::string szTemp = std::string(szFullPath);

	m_pTexture = g_pTextureManager->GetTexture(szFullPath, &stImageInfo);

	m_stSize.nWitdh = stImageInfo.Width;
	m_stSize.nHeight = stImageInfo.Height;

	if (szTemp.find("font1") != -1)
	{
		m_fontFileType = FONT1;

		m_textPos.x = 16;
		m_textPos.y = 16;
	}
	else if (szTemp.find("font2") != -1)
	{
		m_fontFileType = FONT2;

		m_textPos.x = 8;
		m_textPos.y = 16;
	}
}

void UITextImageView::Render(LPD3DXSPRITE pSprite)
{
	D3DXMATRIXA16 tMat = m_matWorld;
	int tXPos = m_matWorld._41;
	int tYPos = m_matWorld._42;

	int tTempValue = (m_stSize.nWitdh / m_textPos.x);

	if (m_isHidden) return;
	if (pSprite == NULL) return;

	pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

	tMat._11 = m_xSize;
	tMat._22 = m_ySize;
	tMat._33 = 1.0f;

	for (int i = 0;i < m_sText.size();i++)
	{
		RECT rc;
		char tChar = m_sText[i];
		int tPos;

		if (m_fontFileType == FONT1)
		{
			if(m_sText[i] >= 97)
				tChar -= 32;

			tPos = tChar - 65;
		}
		else if (m_fontFileType == FONT2)
		{
			tPos = tChar - 33;
		}

		SetRect(&rc,
			(tPos % tTempValue) * m_textPos.x,
			(tPos/ tTempValue) * m_textPos.y,
			((tPos % tTempValue) * m_textPos.x) + m_textPos.x,
			((tPos / tTempValue) * m_textPos.y) + m_textPos.y);

		pSprite->SetTransform(&tMat);

		tMat._41 = tMat._41 + m_textPos.x * tMat._11;

		if(*m_Select == m_index)
			pSprite->Draw(m_pTexture, &rc, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0), D3DCOLOR_ARGB(255, 255, 0, 255));
		else
			pSprite->Draw(m_pTexture, &rc, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0), m_color);
	}

	pSprite->End();

	UIObject::Render(pSprite);
}
