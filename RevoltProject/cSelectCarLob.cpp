#include "stdafx.h"
#include "cSelectCarLob.h"
#include "UIImageView.h"
#include "UITextImageView.h"

cSelectCarLob::cSelectCarLob()
{
}

cSelectCarLob::~cSelectCarLob()
{
}

void cSelectCarLob::Setup()
{
	iLobby::Setup();

	UIImageView* pImageView1 = new UIImageView;
	pImageView1->SetPosition(80, 50);
	pImageView1->SetXSize(4.0f);
	pImageView1->SetYSize(4.0f);
	pImageView1->SetIsBoard(true);
	pImageView1->SetTexture("Maps/Front/Image/blueRing.png");

	UIImageView* pImageView2 = new UIImageView;
	pImageView2->SetXSize(1.2f);
	pImageView2->SetYSize(1.2f);
	pImageView2->SetPosition(17, 17);
	pImageView2->SetTexture("Maps/Front/Image/bluecar.png");

	UIImageView* pImageView3 = new UIImageView;
	pImageView3->SetPosition(120, 25);
	pImageView3->SetIsBoard(true);
	pImageView3->SetXSize(20.0f);
	pImageView3->SetYSize(1.0f);
	pImageView3->SetTexture("Maps/Front/Image/ring.png");

	UITextImageView* pImageView4 = new UITextImageView;
	pImageView4->SetTexture("Maps/Front/Image/font1.png");
	pImageView4->SetText("SELECT CAR");
	pImageView4->SetXSize(1.5f);
	pImageView4->SetYSize(1.5f);
	pImageView4->SetPosition(180, 45);

	UIImageView* pImageView5 = new UIImageView;
	pImageView5->SetPosition(50, 130);
	pImageView5->SetIsBoard(true);
	pImageView5->SetXSize(28.0f);
	pImageView5->SetYSize(16.0f);
	pImageView5->SetTexture("Maps/Front/Image/ring.png");

	UITextImageView* pImageView6 = new UITextImageView;
	pImageView6->SetTexture("Maps/Front/Image/font2.png");
	pImageView6->SetText("Class");
	pImageView6->SetPosition(60, 100);

	UITextImageView* pImageView7 = new UITextImageView;
	pImageView7->SetTexture("Maps/Front/Image/font2.png");
	pImageView7->SetText("Rating");
	pImageView7->SetPosition(60, 125);

	UITextImageView* pImageView8 = new UITextImageView;
	pImageView8->SetTexture("Maps/Front/Image/font2.png");
	pImageView8->SetText("Speed");
	pImageView8->SetPosition(60, 150);

	UITextImageView* pImageView9 = new UITextImageView;
	pImageView9->SetTexture("Maps/Front/Image/font2.png");
	pImageView9->SetText("Acc");
	pImageView9->SetPosition(60, 175);

	UITextImageView* pImageView10 = new UITextImageView;
	pImageView10->SetTexture("Maps/Front/Image/font2.png");
	pImageView10->SetText("Weight");
	pImageView10->SetPosition(60, 200);

	UITextImageView* pImageView11 = new UITextImageView;
	pImageView11->SetTexture("Maps/Front/Image/font2.png");
	pImageView11->SetText("Trans");
	pImageView11->SetPosition(60, 225);

	UITextImageView* pImageView12 = new UITextImageView;
	pImageView12->SetTexture("Maps/Front/Image/font2.png");
	pImageView12->SetCarIndex(1);
	pImageView12->SetIsRealTime(true);
	pImageView12->SetPosition(200, 100);
	pImageView12->SetColor(D3DCOLOR_ARGB(255, 250, 237, 125));

	UITextImageView* pImageView13 = new UITextImageView;
	pImageView13->SetTexture("Maps/Front/Image/font2.png");
	pImageView13->SetCarIndex(2);
	pImageView13->SetIsRealTime(true);
	pImageView13->SetPosition(200, 125);
	pImageView13->SetColor(D3DCOLOR_ARGB(255, 250, 237, 125));

	UITextImageView* pImageView14 = new UITextImageView;
	pImageView14->SetTexture("Maps/Front/Image/font2.png");
	pImageView14->SetCarIndex(3);
	pImageView14->SetIsRealTime(true);
	pImageView14->SetPosition(200, 150);
	pImageView14->SetColor(D3DCOLOR_ARGB(255, 250, 237, 125));

	UITextImageView* pImageView15 = new UITextImageView;
	pImageView15->SetTexture("Maps/Front/Image/font2.png");
	pImageView15->SetCarIndex(4);
	pImageView15->SetIsRealTime(true);
	pImageView15->SetPosition(200, 175);
	pImageView15->SetColor(D3DCOLOR_ARGB(255, 250, 237, 125));

	UITextImageView* pImageView16 = new UITextImageView;
	pImageView16->SetTexture("Maps/Front/Image/font2.png");
	pImageView16->SetCarIndex(5);
	pImageView16->SetIsRealTime(true);
	pImageView16->SetPosition(200, 200);
	pImageView16->SetColor(D3DCOLOR_ARGB(255, 250, 237, 125));

	UITextImageView* pImageView17 = new UITextImageView;
	pImageView17->SetTexture("Maps/Front/Image/font2.png");
	pImageView17->SetCarIndex(6);
	pImageView17->SetIsRealTime(true);
	pImageView17->SetPosition(200, 225);
	pImageView17->SetColor(D3DCOLOR_ARGB(255, 250, 237, 125));

	m_pCarName = new UITextImageView;
	m_pCarName->SetTexture("Maps/Front/Image/font2.png");
	m_pCarName->SetCarIndex(0);
	m_pCarName->SetIsRealTime(true);
	m_pCarName->SetPosition(50, 50);
	m_pCarName->SetColor(D3DCOLOR_ARGB(255, 250, 237, 125));

	m_pRootUI->AddChild(pImageView1);
	pImageView1->AddChild(pImageView2);
	pImageView1->AddChild(pImageView3);
	pImageView1->AddChild(pImageView4);
	pImageView1->AddChild(pImageView5);
	pImageView5->AddChild(pImageView6);
	pImageView5->AddChild(pImageView7);
	pImageView5->AddChild(pImageView8);
	pImageView5->AddChild(pImageView9);
	pImageView5->AddChild(pImageView10);
	pImageView5->AddChild(pImageView11);
	pImageView5->AddChild(pImageView12);
	pImageView5->AddChild(pImageView13);
	pImageView5->AddChild(pImageView14);
	pImageView5->AddChild(pImageView15);
	pImageView5->AddChild(pImageView16);
	pImageView5->AddChild(pImageView17);
	pImageView5->AddChild(m_pCarName);
}

void cSelectCarLob::Update()
{
	iLobby::Update();
}

void cSelectCarLob::Render(LPD3DXSPRITE pSprite)
{
	iLobby::Render(pSprite);
}

std::string cSelectCarLob::GetCarName()
{
	return m_pCarName->GetCarName();
}
