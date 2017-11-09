#include "stdafx.h"
#include "UIImageView.h"
#include "cCar.h"

#define INCREASE_NOISE_X	20.0f
#define LEFT_NOISE_X		-500.0f
#define RIGHT_NOISE_X		-512.0f
#define LIMIT_NOISE_X		-256.0f


UIImageView::UIImageView()
	: m_pTexture(NULL)
	, m_isBoard(false)
	, m_xSize(1.0f)
	, m_ySize(1.0f)
	, m_color(D3DXCOLOR(255, 255, 255, 255))
	, m_isMove(false)
	, m_isNoise(false)
	, m_isItem(false)
	, m_isSpeed(false)
	, m_isSpeedFrame(false)
	, m_isArrowDir(false)
	, LeftNoiseX(LEFT_NOISE_X)
	, RightNoiseX(RIGHT_NOISE_X)
	, UpNoiseY(-256.0f)
	, DownNoiseY(-512.0f)
	, m_itemID(0)
	, m_itemPrevID(8)
	, m_alpha(0)
	, m_updateTIme(500)
	, m_alphaValue(0)
	, m_fArrowAngle(0.0f)

{
	for (int i = 0; i < sizeof(m_speedAlpha) / sizeof(m_speedAlpha[0]); i++)
	{
		m_speedAlpha[i] = 0;
	}
}

UIImageView::~UIImageView()
{
	SAFE_RELEASE(m_pTexture);
}

void UIImageView::SetTexture(char * szFullPath)
{
	D3DXIMAGE_INFO stImageInfo;

	m_pTexture = g_pTextureManager->GetTexture(szFullPath, &stImageInfo);

	m_stSize.nWitdh = stImageInfo.Width;
	m_stSize.nHeight = stImageInfo.Height;

}

void UIImageView::Update()
{
	if (m_isNoise)
	{
		if (m_isMove)
		{
			if (LeftNoiseX < LIMIT_NOISE_X)   LeftNoiseX += INCREASE_NOISE_X;
			else
			{
				m_isMove = false;
				LeftNoiseX = LEFT_NOISE_X;
				RightNoiseX = RIGHT_NOISE_X;
			}
		}
	}

	/*   현재 이미지가 아이템 리스트 라면   */
	else if (m_isItem)
	{
		/*   update타입이 100이하면 선택된 m_item이 된다   */
		if (m_updateTIme < 100)
		{
			m_alpha = 255;
		}
		else
		{
			srand(time(NULL));
			if (m_itemID > MAX_ID)
			{
				m_itemID = 3;
				//m_itemID = m_pCar->GetHoldItem();
			}
				
			if (m_itemPrevID > MAX_ID)
				m_itemPrevID = rand() % 12;

			if (m_fTime % m_updateTIme != 0)
			{
				m_alpha += 20;
			}

			if (m_alpha >= 255)
			{
				m_alpha = 0;
				m_itemID++;
				m_itemPrevID++;
			}

			m_updateTIme -= 2;
		}
	}
	else if (m_isSpeed)
	{
		m_Rpm = m_Rpm * 7;

		for (int i = 0; i < sizeof(m_speedAlpha) / sizeof(m_speedAlpha[0]); i++)
		{
			m_speedAlpha[i] = m_Rpm / ((i * i) + 1) ;
		
			if (m_speedAlpha[i] >= 255)
			{
				m_speedAlpha[i] = 255;
			}
		}
	}


	UIObject::Update();
}

