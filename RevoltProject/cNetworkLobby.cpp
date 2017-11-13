#include "stdafx.h"
#include "cNetworkLobby.h"
#include "UIObject.h"
#include "UIImageView.h"
#include "UITextImageView.h"
#include "cNetwork.h"

cNetworkLobby::cNetworkLobby()
{
}

cNetworkLobby::~cNetworkLobby()
{
}

void cNetworkLobby::Setup()
{
	m_pRootUI = new UIObject;

	pImageView1 = new UIImageView;
	pImageView1->SetPosition(80, 50);
	pImageView1->SetXSize(4.0f);
	pImageView1->SetYSize(4.0f);
	pImageView1->SetIsBoard(true);
	pImageView1->SetTexture("UIImage/blueRing.png");

	pImageView2 = new UIImageView;
	pImageView2->SetXSize(1.2f);
	pImageView2->SetYSize(1.2f);
	pImageView2->SetPosition(17, 17);
	pImageView2->SetTexture("UIImage/bluemulti.png");

	pImageView3 = new UIImageView;
	pImageView3->SetPosition(120, 25);
	pImageView3->SetIsBoard(true);
	pImageView3->SetXSize(32.0f);
	pImageView3->SetYSize(1.0f);
	pImageView3->SetTexture("UIImage/ring.png");

	pImageView4 = new UITextImageView;
	pImageView4->SetTexture("UIImage/font1.png");
	pImageView4->SetText("MULTIPLAYER LOBBY");
	pImageView4->SetIndex(INT_MAX);
	pImageView4->SetXSize(1.5f);
	pImageView4->SetYSize(1.5f);
	pImageView4->SetPosition(180, 45);

	pImageView5 = new UIImageView;
	pImageView5->SetPosition(150, 200);
	pImageView5->SetIsBoard(true);
	pImageView5->SetXSize(30.0f);
	pImageView5->SetYSize(27.0f);
	pImageView5->SetTexture("UIImage/ring.png");

	pImageView6 = new UIImageView;
	pImageView6->SetPosition(520, 0);
	pImageView6->SetIsBoard(true);
	pImageView6->SetXSize(11.0f);
	pImageView6->SetYSize(20.0f);
	pImageView6->SetTexture("UIImage/ring.png");

	pImageView7 = new UIImageView;
	pImageView7->SetPosition(520, 360);
	pImageView7->SetIsBoard(true);
	pImageView7->SetXSize(11.0f);
	pImageView7->SetYSize(3.2f);
	pImageView7->SetTexture("UIImage/ring.png");

	pImageView8 = new UITextImageView;
	pImageView8->SetTexture("UIImage/font2.png");
	pImageView8->SetText("F5 CREATE ROOM");
	pImageView8->SetIndex(INT_MAX);
	pImageView8->SetColor(D3DCOLOR_ARGB(255, 250, 237, 125));
	pImageView8->SetXSize(1.5f);
	pImageView8->SetYSize(1.5f);
	pImageView8->SetPosition(25, 40);

	pImageView9 = new UITextImageView;
	pImageView9->SetTexture("UIImage/font2.png");
	pImageView9->SetText("USER NAME");
	pImageView9->SetColor(D3DCOLOR_ARGB(255, 250, 237, 125));
	pImageView9->SetIndex(INT_MAX);
	pImageView9->SetXSize(1.5f);
	pImageView9->SetYSize(1.5f);
	pImageView9->SetPosition(25, 60);

	pImageView10 = new UITextImageView;
	pImageView10->SetTexture("UIImage/font2.png");
	pImageView10->SetText("CAR NAME");
	pImageView10->SetIndex(INT_MAX);
	pImageView10->SetColor(D3DCOLOR_ARGB(255, 250, 237, 125));
	pImageView10->SetXSize(1.5f);
	pImageView10->SetYSize(1.5f);
	pImageView10->SetPosition(25, 150);

	m_pUserName = new UITextImageView;
	m_pUserName->SetTexture("UIImage/font2.png");
	m_pUserName->SetColor(D3DCOLOR_ARGB(255, 61, 183, 204));
	m_pUserName->SetIndex(INT_MAX);
	m_pUserName->SetXSize(1.5f);
	m_pUserName->SetYSize(1.5f);
	m_pUserName->SetPosition(25, 100);

	m_pCarName = new UITextImageView;
	m_pCarName->SetTexture("UIImage/font2.png");
	m_pCarName->SetColor(D3DCOLOR_ARGB(255, 61, 183, 204));
	m_pCarName->SetIndex(INT_MAX);
	m_pCarName->SetXSize(1.5f);
	m_pCarName->SetYSize(1.5f);
	m_pCarName->SetPosition(25, 190);

	m_pRootUI->AddChild(pImageView1);
	m_pRootUI->AddChild(pImageView5);
	pImageView1->AddChild(pImageView2);
	pImageView1->AddChild(pImageView3);
	pImageView1->AddChild(pImageView4);
	pImageView5->AddChild(pImageView6);
	pImageView5->AddChild(pImageView7);
	pImageView6->AddChild(pImageView9);
	pImageView6->AddChild(pImageView10);
	pImageView6->AddChild(m_pUserName);
	pImageView6->AddChild(m_pCarName);
	pImageView7->AddChild(pImageView8);
}

void cNetworkLobby::Update()
{
	iLobby::Update();
}

void cNetworkLobby::Render(LPD3DXSPRITE pSprite)
{
	iLobby::Render(pSprite);
}

void cNetworkLobby::Destroy()
{
	SAFE_DELETE(m_pUserName);
	SAFE_DELETE(m_pCarName);
	SAFE_DELETE(pImageView1);
	SAFE_DELETE(pImageView2);
	SAFE_DELETE(pImageView3);
	SAFE_DELETE(pImageView4);
	SAFE_DELETE(pImageView5);
	SAFE_DELETE(pImageView6);
	SAFE_DELETE(pImageView7);
	SAFE_DELETE(pImageView8);
	SAFE_DELETE(pImageView9);
	SAFE_DELETE(pImageView10);


	iLobby::Destroy();
}

void cNetworkLobby::SetUserName(std::string pName)
{
	m_pUserName->SetText(pName);
}

void cNetworkLobby::SetCarName(std::string pName)
{
	m_pCarName->SetText(pName);
}

std::string cNetworkLobby::GetName()
{
	return m_pUserName->GetText();
}
