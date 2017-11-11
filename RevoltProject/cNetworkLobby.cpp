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
	pImageView3->SetXSize(32.0f);
	pImageView3->SetYSize(1.0f);
	pImageView3->SetTexture("UIImage/ring.png");

	UITextImageView* pImageView4 = new UITextImageView;
	pImageView4->SetTexture("UIImage/font1.png");
	pImageView4->SetText("MULTIPLAYER LOBBY");
	pImageView4->SetXSize(1.5f);
	pImageView4->SetYSize(1.5f);
	pImageView4->SetPosition(180, 45);
	pImageView4->SetIndex(INT_MAX);

	UIImageView* pImageView5 = new UIImageView;
	pImageView5->SetPosition(240, 280);
	pImageView5->SetIsBoard(true);
	pImageView5->SetXSize(30.0f);
	pImageView5->SetYSize(1.0f);
	pImageView5->SetTexture("UIImage/ring.png");

	m_pServerIP = new UITextImageView;
	m_pServerIP->SetPosition(50, 25);
	m_pServerIP->SetIsChatingText(true);
	m_pServerIP->SetTexture("UIImage/font2.png");

	m_pRootUI->AddChild(pImageView1);
	m_pRootUI->AddChild(pImageView5);
	pImageView1->AddChild(pImageView2);
	pImageView1->AddChild(pImageView3);
	pImageView1->AddChild(pImageView4);
	pImageView5->AddChild(m_pServerIP);
}

void cNetworkLobby::Update()
{
	iLobby::Update();
}

void cNetworkLobby::Render(LPD3DXSPRITE pSprite)
{
	iLobby::Render(pSprite);
}

std::string cNetworkLobby::GetServerIP()
{
	return m_pServerIP->GetChatName();
}