void UIImageView::Render(LPD3DXSPRITE pSprite)
{
	D3DXMATRIXA16 tMat = m_matWorld;

	int tXPos;
	int tYPos;

	if (m_isHidden) return;
	if (pSprite == NULL) return;

	pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	/*   그릴려고 하는 이미지가 파랑 테두리의 판일 경우   */
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

	} // << if(m_isBoard) end
	else if (m_isNoise && m_isMove)
	{
		RECT rc;

		tMat._11 = m_xSize;
		tMat._22 = m_ySize;

		pSprite->SetTransform(&tMat);
		SetRect(&rc, RightNoiseX, 0, LeftNoiseX, m_stSize.nHeight);
		pSprite->Draw(m_pTexture, &rc, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0), m_color);
	}

	else if (m_isItem)
	{
		RECT rc;

		pSprite->SetTransform(&tMat);

		SetRect(&rc, (m_itemID % 4) * 32, (m_itemID / 4) * 32, ((m_itemID % 4) + 1) * 32, ((m_itemID / 4) + 1) * 32);
		pSprite->Draw(m_pTexture, &rc, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0), D3DCOLOR_ARGB(m_alpha, 255, 255, 255));

		SetRect(&rc, (m_itemPrevID % 4) * 32, (m_itemPrevID / 4) * 32, ((m_itemPrevID % 4) + 1) * 32, ((m_itemPrevID / 4) + 1) * 32);
		pSprite->Draw(m_pTexture, &rc, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0), D3DCOLOR_ARGB(255 - m_alpha, 255, 255, 255));
	}

	else if (m_isSpeedFrame || m_isSpeed)
	{
		RECT rc;

		m_xSize = 1.5f;
		m_ySize = 1.5f;

		if (m_isSpeedFrame)
		{
			for (int i = 0; i < sizeof(m_speedAlpha) / sizeof(m_speedAlpha[0]); i++)
			{
				m_speedAlpha[i] = 230;
			}
		}

		tMat = m_matWorld;
		tMat._11 = m_xSize;
		tMat._22 = m_ySize;

		pSprite->SetTransform(&tMat);
		SetRect(&rc, 0, 0, 22, 22);
		pSprite->Draw(m_pTexture, &rc, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0), D3DCOLOR_ARGB(m_speedAlpha[0], 255, 255, 255));

		tMat = m_matWorld;
		tMat._11 = m_xSize;
		tMat._22 = m_ySize;
		tMat._41 = tMat._41 + 20;
		tMat._42 = tMat._42 - 20;
		pSprite->SetTransform(&tMat);
		SetRect(&rc, 22, 0, 44, 22);
		pSprite->Draw(m_pTexture, &rc, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0), D3DCOLOR_ARGB(m_speedAlpha[1], 255, 255, 255));

		tMat = m_matWorld;
		tMat._11 = m_xSize;
		tMat._22 = m_ySize;
		tMat._41 = tMat._41 + 44;
		tMat._42 = tMat._42 - 37;
		pSprite->SetTransform(&tMat);
		SetRect(&rc, 44, 0, 66, 22);
		pSprite->Draw(m_pTexture, &rc, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0), D3DCOLOR_ARGB(m_speedAlpha[2], 255, 255, 255));

		tMat = m_matWorld;
		tMat._11 = m_xSize;
		tMat._22 = m_ySize;
		tMat._41 = tMat._41 + 70;
		tMat._42 = tMat._42 - 47;
		pSprite->SetTransform(&tMat);
		SetRect(&rc, 66, 0, 88, 22);
		pSprite->Draw(m_pTexture, &rc, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0), D3DCOLOR_ARGB(m_speedAlpha[3], 255, 255, 255));

		tMat = m_matWorld;
		tMat._11 = m_xSize;
		tMat._22 = m_ySize;
		tMat._41 = tMat._41 + 100;
		tMat._42 = tMat._42 - 54;
		pSprite->SetTransform(&tMat);
		SetRect(&rc, 88, 0, 110, 22);
		pSprite->Draw(m_pTexture, &rc, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0), D3DCOLOR_ARGB(m_speedAlpha[4], 255, 255, 255));

		tMat = m_matWorld;
		tMat._11 = m_xSize;
		tMat._22 = m_ySize;
		tMat._41 = tMat._41 + 131;
		tMat._42 = tMat._42 - 59;
		pSprite->SetTransform(&tMat);
		SetRect(&rc, 110, 0, 132, 22);
		pSprite->Draw(m_pTexture, &rc, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0), D3DCOLOR_ARGB(m_speedAlpha[5], 255, 255, 255));

		tMat = m_matWorld;
		tMat._11 = m_xSize;
		tMat._22 = m_ySize;
		tMat._41 = tMat._41 + 168;
		tMat._42 = tMat._42 - 61;
		pSprite->SetTransform(&tMat);
		SetRect(&rc, 132, 0, 154, 22);
		pSprite->Draw(m_pTexture, &rc, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0), D3DCOLOR_ARGB(m_speedAlpha[6], 255, 255, 255));

	}	// << if (m_isSpeedFrame || m_isSpeed) end
	else if (m_isArrowDir)
	{
		RECT rc;
		
		D3DXMATRIXA16 matWorld, matR, matT1, matT2;
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixIdentity(&matR);
		D3DXMatrixIdentity(&matT1);
		D3DXMatrixIdentity(&matT2);
	
		// 이미지가 제자리에서 회전하기위해 위치 보정(D3DXMatrixTranslation 2번)
		D3DXMatrixTranslation(&matT1, -m_stSize.nWitdh / 2, -m_stSize.nHeight / 2, 0.0f);
		D3DXMatrixRotationZ(&matR, m_fArrowAngle);
		D3DXMatrixTranslation(&matT2, m_stSize.nWitdh / 2, m_stSize.nHeight / 2, 0.0f);
		
		matWorld = matWorld * matT1 * matR * matT2 * m_matWorld;
		
		pSprite->SetTransform(&matWorld);
		SetRect(&rc, 0, 0, m_stSize.nWitdh, m_stSize.nHeight);
		pSprite->Draw(m_pTexture, &rc, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0), m_color);

	}
	else if ((!m_isBoard || !m_isNoise) && !m_isMove)
	{
		RECT rc;

		tMat._11 = m_xSize;
		tMat._22 = m_ySize;

		pSprite->SetTransform(&tMat);
		SetRect(&rc, 0, 0, m_stSize.nWitdh, m_stSize.nHeight);
		pSprite->Draw(m_pTexture, &rc, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0), m_color);
	}

	pSprite->End();

	UIObject::Render(pSprite);
}