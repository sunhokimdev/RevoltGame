#include "stdafx.h"
#include "SelectMap.h"
#include "UITextImageView.h"
#include "UIImageView.h"

#define INCREASE_NOISE_X	20.0f
#define LEFT_NOISE_X		-500.0f
#define RIGHT_NOISE_X		-512.0f
#define LIMIT_NOISE_X		-256.0f

SelectMap::SelectMap()
	: m_selectMapType(0)
	, m_isUnLocked(true)
	, m_isOpenGarden(false)
	, m_isOpenShip(false)
	, m_isOpenMuse(false)
	, m_isLockedRender(false)
	, m_isMove(false)
	, m_LockedTime(0)
	, m_mapType(NONE)
	, m_FileName("Maps/Front/Image/market.bmp")
	, m_pTexture(NULL)
	, LeftNoiseX(LEFT_NOISE_X)
	, RightNoiseX(RIGHT_NOISE_X)
	, UpNoiseY(LIMIT_NOISE_X)
	, DownNoiseY(RIGHT_NOISE_X)
	
{
}

SelectMap::~SelectMap()
{
	SAFE_RELEASE(m_pTexture);
}

void SelectMap::SetTexture(char * szFullPath)
{
	D3DXIMAGE_INFO stImageInfo;

	m_pTexture = g_pTextureManager->GetTexture(szFullPath, &stImageInfo);

	m_stSize.nWitdh = stImageInfo.Width;
	m_stSize.nHeight = stImageInfo.Height;
}

void SelectMap::Setup()
{

	m_mapName = new UITextImageView;
	m_mapLength = new UITextImageView;
	m_mapDifficulty = new UITextImageView;

	m_mapName->SetIndex(INT_MAX);
	m_mapLength->SetIndex(INT_MAX);
	m_mapDifficulty->SetIndex(INT_MAX);

	
	

	m_mapParent = new UIImageView;
	m_mapParent->SetPosition(80, 50);
	m_mapParent->SetXSize(4.0f);
	m_mapParent->SetYSize(4.0f);
	m_mapParent->SetIsBoard(true);
	m_mapParent->SetTexture("UIImage/blueRing.png");

	UIImageView* pImageView63 = new UIImageView;
	pImageView63->SetXSize(1.2f);
	pImageView63->SetYSize(1.2f);
	pImageView63->SetPosition(17, 17);
	pImageView63->SetTexture("UIImage/blueflag.png");

	UIImageView* pImageView64 = new UIImageView;
	pImageView64->SetPosition(120, 20);
	pImageView64->SetIsBoard(true);
	pImageView64->SetXSize(25.0f);
	pImageView64->SetYSize(1.0f);
	pImageView64->SetTexture("UIImage/ring.png");

	UITextImageView* pImageView65 = new UITextImageView;
	pImageView65->SetTexture("UIImage/font1.png");
	pImageView65->SetText("SELECT TRACK");
	pImageView65->SetIndex(INT_MAX);
	pImageView65->SetXSize(1.5f);
	pImageView65->SetYSize(1.5f);
	pImageView65->SetPosition(180, 40);

	UIImageView* pImageView66 = new UIImageView;
	pImageView66->SetPosition(230, 400);
	pImageView66->SetIsBoard(true);
	pImageView66->SetXSize(25.0f);
	pImageView66->SetYSize(10.0f);
	pImageView66->SetTexture("UIImage/ring.png");

	UITextImageView* pImageView67 = new UITextImageView;
	pImageView67->SetTexture("UIImage/font2.png");
	pImageView67->SetText("Length");
	pImageView67->SetIndex(INT_MAX);
	pImageView67->SetPosition(60, 80);

	UITextImageView* pImageView68 = new UITextImageView;
	pImageView68->SetTexture("UIImage/font2.png");
	pImageView68->SetIndex(INT_MAX);
	pImageView68->SetText("Difficulty");
	pImageView68->SetPosition(60, 105);

	m_LockedRing = new UIImageView;
	m_LockedRing->SetPosition(400, 280);
	m_LockedRing->SetIsBoard(true);
	m_LockedRing->SetXSize(2.0f);
	m_LockedRing->SetYSize(0.5f);
	m_LockedRing->SetTexture("UIImage/ring.png");

	m_LockedTextImage = new UITextImageView;
	m_LockedTextImage->SetTexture("UIImage/font2.png");
	m_LockedTextImage->SetColor(D3DCOLOR_ARGB(255, 255, 0, 0));
	m_LockedTextImage->SetText("Locked");
	m_LockedTextImage->SetIndex(INT_MAX);
	m_LockedTextImage->SetPosition(15, 20);

	//m_mapParent->AddChild(m_mapImage);
	m_mapParent->AddChild(pImageView63);
	m_mapParent->AddChild(pImageView64);
	m_mapParent->AddChild(pImageView65);
	m_mapParent->AddChild(pImageView66);
	pImageView66->AddChild(m_mapName);
	pImageView66->AddChild(pImageView67);
	pImageView66->AddChild(pImageView68);
	pImageView66->AddChild(m_mapLength);
	pImageView66->AddChild(m_mapDifficulty);
	m_mapParent->AddChild(m_LockedRing);
	m_LockedRing->AddChild(m_LockedTextImage);

	SetTexture(m_FileName);

}

