#include "stdafx.h"
#include "cNetworkInRoom.h"
#include "UIImageView.h"
#include "UITextImageView.h"
#include "UITextView.h"

cNetworkInRoom::cNetworkInRoom()
	: m_index(0)
	, m_sizeY(20)
{
}


cNetworkInRoom::~cNetworkInRoom()
{
	SAFE_DELETE(m_pMap);
	SAFE_DELETE(m_pMapName);
	SAFE_DELETE(m_pChating);
	SAFE_DELETE(m_pText);
}

void cNetworkInRoom::Setup()
{
	iLobby::Setup();

	m_pMap = new UIImageView;
	m_pMap->SetPosition(30, 30);
	m_pMap->SetXSize(0.6f);
	m_pMap->SetYSize(0.5f);

	m_pMapName = new UITextImageView;
	m_pMapName->SetPosition(30, 170);
	m_pMapName->SetColor(D3DCOLOR_ARGB(255, 250, 237, 125));
	m_pMapName->SetXSize(1.5f);
	m_pMapName->SetYSize(1.5f);
	m_pMapName->SetTexture("UIImage/font2.png");

	m_pChating = new UITextImageView;
	m_pChating->SetIsChatingText(true);
	m_pChating->SetTexture("UIImage/font2.png");
	m_pChating->SetPosition(30, 20);
	m_pChating->SetColor(D3DCOLOR_ARGB(255, 250, 237, 125));

	m_pText = new UITextImageView;
	m_pText->SetTexture("UIImage/font2.png");
	m_pText->SetPosition(30, 20);
	m_pText->SetColor(D3DCOLOR_ARGB(255, 250, 237, 125));

	m_vecText.push_back(m_pText);

	UIImageView* pImageView1 = new UIImageView;
	pImageView1->SetPosition(80, 50);
	pImageView1->SetXSize(4.0f);
	pImageView1->SetYSize(4.0f);
	pImageView1->SetIsBoard(true);
	pImageView1->SetTexture("UIImage/blueRing.png");

	UIImageView* pImageView2 = new UIImageView;
	pImageView2->SetXSize(1.2f);
	pImageView2->SetYSize(1.2f);
	pImageView2->SetPosition(17, 17);
	pImageView2->SetTexture("UIImage/bluemulti.png");

	UIImageView* pImageView3 = new UIImageView;
	pImageView3->SetPosition(120, 25);
	pImageView3->SetIsBoard(true);
	pImageView3->SetXSize(30.0f);
	pImageView3->SetYSize(1.0f);
	pImageView3->SetTexture("UIImage/ring.png");

	UITextImageView* pImageView4 = new UITextImageView;
	pImageView4->SetTexture("UIImage/font1.png");
	pImageView4->SetText("MULTIPLAYER ROOM");
	pImageView4->SetXSize(1.5f);
	pImageView4->SetYSize(1.5f);
	pImageView4->SetPosition(180, 45);

	pImageView5 = new UIImageView;
	pImageView5->SetPosition(150, 200);
	pImageView5->SetIsBoard(true);
	pImageView5->SetXSize(30.0f);
	pImageView5->SetYSize(21.0f);
	pImageView5->SetTexture("UIImage/ring.png");

	UIImageView* pImageView6 = new UIImageView;
	pImageView6->SetPosition(520, 0);
	pImageView6->SetIsBoard(true);
	pImageView6->SetXSize(11.0f);
	pImageView6->SetYSize(27.0f);
	pImageView6->SetTexture("UIImage/ring.png");

	UIImageView* pImageView7 = new UIImageView;
	pImageView7->SetPosition(70, 540);
	pImageView7->SetIsBoard(true);
	pImageView7->SetXSize(30.0f);
	pImageView7->SetYSize(0.5f);
	pImageView7->SetTexture("UIImage/ring.png");

	m_pRootUI->AddChild(pImageView1);
	m_pRootUI->AddChild(pImageView5);
	pImageView1->AddChild(pImageView2);
	pImageView1->AddChild(pImageView3);
	pImageView1->AddChild(pImageView4);
	pImageView1->AddChild(pImageView7);
	pImageView5->AddChild(pImageView6);
	pImageView5->AddChild(m_vecText[m_index]);
	pImageView6->AddChild(m_pMap);
	pImageView6->AddChild(m_pMapName);
	pImageView7->AddChild(m_pChating);

	for (int i = 0; i < 1000; i++)
	{
		UITextImageView *pText = new UITextImageView;
		pText->SetTexture("Maps/Front/Image/font2.png");
		m_vecText.push_back(pText);

		pImageView5->AddChild(m_vecText[i]);
	}
}

void cNetworkInRoom::Update()
{
	iLobby::Update();
}

void cNetworkInRoom::Render(LPD3DXSPRITE pSprite)
{
	iLobby::Render(pSprite);
}

void cNetworkInRoom::SetMap(std::string mapName)
{
	if (mapName.find("Market") != -1)
	{
		m_pMap->SetTexture("Maps/Front/Image/market.bmp");
		m_pMapName->SetText("Market");
	}
}

std::string cNetworkInRoom::GetMsg()
{
	std::string str = std::string("[") + m_userName + std::string("] : ") + m_pChating->GetChatName();

	//m_vecText[m_index]->SetPosition(30, 20 * (m_index + 1));
	//m_vecText[m_index]->SetColor(D3DCOLOR_ARGB(255, 250, 237, 125));
	//m_vecText[m_index]->SetText(str);
	//m_index++;

	return str;
}

void cNetworkInRoom::SetResetCharText()
{
	m_pChating->SetChatText("");
}

void cNetworkInRoom::SetText(std::string str)
{
<<<<<<< HEAD
	UITextImageView *pText = new UITextImageView;
	pText->SetTexture("UIImage/font2.png");
	pText->SetPosition(30, 20 * (m_index+1));
	pText->SetColor(D3DCOLOR_ARGB(255, 250, 237, 125));
	
	str = std::string("[") + m_userName + std::string("] : ") + str;
	
	pText->SetText(str);

	m_vecText.push_back(pText);
	pImageView5->AddChild(m_vecText[m_index]);
	m_index++;
=======
	if (str.size() != 0)
	{
		m_vecText[m_index]->SetPosition(30, 20 * (m_index + 1));
		m_vecText[m_index]->SetColor(D3DCOLOR_ARGB(255, 250, 237, 125));
		m_vecText[m_index]->SetText(str);
		m_index++;
	}
>>>>>>> dddf369d0eba308ce85984f03c5cbe8132f7fde7
}
