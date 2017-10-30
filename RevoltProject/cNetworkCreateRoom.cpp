#include "stdafx.h"
#include "cNetworkCreateRoom.h"
#include "SelectMap.h"
#include "UIObject.h"
#include "UIImageView.h"
#include "UITextImageView.h"

cNetworkCreateRoom::cNetworkCreateRoom()
{
}


cNetworkCreateRoom::~cNetworkCreateRoom()
{

}

void cNetworkCreateRoom::Setup()
{
	iLobby::Setup();

	m_pMapImage = new UIImageView;
	m_pMapImage->SetXSize(1.5);
	m_pMapImage->SetPosition(250, 100);
	m_pMapImage->SetIsNoise(true);
	m_pMapImage->SetTexture("Maps/Front/Image/market.bmp");

	m_pRoomName = new UITextImageView;
	m_pRoomName->SetIsChatingText(true);
	m_pRoomName->SetTexture("Maps/Front/Image/font2.png");
	m_pRoomName->SetColor(D3DCOLOR_ARGB(255, 250, 237, 125));
	m_pRoomName->SetPosition(40, 20);

	UIImageView* pImageView0 = new UIImageView;
	pImageView0->SetXSize(4.0f);
	pImageView0->SetYSize(4.0f);
	pImageView0->SetPosition(80, 50);
	pImageView0->SetIsBoard(true);
	pImageView0->SetTexture("Maps/Front/Image/blueRing.png");

	UIImageView* pImageView1 = new UIImageView;
	pImageView1->SetXSize(1.2f);
	pImageView1->SetYSize(1.2f);
	pImageView1->SetPosition(17, 17);
	pImageView1->SetTexture("Maps/Front/Image/blueflag.png");

	UIImageView* pImageView2 = new UIImageView;
	pImageView2->SetPosition(120, 20);
	pImageView2->SetIsBoard(true);
	pImageView2->SetXSize(25.0f);
	pImageView2->SetYSize(1.0f);
	pImageView2->SetTexture("Maps/Front/Image/ring.png");

	UITextImageView* pImageView3 = new UITextImageView;
	pImageView3->SetTexture("Maps/Front/Image/font1.png");
	pImageView3->SetText("SELECT TRACK");
	pImageView3->SetXSize(1.5f);
	pImageView3->SetYSize(1.5f);
	pImageView3->SetPosition(180, 40);

	UIImageView* pImageView4 = new UIImageView;
	pImageView4->SetPosition(230, 450);
	pImageView4->SetIsBoard(true);
	pImageView4->SetXSize(25.0f);
	pImageView4->SetYSize(10.0f);
	pImageView4->SetTexture("Maps/Front/Image/ring.png");

	UITextImageView* pImageView5 = new UITextImageView;
	pImageView5->SetTexture("Maps/Front/Image/font2.png");
	pImageView5->SetText("Length");
	pImageView5->SetPosition(60, 80);

	UITextImageView* pImageView6 = new UITextImageView;
	pImageView6->SetTexture("Maps/Front/Image/font2.png");
	pImageView6->SetText("Difficulty");
	pImageView6->SetPosition(60, 105);

	UIImageView* pImageView7 = new UIImageView;
	pImageView7->SetPosition(230, 370);
	pImageView7->SetIsBoard(true);
	pImageView7->SetXSize(25.0f);
	pImageView7->SetYSize(0.5f);
	pImageView7->SetTexture("Maps/Front/Image/ring.png");

	m_pRootUI->AddChild(pImageView0);
	pImageView0->AddChild(m_pMapImage);
	pImageView0->AddChild(pImageView1);
	pImageView0->AddChild(pImageView2);
	pImageView0->AddChild(pImageView3);
	pImageView0->AddChild(pImageView4);
	pImageView0->AddChild(pImageView7);
	pImageView4->AddChild(pImageView5);
	pImageView4->AddChild(pImageView6);
	pImageView7->AddChild(m_pRoomName);
}

void cNetworkCreateRoom::Update()
{
	iLobby::Update();
}

void cNetworkCreateRoom::Render(LPD3DXSPRITE pSprite)
{
	iLobby::Render(pSprite);
}

std::string cNetworkCreateRoom::GetRoomName()
{
	return m_pRoomName->GetChatName();
}

std::string cNetworkCreateRoom::GetImageName()
{
	return std::string("Market");
}