void SelectMap::Update()
{
	if (m_isMove)
	{
		if (LeftNoiseX < LIMIT_NOISE_X)
			LeftNoiseX += INCREASE_NOISE_X;
		else
		{
			m_isMove = false;
			LeftNoiseX = LEFT_NOISE_X;
			RightNoiseX = RIGHT_NOISE_X;
		}
	}
}

void SelectMap::SetMapType(MAP_TYPE* mapType, int SelectNum)
{
	if (SelectNum == 0) *mapType = SUPERMARKET;
	else if (SelectNum == 1)
	{
		if (m_isUnLocked)	*mapType = GARDEN;
		else *mapType = NONE;

	}
	else if (SelectNum == 2)
	{
		if (m_isUnLocked)	*mapType = MUSEUM;
		else *mapType = NONE;
	}
	else if (SelectNum == 3)
	{
		if (m_isUnLocked)	*mapType = SHIP;
		else *mapType = NONE;
	}

	MapTypeUpdate(SelectNum);
}


void SelectMap::MapTypeUpdate(int SelectNum)
{
	
	/*          Set Select Map          */

	/*
				mapType

			1 = SuperMarket
			2 = nHood
			3 = Muse
			4 = Ship

	*/
	// Stage Name Color
	if (m_isOpenGarden) m_mapName->SetColor(D3DCOLOR_ARGB(255, 255, 255, 0));
	else if (m_isOpenShip) m_mapName->SetColor(D3DCOLOR_ARGB(255, 255, 255, 0));
	else if (m_isOpenMuse) m_mapName->SetColor(D3DCOLOR_ARGB(255, 255, 255, 0));
	else m_mapName->SetColor(D3DCOLOR_ARGB(150, 0, 0, 0));

	if (SelectNum == 0)
	{
		m_FileName = "Maps/Front/Image/market.bmp";

		SetTexture(m_FileName);

		m_LockedRing->SetTexture("");
		m_LockedTextImage->SetText("");
		m_isUnLocked = true;

		m_mapName->SetTexture("UIImage/font2.png");
		m_mapName->SetColor(D3DCOLOR_ARGB(255, 255, 255, 0));
		m_mapName->SetText("SuperMarket 1");
		m_mapName->SetPosition(60, 50);

		m_mapLength->SetTexture("UIImage/font2.png");
		m_mapLength->SetText("301 meters");
		m_mapLength->SetPosition(260, 80);

		m_mapDifficulty->SetTexture("UIImage/font2.png");
		m_mapDifficulty->SetText("Easy");
		m_mapDifficulty->SetPosition(260, 105);
	}

	else if (SelectNum == 1)
	{
		m_FileName = "Maps/Front/Image/garden.bmp";
		SetTexture(m_FileName);

		if (m_isOpenGarden)
		{
			m_LockedRing->SetTexture("");
			m_LockedTextImage->SetText("");
			m_isUnLocked = true;
			m_mapName->SetColor(D3DCOLOR_ARGB(255, 255, 255, 0));
		}
		else
		{
			m_isUnLocked = false;
			m_mapName->SetColor(D3DCOLOR_ARGB(50, 255, 255, 255));
		}

		m_mapName->SetTexture("UIImage/font2.png");
		m_mapName->SetText("Botanical Garden");
		m_mapName->SetPosition(60, 50);

		m_mapLength->SetTexture("UIImage/font2.png");
		m_mapLength->SetText("323 meters");
		m_mapLength->SetPosition(260, 80);

		m_mapDifficulty->SetTexture("UIImage/font2.png");
		m_mapDifficulty->SetText("Easy");
		m_mapDifficulty->SetPosition(260, 105);
	}
	else if (SelectNum == 2)
	{
		m_FileName = "Maps/Front/Image/muse.bmp";
		SetTexture(m_FileName);

		if (m_isOpenMuse)
		{
			m_LockedRing->SetTexture("");
			m_LockedTextImage->SetText("");
			m_isUnLocked = true;
			m_mapName->SetColor(D3DCOLOR_ARGB(255, 255, 255, 0));
		}
		else
		{
			m_isUnLocked = false;
			m_mapName->SetColor(D3DCOLOR_ARGB(50, 255, 255, 255));
		}
		m_mapName->SetTexture("UIImage/font2.png");
		m_mapName->SetText("Museum 1");
		m_mapName->SetPosition(60, 50);

		m_mapLength->SetTexture("UIImage/font2.png");
		m_mapLength->SetText("600 meters");
		m_mapLength->SetPosition(260, 80);

		m_mapDifficulty->SetTexture("UIImage/font2.png");
		m_mapDifficulty->SetText("Mideum");
		m_mapDifficulty->SetPosition(260, 105);
	}
	else if (SelectNum == 3)
	{
		m_FileName = "Maps/Front/Image/ship.bmp";
		SetTexture(m_FileName);

		if (m_isOpenShip)
		{
			m_LockedRing->SetTexture("");
			m_LockedTextImage->SetText("");
			m_isUnLocked = true;
			m_mapName->SetColor(D3DCOLOR_ARGB(255, 255, 255, 0));
		}
		else
		{
			m_isUnLocked = false;
			m_mapName->SetColor(D3DCOLOR_ARGB(50, 255, 255, 255));
		}

		m_mapName->SetTexture("UIImage/font2.png");
		m_mapName->SetText("Toytanic 1");
		m_mapName->SetPosition(60, 50);

		m_mapLength->SetTexture("UIImage/font2.png");
		m_mapLength->SetText("742 meters");
		m_mapLength->SetPosition(260, 80);

		m_mapDifficulty->SetTexture("UIImage/font2.png");
		m_mapDifficulty->SetText("Hard");
		m_mapDifficulty->SetPosition(260, 105);

	}
	/*          Control Locked Image, Text          */
	if (!m_isUnLocked)
	{
		if ((m_LockedTime / 10) % 2 == 1)
			m_isLockedRender = true;
		else
			m_isLockedRender = false;

		m_LockedTime++;

		if (m_LockedTime > 1000000)
			m_LockedTime = 0;

		if (m_isLockedRender)
		{
			m_LockedRing->SetTexture("");
			m_LockedTextImage->SetText("");
		}
		else
		{
			m_LockedRing->SetTexture("UIImage/ring.png");
			m_LockedTextImage->SetTexture("UIImage/font2.png");
			m_LockedTextImage->SetText("Locked");
		}
	}
}

