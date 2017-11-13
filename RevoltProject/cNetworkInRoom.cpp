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
	SAFE_DELETE(m_pChating);
	SAFE_DELETE(m_pText);
}

void cNetworkInRoom::Setup()
{
	iLobby::Setup();

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
	pImageView4->SetIndex(INT_MAX);
	pImageView4->SetXSize(1.5f);
	pImageView4->SetYSize(1.5f);
	pImageView4->SetPosition(180, 45);

	UIImageView* pImageView5 = new UIImageView;
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
	pImageView7->AddChild(m_pChating);

	for (int i = 0; i < 500; i++)
	{
		UITextImageView *pText = new UITextImageView;
		pText->SetTexture("UIImage/font2.png");
		m_vecText.push_back(pText);
		m_vecText[i]->SetIndex(INT_MAX);

		pImageView5->AddChild(m_vecText[i]);
	}

	for (int i = 0; i < USER_SIZE; i++)
	{
		UITextImageView *pText = new UITextImageView;
		pText->SetTexture("UIImage/font2.png");
		m_vecUser.push_back(pText);
		m_vecUser[i]->SetIndex(INT_MAX);

		pImageView6->AddChild(m_vecUser[i]);
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

std::string cNetworkInRoom::GetMsg()
{
	std::string str = std::string("[") + g_pNetworkManager->GetClientName() + std::string("] : ") + m_pChating->GetChatName();

	return str;
}

void cNetworkInRoom::SetResetCharText()
{
	m_pChating->SetChatText("");
}

void cNetworkInRoom::SetText(std::string str)
{
	bool isEqual = false;
	int sum = 0;

	for (int i = 0;i < str.size()-1;++i)
	{
		sum += str[i];

		if (sum % 35 != 0)
		{
			isEqual = true;
			break;
		}
	}

	if (isEqual)
	{
		m_vecText[m_index]->SetPosition(30, 20 * (m_index + 1));
		m_vecText[m_index]->SetColor(D3DCOLOR_ARGB(255, 250, 237, 125));

		const char* pch = strtok((char*)str.c_str(), "#");

		m_vecText[m_index]->SetText(pch);

		m_index++;
	}
}

void cNetworkInRoom::SetUserText(std::string str, int index, D3DXCOLOR color)
{
	bool isEqual = false;
	int sum = 0;

	for (int i = 0; i < str.size() - 1; ++i)
	{
		sum += str[i];

		if (sum % 35 != 0)
		{
			isEqual = true;
			break;
		}
	}

	m_vecUser[index]->SetPosition(30, 20 * (index + 1));
	m_vecUser[index]->SetColor(color);

	const char* pch = strtok((char*)str.c_str(), "#");

	m_vecUser[index]->SetText(pch);
}

