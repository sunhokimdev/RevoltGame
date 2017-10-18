#include "stdafx.h"
#include "UITextView.h"


UITextView::UITextView()
	: m_eFontType(FontManager::E_DEFAULT)
	, m_dwDrawTextFormat(DT_LEFT | DT_TOP)
	, m_dwTextColor(D3DCOLOR_XRGB(0, 0, 0))
{
}


UITextView::~UITextView()
{
}

void UITextView::Render(LPD3DXSPRITE pSprite)
{
	if (m_isHidden) return;

	LPD3DXFONT pFont = g_pFontManager->GetFont(m_eFontType);
	RECT rc;

	SetRect(&rc, (int)m_matWorld._41, (int)m_matWorld._42, (int)m_matWorld._41 + (int)m_stSize.nWitdh, (int)m_matWorld._42 + (int)m_stSize.nHeight);

	pFont->DrawTextA(NULL, m_sText.c_str(), m_sText.length(), &rc, m_dwDrawTextFormat, m_dwTextColor);

	UIObject::Render(pSprite);
}
