#include "stdafx.h"
#include "UITextImageView.h"
#include "Thing.h"

int* UITextImageView::m_Select;
int* UITextImageView::m_LeftAndRightSelect;

UITextImageView::UITextImageView()
	: m_pTexture(NULL)
	, m_xSize(1)
	, m_ySize(1)
	, m_color(D3DCOLOR_ARGB(255, 255, 255, 255))
	, m_isVectorText(false)
	, m_isChatingText(false)
	, m_chatText("")
	, m_cursorTime(0.0f)
	, m_isCursorRender(false)
{
}

UITextImageView::~UITextImageView()
{
	SAFE_RELEASE(m_pTexture);
	SAFE_DELETE(m_Select);
	SAFE_DELETE(m_LeftAndRightSelect);
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

void UITextImageView::KeyEvent()
{
	int tSize = m_chatText.size();

	if (g_pKeyManager->isOnceKeyDown('A'))
		m_chatText += 'a';
	if (g_pKeyManager->isOnceKeyDown('B'))
		m_chatText += 'b';
	if (g_pKeyManager->isOnceKeyDown('C'))
		m_chatText += 'c';
	if (g_pKeyManager->isOnceKeyDown('D'))
		m_chatText += 'd';
	if (g_pKeyManager->isOnceKeyDown('E'))
		m_chatText += 'e';
	if (g_pKeyManager->isOnceKeyDown('F'))
		m_chatText += 'f';
	if (g_pKeyManager->isOnceKeyDown('G'))
		m_chatText += 'g';
	if (g_pKeyManager->isOnceKeyDown('H'))
		m_chatText += 'h';
	if (g_pKeyManager->isOnceKeyDown('I'))
		m_chatText += 'i';
	if (g_pKeyManager->isOnceKeyDown('J'))
		m_chatText += 'j';
	if (g_pKeyManager->isOnceKeyDown('K'))
		m_chatText += 'k';
	if (g_pKeyManager->isOnceKeyDown('L'))
		m_chatText += 'l';
	if (g_pKeyManager->isOnceKeyDown('M'))
		m_chatText += 'm';
	if (g_pKeyManager->isOnceKeyDown('N'))
		m_chatText += 'n';
	if (g_pKeyManager->isOnceKeyDown('O'))
		m_chatText += 'o';
	if (g_pKeyManager->isOnceKeyDown('P'))
		m_chatText += 'p';
	if (g_pKeyManager->isOnceKeyDown('Q'))
		m_chatText += 'q';
	if (g_pKeyManager->isOnceKeyDown('R'))
		m_chatText += 'r';
	if (g_pKeyManager->isOnceKeyDown('S'))
		m_chatText += 's';
	if (g_pKeyManager->isOnceKeyDown('T'))
		m_chatText += 't';
	if (g_pKeyManager->isOnceKeyDown('U'))
		m_chatText += 'u';
	if (g_pKeyManager->isOnceKeyDown('V'))
		m_chatText += 'v';
	if (g_pKeyManager->isOnceKeyDown('W'))
		m_chatText += 'w';
	if (g_pKeyManager->isOnceKeyDown('X'))
		m_chatText += 'x';
	if (g_pKeyManager->isOnceKeyDown('Y'))
		m_chatText += 'y';
	if (g_pKeyManager->isOnceKeyDown('Z'))
		m_chatText += 'z';
	if (g_pKeyManager->isOnceKeyDown(VK_BACK))
	{
		if (m_chatText.size() != 0)
		{
			m_chatText.pop_back();
			Thing::g_xRotAngle = (-D3DX_PI / 15.0f * 2);
			return;
		}
	}

	if (tSize != m_chatText.size())
	{
		//g_pSoundManager->Play("honkgood.wav", 1.0f);

		if (m_chatText.size() == 1)
		{
			int temp;

			if (m_chatText[0] >= 97)
				temp = m_chatText[0] - 97;

			Thing::g_xRotAngle = temp * (D3DX_PI / 15.0f);
		}
		else
		{
			int temp1;
			int temp2;
			
			temp1 = m_chatText[m_chatText.size() - 1] - 96;

			if(m_chatText[m_chatText.size() - 2] >= 97)
				temp2 = m_chatText[m_chatText.size() - 2] - 96;
			else
				temp2 = m_chatText[m_chatText.size() - 2] - 64;

			if(Thing::g_xRotAngle != -D3DX_PI / 15.0f * 2)
				Thing::g_xRotAngle += (temp1 - temp2) * (D3DX_PI / 15.0f);
			else
				Thing::g_xRotAngle = (temp1-1) * (D3DX_PI / 15.0f);
		}
	}

	if (m_chatText.size() != 0 && m_chatText[0] >= 97)
		m_chatText[0] -= 32;
}

void UITextImageView::Update()
{
	if (m_isChatingText)
	{
		KeyEvent();

		if ((m_cursorTime / CURSORRENDER) % 2 == 1)
			m_isCursorRender = true;
		else
			m_isCursorRender = false;

		m_cursorTime++;

		if (m_cursorTime > 1000000)
			m_cursorTime = 0;
	}

	UIObject::Update();
}

void UITextImageView::Render(LPD3DXSPRITE pSprite)
{
	D3DXMATRIXA16 tMat = m_matWorld;
	int tXPos = m_matWorld._41;
	int tYPos = m_matWorld._42;
	std::string tStr = "";

	int tTempValue = (m_stSize.nWitdh / m_textPos.x);

	if (m_isHidden) return;
	if (pSprite == NULL) return;

	pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

	tMat._11 = m_xSize;
	tMat._22 = m_ySize;
	tMat._33 = 1.0f;

	if (m_isVectorText)
		tStr = m_vecText[*m_LeftAndRightSelect];
	else if (m_isChatingText)
		tStr = m_chatText;
	else
		tStr = m_sText;

	for (int i = 0;i < tStr.size();i++)
	{
		RECT rc;
		char tChar = tStr[i];
		int tPos;

		if (m_fontFileType == FONT1)
		{
			if(tChar >= 97)
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

	if (m_isChatingText && m_isCursorRender)
	{
		RECT rc;

		tMat._42 = tMat._42 + m_textPos.y * tMat._22;

		pSprite->SetTransform(&tMat);

		D3DXIMAGE_INFO stImageInfo;
		std::string szTemp = std::string("Maps/Front/Image/charcursor.png");

		LPDIRECT3DTEXTURE9	tTexture = g_pTextureManager->GetTexture(szTemp, &stImageInfo);
		SetRect(&rc, 0, 0, stImageInfo.Width, stImageInfo.Height);
		pSprite->Draw(tTexture, &rc, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0), m_color);
	}

	pSprite->End();

	UIObject::Render(pSprite);
}
