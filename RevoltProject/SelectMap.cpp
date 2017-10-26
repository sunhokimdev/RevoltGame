#include "stdafx.h"
#include "SelectMap.h"
#include "UITextImageView.h"
#include "UIImageView.h"

SelectMap::SelectMap()
	: m_selectMapType(0)
	, m_isUnLocked(true)
	, m_isOpenHood(false)
	, m_isOpenShip(false)
	, m_isOpenMuse(false)
	, m_isLockedRender(false)
	, m_LockedTime(0)
	, m_mapType(NONE)
{
}

SelectMap::~SelectMap()
{
}

void SelectMap::Setup()
{
	m_mapName = new UITextImageView;
	m_mapLength = new UITextImageView;
	m_mapDifficulty = new UITextImageView;
	m_mapImage = new UIImageView;
	m_mapImage->SetXSize(1.5f);
	m_mapImage->SetPosition(250, 100);
	m_mapImage->SetIsNoise(true);

	m_mapParent = new UIImageView;
	m_mapParent->SetPosition(80, 50);
	m_mapParent->SetXSize(4.0f);
	m_mapParent->SetYSize(4.0f);
	m_mapParent->SetIsBoard(true);
	m_mapParent->SetTexture("Maps/Front/Image/blueRing.png");

	UIImageView* pImageView63 = new UIImageView;
	pImageView63->SetXSize(1.2f);
	pImageView63->SetYSize(1.2f);
	pImageView63->SetPosition(17, 17);
	pImageView63->SetTexture("Maps/Front/Image/blueflag.png");

	UIImageView* pImageView64 = new UIImageView;
	pImageView64->SetPosition(120, 20);
	pImageView64->SetIsBoard(true);
	pImageView64->SetXSize(25.0f);
	pImageView64->SetYSize(1.0f);
	pImageView64->SetTexture("Maps/Front/Image/ring.png");

	UITextImageView* pImageView65 = new UITextImageView;
	pImageView65->SetTexture("Maps/Front/Image/font1.png");
	pImageView65->SetText("SELECT TRACK");
	pImageView65->SetXSize(1.5f);
	pImageView65->SetYSize(1.5f);
	pImageView65->SetPosition(180, 40);

	UIImageView* pImageView66 = new UIImageView;
	pImageView66->SetPosition(230, 400);
	pImageView66->SetIsBoard(true);
	pImageView66->SetXSize(25.0f);
	pImageView66->SetYSize(10.0f);
	pImageView66->SetTexture("Maps/Front/Image/ring.png");

	UITextImageView* pImageView67 = new UITextImageView;
	pImageView67->SetTexture("Maps/Front/Image/font2.png");
	pImageView67->SetText("Length");
	pImageView67->SetPosition(60, 80);

	UITextImageView* pImageView68 = new UITextImageView;
	pImageView68->SetTexture("Maps/Front/Image/font2.png");
	pImageView68->SetText("Difficulty");
	pImageView68->SetPosition(60, 105);

	m_LockedRing = new UIImageView;
	m_LockedRing->SetPosition(150, 180);
	m_LockedRing->SetIsBoard(true);
	m_LockedRing->SetXSize(2.0f);
	m_LockedRing->SetYSize(0.5f);
	m_LockedRing->SetTexture("Maps/Front/Image/ring.png");

	m_LockedTextImage = new UITextImageView;
	m_LockedTextImage->SetTexture("Maps/Front/Image/font2.png");
	m_LockedTextImage->SetColor(D3DCOLOR_ARGB(255, 255, 0, 0));
	m_LockedTextImage->SetText("Locked");
	m_LockedTextImage->SetPosition(15, 20);


	m_mapParent->AddChild(m_mapImage);
	m_mapParent->AddChild(pImageView63);
	m_mapParent->AddChild(pImageView64);
	m_mapParent->AddChild(pImageView65);
	m_mapParent->AddChild(pImageView66);
	pImageView66->AddChild(m_mapName);
	pImageView66->AddChild(pImageView67);
	pImageView66->AddChild(pImageView68);
	pImageView66->AddChild(m_mapLength);
	pImageView66->AddChild(m_mapDifficulty);
	m_mapImage->AddChild(m_LockedRing);
	m_LockedRing->AddChild(m_LockedTextImage);
}

void SelectMap::SetMapType(MAP_TYPE* mapType, int SelectNum)
{
	if (SelectNum == 0) *mapType = SUPERMARKET;
	else if (SelectNum == 1)
	{
		if (GetOpenHood() == true)	*mapType = NHOOD;
		else *mapType = NONE;

	}
	else if (SelectNum == 2)
	{
		if (GetOpenMuse() == true)	*mapType = MUSEUM;
		else *mapType = NONE;
	}
	else if (SelectNum == 3)
	{
		if (GetOpenShip() == true)	*mapType = SHIP;
		else *mapType = NONE;
	}

	MapTypeUpdate(SelectNum);
}