void SelectMap::Render(LPD3DXSPRITE pSprite)
{
	D3DXMATRIXA16 matS, matR, matT, matView, matWorld;

	D3DXMatrixIdentity(&matWorld);

	D3DXMatrixScaling(&matS, 0.02f, 0.013f, 0.01f);
	D3DXMatrixRotationZ(&matR, D3DX_PI);
	D3DXMatrixTranslation(&matT, 23, 7.5f, -15.3);

	matWorld = matS * matR * matT;

	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
	pSprite->SetWorldViewLH(NULL, &matView);

	pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE | D3DXSPRITE_BILLBOARD);

	pSprite->SetTransform(&matWorld);

	RECT rc;

	if (m_isMove)
		SetRect(&rc, RightNoiseX, 0, LeftNoiseX, m_stSize.nHeight);
	if(!m_isMove)
		SetRect(&rc, 0, 0, m_stSize.nWitdh, m_stSize.nHeight);

	pSprite->Draw(m_pTexture, &rc, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0), 0xFFFFFFFF);

	pSprite->End();

}

void SelectMap::Destroy()
{
	SAFE_RELEASE(m_pTexture);
	SAFE_DELETE(m_mapParent);
	SAFE_DELETE(m_mapName);
	SAFE_DELETE(m_mapLength);
	SAFE_DELETE(m_mapDifficulty);
	SAFE_DELETE(m_LockedRing);
	SAFE_DELETE(m_LockedTextImage);
}
