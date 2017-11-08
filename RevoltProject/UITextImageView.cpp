#include "stdafx.h"
#include "UITextImageView.h"

#include "CarBox.h"
#include "WheelTire.h"

#include "Thing.h"
#include "UserFileLoader.h"

int* UITextImageView::m_Select;
int* UITextImageView::m_LeftAndRightSelect;
std::string	UITextImageView::m_PlayerName;
bool* UITextImageView::m_isCreate;
bool* UITextImageView::m_isflag;

UITextImageView::UITextImageView()
	: m_pTexture(NULL)
	, m_xSize(1)
	, m_ySize(1)
	, m_color(D3DCOLOR_ARGB(255, 255, 255, 255))
	, m_isVectorText(false)
	, m_isVectorText2(false)
	, m_isChatingText(false)
	, m_chatText("")
	, m_cursorTime(0.0f)
	, m_isCursorRender(false)
	, m_isRealTime(false)
	, m_index(0)
{
}

UITextImageView::~UITextImageView()
{
	SAFE_RELEASE(m_pTexture);
	SAFE_DELETE(m_Select);
	SAFE_DELETE(m_LeftAndRightSelect);
	SAFE_DELETE(m_isCreate);
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

std::string UITextImageView::GetCarName()
{
	return CarBox::g_vecCar[*m_LeftAndRightSelect].name;
}

void UITextImageView::KeyEvent()
{
	int tSize = m_chatText.size();
	
	if (!(*m_isflag))
	{
		*m_isflag = true;
		m_chatText = "";
		m_chatText += m_PlayerName;
	}

	if (g_pKeyManager->isOnceKeyDown('A'))
		m_chatText += 'a';
	else if (g_pKeyManager->isOnceKeyDown('B'))
		m_chatText += 'b';
	else if (g_pKeyManager->isOnceKeyDown('C'))
		m_chatText += 'c';
	else if (g_pKeyManager->isOnceKeyDown('D'))
		m_chatText += 'd';
	else if (g_pKeyManager->isOnceKeyDown('E'))
		m_chatText += 'e';
	else if (g_pKeyManager->isOnceKeyDown('F'))
		m_chatText += 'f';
	else if (g_pKeyManager->isOnceKeyDown('G'))
		m_chatText += 'g';
	else if (g_pKeyManager->isOnceKeyDown('H'))
		m_chatText += 'h';
	else if (g_pKeyManager->isOnceKeyDown('I'))
		m_chatText += 'i';
	else if (g_pKeyManager->isOnceKeyDown('J'))
		m_chatText += 'j';
	else if (g_pKeyManager->isOnceKeyDown('K'))
		m_chatText += 'k';
	else if (g_pKeyManager->isOnceKeyDown('L'))
		m_chatText += 'l';
	else if (g_pKeyManager->isOnceKeyDown('M'))
		m_chatText += 'm';
	else if (g_pKeyManager->isOnceKeyDown('N'))
		m_chatText += 'n';
	else if (g_pKeyManager->isOnceKeyDown('O'))
		m_chatText += 'o';
	else if (g_pKeyManager->isOnceKeyDown('P'))
		m_chatText += 'p';
	else if (g_pKeyManager->isOnceKeyDown('Q'))
		m_chatText += 'q';
	else if (g_pKeyManager->isOnceKeyDown('R'))
		m_chatText += 'r';
	else if (g_pKeyManager->isOnceKeyDown('S'))
		m_chatText += 's';
	else if (g_pKeyManager->isOnceKeyDown('T'))
		m_chatText += 't';
	else if (g_pKeyManager->isOnceKeyDown('U'))
		m_chatText += 'u';
	else if (g_pKeyManager->isOnceKeyDown('V'))
		m_chatText += 'v';
	else if (g_pKeyManager->isOnceKeyDown('W'))
		m_chatText += 'w';
	else if (g_pKeyManager->isOnceKeyDown('X'))
		m_chatText += 'x';
	else if (g_pKeyManager->isOnceKeyDown('Y'))
		m_chatText += 'y';
	else if (g_pKeyManager->isOnceKeyDown('Z'))
		m_chatText += 'z';
	else if (g_pKeyManager->isOnceKeyDown('0'))
		m_chatText += '0';
	else if (g_pKeyManager->isOnceKeyDown('1'))
		m_chatText += '1';
	else if (g_pKeyManager->isOnceKeyDown('2'))
		m_chatText += '2';
	else if (g_pKeyManager->isOnceKeyDown('3'))
		m_chatText += '3';
	else if (g_pKeyManager->isOnceKeyDown('4'))
		m_chatText += '4';
	else if (g_pKeyManager->isOnceKeyDown('5'))
		m_chatText += '5';
	else if (g_pKeyManager->isOnceKeyDown('6'))
		m_chatText += '6';
	else if (g_pKeyManager->isOnceKeyDown('7'))
		m_chatText += '7';
	else if (g_pKeyManager->isOnceKeyDown('8'))
		m_chatText += '8';
	else if (g_pKeyManager->isOnceKeyDown('9'))
		m_chatText += '9';
	else if (g_pKeyManager->isOnceKeyDown(VK_OEM_PERIOD))
		m_chatText += '.';
	else if (g_pKeyManager->isOnceKeyDown(VK_BACK))
	{
		if (m_chatText.size() != 0)
		{
			m_chatText.pop_back();
			WheelTire::g_xRotAngle = (-D3DX_PI / 15.0f * 2);
			return;
		}
	}
	if (tSize != m_chatText.size())
	{
		if (m_chatText.size() == 1)
		{
			int temp = 0;

			if (m_chatText[0] >= 97)
				temp = m_chatText[0] - 97;

			WheelTire::g_xRotAngle = temp * (D3DX_PI / 15.0f);
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

			if(WheelTire::g_xRotAngle != -D3DX_PI / 15.0f * 2)
				WheelTire::g_xRotAngle += (temp1 - temp2) * (D3DX_PI / 15.0f);
			else
				WheelTire::g_xRotAngle = (temp1-1) * (D3DX_PI / 15.0f);
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

		if (*m_isCreate && (m_chatText.size() > 0))
		{
			*m_isCreate = false;
			UserFileLoader* Create = new UserFileLoader;
			Create->CreateProfile(m_chatText);
		}

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
	else if(m_isVectorText2)
		tStr = m_vecText[*m_Select];
	else if (m_isChatingText)
		tStr = m_chatText;
	else if (m_isRealTime)			// 실시간으로 그려야할 텍스트인 경우
	{
		switch (m_carIndex)
		{
			case 0:
				tStr = CarBox::g_vecCar[*m_LeftAndRightSelect].name;
			break;
			case 1:
				tStr = CarBox::g_vecCar[*m_LeftAndRightSelect].car_class;
			break;
			case 2:
				tStr = CarBox::g_vecCar[*m_LeftAndRightSelect].car_skill_level;
			break;
			case 6:
				tStr = CarBox::g_vecCar[*m_LeftAndRightSelect].trans;
			break;
		}
	}
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


		if (*m_Select == m_index)
			pSprite->Draw(m_pTexture, &rc, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0), D3DCOLOR_ARGB(255, 255, 0, 255));
		else if (*m_Select != m_index)
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

	if (m_isRealTime)
	{
		RECT rc;
		pSprite->SetTransform(&m_matWorld);

		D3DXIMAGE_INFO stImageInfo;
		std::string szTemp = std::string("Maps/Front/Image/progressbar.png");

		LPDIRECT3DTEXTURE9	tTexture = g_pTextureManager->GetTexture(szTemp, &stImageInfo);

		if (m_carIndex == 3 ||
			m_carIndex == 4 ||
			m_carIndex == 5)
		{
			float ratio;

			switch (m_carIndex)
			{
				case 3:
					ratio = CarBox::g_vecCar[*m_LeftAndRightSelect].speed;
					SetRect(&rc, 0, 0, (ratio/80.0f)*stImageInfo.Width, stImageInfo.Height - 48);
					break;
				case 4:
					ratio = CarBox::g_vecCar[*m_LeftAndRightSelect].acc;
					SetRect(&rc, 0, 0, (ratio / 15.0f)*stImageInfo.Width, stImageInfo.Height - 48);
					break;
				case 5:
					ratio = CarBox::g_vecCar[*m_LeftAndRightSelect].weight;
					SetRect(&rc, 0, 0, (ratio *stImageInfo.Width) /5.0f, stImageInfo.Height - 48);
					break;
			}

			pSprite->Draw(tTexture, &rc, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0), m_color);
		}
	}

	pSprite->End();

	UIObject::Render(pSprite);
}
