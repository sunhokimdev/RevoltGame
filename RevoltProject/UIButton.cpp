#include "stdafx.h"
#include "UIButton.h"
#include "UITextView.h"

UIButton::UIButton()
	: m_eButtonState(E_NORMAL)
	, m_pDelegate(NULL)
{
}


UIButton::~UIButton()
{
}

void UIButton::SetTexture(char * szNor, char * szOvr, char * szSel)
{
	D3DXIMAGE_INFO stImageInfo;
	m_aTexture[E_NORMAL] = g_pTextureManager->GetTexture(szNor, &stImageInfo);

	m_stSize.nWitdh = stImageInfo.Width;
	m_stSize.nHeight = stImageInfo.Height;

	m_aTexture[E_MOUSEOVER] = g_pTextureManager->GetTexture(szOvr, &stImageInfo);
	m_aTexture[E_SELECTED] = g_pTextureManager->GetTexture(szSel, &stImageInfo);
}

void UIButton::Update()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	RECT rc;
	SetRect(&rc, (int)m_matWorld._41, (int)m_matWorld._42, (int)m_matWorld._41 + (int)m_stSize.nWitdh, (int)m_matWorld._42 + (int)m_stSize.nHeight);

	if (PtInRect(&rc, pt))
	{
		if (GetKeyState(VK_LBUTTON) & 0x8000)
		{
			if (m_eButtonState == E_MOUSEOVER)
			{
				m_eButtonState = E_SELECTED;
			}
		}
		else
		{
			if (m_eButtonState == E_SELECTED)
			{
				if (m_pDelegate)
					m_pDelegate->OnClick(this);
			}
			m_eButtonState = E_MOUSEOVER;
		}
	}
	else
	{
		m_eButtonState = E_NORMAL;
	}

	UIObject::Update();
}

void UIButton::Render(LPD3DXSPRITE pSprite)
{
	if (m_isHidden) return;

	if (pSprite == nullptr) return;

	pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	pSprite->SetTransform(&m_matWorld);

	RECT rc;
	SetRect(&rc, 0, 0, m_stSize.nWitdh, m_stSize.nHeight);

	pSprite->Draw(m_aTexture[m_eButtonState], &rc, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0), D3DCOLOR_ARGB(255, 255, 255, 255));

	pSprite->End();
	UIObject::Render(pSprite);
}


void UIButton::SetTexture(char * szNor, char * szOvr, char * szSel, std::string str)
{
	SetTexture(szNor, szOvr, szSel);
	SetText(str);
}

void UIButton::SetText(std::string str)
{
	UITextView* pTextView = new UITextView;
	pTextView->SetText(str);
	pTextView->SetSize(ST_SIZE(m_stSize.nWitdh, m_stSize.nHeight));
	pTextView->SetPosition((int)m_matWorld._41, (int)m_matWorld._42);
	pTextView->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	pTextView->SetTextColor(D3DCOLOR_XRGB(255, 255, 0));

	this->AddChild(pTextView);
}
