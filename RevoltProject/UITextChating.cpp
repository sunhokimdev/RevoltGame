#include "stdafx.h"
#include "UITextChating.h"


UITextChating::UITextChating()
{
}


UITextChating::~UITextChating()
{
}

void UITextChating::Update()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	RECT rc;
	SetRect(&rc, (int)m_matWorld._41, (int)m_matWorld._42, (int)m_matWorld._41 + (int)m_stSize.nWitdh, (int)m_matWorld._42 + (int)m_stSize.nHeight);

	if (PtInRect(&rc, pt))
	{
		SetCursor(LoadCursor(NULL, IDC_IBEAM));
		if (GetKeyState(VK_LBUTTON) & 8000)
		{
			m_isLButtonDown = true;
		}
	}
	else
	{
		if (GetKeyState(VK_LBUTTON) & 8000)
		{
			m_isLButtonDown = false;
		}
	}

	if (m_isLButtonDown)
	{
		if (GetKeyState('A') & 8000)
		{
			m_sText += "a";
		}
	}

	UIObject::Update();
}

void UITextChating::Render(LPD3DXSPRITE pSprite)
{
	if (m_isHidden) return;

	if (pSprite == nullptr) return;

	pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	pSprite->SetTransform(&m_matWorld);

	RECT rc;
	SetRect(&rc, 0, 0, m_stSize.nWitdh, m_stSize.nHeight);

	pSprite->Draw(m_aTexture, &rc, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0), D3DCOLOR_ARGB(255, 255, 255, 255));

	pSprite->End();

	LPD3DXFONT pFont = g_pFontManager->GetFont(m_eFontType);

	SetRect(&rc, (int)m_matWorld._41, (int)m_matWorld._42, (int)m_matWorld._41 + (int)m_stSize.nWitdh, (int)m_matWorld._42 + (int)m_stSize.nHeight);

	pFont->DrawTextA(NULL, m_sText.c_str(), m_sText.length(), &rc, m_dwDrawTextFormat, m_dwTextColor);

	UIObject::Render(pSprite);
}

void UITextChating::SetTexture(char * szFile)
{
	D3DXIMAGE_INFO stImageInfo;
	m_aTexture = g_pTextureManager->GetTexture(szFile, &stImageInfo);

	m_stSize.nWitdh = stImageInfo.Width;
	m_stSize.nHeight = stImageInfo.Height;
}