void SelectMap::MapTypeUpdate(int SelectNum)
{
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
			m_LockedRing->SetTexture("Maps/Front/Image/ring.png");
			m_LockedTextImage->SetTexture("Maps/Front/Image/font2.png");
			m_LockedTextImage->SetText("Locked");
		}
	}

	/*          Set Select Map          */

	/*
				mapType

			1 = SuperMarket
			2 = nHood
			3 = Muse
			4 = Ship

	*/
	// Stage Name Color
	if (m_isOpenHood) m_mapName->SetColor(D3DCOLOR_ARGB(255, 255, 255, 0));
	else if (m_isOpenShip) m_mapName->SetColor(D3DCOLOR_ARGB(255, 255, 255, 0));
	else if (m_isOpenMuse) m_mapName->SetColor(D3DCOLOR_ARGB(255, 255, 255, 0));
	else m_mapName->SetColor(D3DCOLOR_ARGB(150, 0, 0, 0));

	if (SelectNum == 0)
	{
		m_mapImage->SetTexture("Maps/Front/Image/market.bmp");
		m_LockedRing->SetTexture("");
		m_LockedTextImage->SetText("");
		m_isUnLocked = true;

		m_mapName->SetTexture("Maps/Front/Image/font2.png");
		m_mapName->SetColor(D3DCOLOR_ARGB(255, 255, 255, 0));
		m_mapName->SetText("SuperMarket");
		m_mapName->SetPosition(60, 50);

		m_mapLength->SetTexture("Maps/Front/Image/font2.png");
		m_mapLength->SetText("301 meters");
		m_mapLength->SetPosition(260, 80);

		m_mapDifficulty->SetTexture("Maps/Front/Image/font2.png");
		m_mapDifficulty->SetText("Easy");
		m_mapDifficulty->SetPosition(260, 105);
	}

	else if (SelectNum == 1)
	{
		m_mapImage->SetTexture("Maps/Front/Image/nhood.bmp");

		if (m_isOpenHood)
		{
			m_LockedRing->SetTexture("");
			m_LockedTextImage->SetText("");
			m_isUnLocked = true;
			m_mapName->SetColor(D3DCOLOR_ARGB(255, 255, 255, 0));
		}
		else
		{
			m_isUnLocked = false;
			m_mapName->SetColor(D3DCOLOR_ARGB(150, 0, 0, 0));
		}

		m_mapName->SetTexture("Maps/Front/Image/font2.png");
		m_mapName->SetText("Toys in the Hood");
		m_mapName->SetPosition(60, 50);

		m_mapLength->SetTexture("Maps/Front/Image/font2.png");
		m_mapLength->SetText("747 meters");
		m_mapLength->SetPosition(260, 80);

		m_mapDifficulty->SetTexture("Maps/Front/Image/font2.png");
		m_mapDifficulty->SetText("Easy");
		m_mapDifficulty->SetPosition(260, 105);
	}
	else if (SelectNum == 2)
	{
		m_mapImage->SetTexture("Maps/Front/Image/muse.bmp");

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
			m_mapName->SetColor(D3DCOLOR_ARGB(150, 0, 0, 0));
		}
		m_mapName->SetTexture("Maps/Front/Image/font2.png");
		m_mapName->SetText("Museum");
		m_mapName->SetPosition(60, 50);

		m_mapLength->SetTexture("Maps/Front/Image/font2.png");
		m_mapLength->SetText("600 meters");
		m_mapLength->SetPosition(260, 80);

		m_mapDifficulty->SetTexture("Maps/Front/Image/font2.png");
		m_mapDifficulty->SetText("Mideum");
		m_mapDifficulty->SetPosition(260, 105);
	}
	else if (SelectNum == 3)
	{
		m_mapImage->SetTexture("Maps/Front/Image/ship.bmp");

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
			m_mapName->SetColor(D3DCOLOR_ARGB(150, 0, 0, 0));
		}

		m_mapName->SetTexture("Maps/Front/Image/font2.png");
		m_mapName->SetText("Toytanic");
		m_mapName->SetPosition(60, 50);

		m_mapLength->SetTexture("Maps/Front/Image/font2.png");
		m_mapLength->SetText("742 meters");
		m_mapLength->SetPosition(260, 80);

		m_mapDifficulty->SetTexture("Maps/Front/Image/font2.png");
		m_mapDifficulty->SetText("Hard");
		m_mapDifficulty->SetPosition(260, 105);

	}
}
