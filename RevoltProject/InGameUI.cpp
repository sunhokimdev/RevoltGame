#include "stdafx.h"
#include "InGameUI.h"
#include "UITextImageView.h"
#include "UIImageView.h"

InGameUI::InGameUI()
	: m_pLobby(NULL)
{
}

InGameUI::~InGameUI()
{
	SAFE_DELETE(m_pRootUI);
	SAFE_DELETE(m_pItemImage);
	SAFE_DELETE(m_pLobby);
}

void InGameUI::Setup()
{
	m_pRootUI = new UIObject;

	UITextImageView* pImageView1 = new UITextImageView;
	pImageView1->SetTexture("Maps/Front/Image/font2.png");
	pImageView1->SetText("Lab");
	pImageView1->SetXSize(1.0f);
	pImageView1->SetYSize(1.0f);
	pImageView1->SetPosition(30, 20);
	pImageView1->SetColor(D3DCOLOR_ARGB(255, 61, 183, 204));

	UITextImageView* pImageView2 = new UITextImageView;
	pImageView2->SetTexture("Maps/Front/Image/font2.png");
	pImageView2->SetText("Last Lap");
	pImageView2->SetXSize(1.0f);
	pImageView2->SetYSize(1.0f);
	pImageView2->SetPosition(900, 20);
	pImageView2->SetColor(D3DCOLOR_ARGB(255, 61, 183, 204));

	UITextImageView* pImageView3 = new UITextImageView;
	pImageView3->SetTexture("Maps/Front/Image/font2.png");
	pImageView3->SetText("Best Lab");
	pImageView3->SetXSize(1.0f);
	pImageView3->SetYSize(1.0f);
	pImageView3->SetPosition(0, 50);
	pImageView3->SetColor(D3DCOLOR_ARGB(255, 61, 183, 204));

	UITextImageView* pImageView4 = new UITextImageView;
	pImageView4->SetTexture("Maps/Front/Image/font2.png");
	pImageView4->SetText("Lab");
	pImageView4->SetXSize(1.0f);
	pImageView4->SetYSize(1.0f);
	pImageView4->SetPosition(39, 100);
	pImageView4->SetColor(D3DCOLOR_ARGB(255, 61, 183, 204));

	UITextImageView* pImageView5 = new UITextImageView;
	pImageView5->SetTexture("Maps/Front/Image/font2.png");
	pImageView5->SetText("Race");
	pImageView5->SetXSize(1.0f);
	pImageView5->SetYSize(1.0f);
	pImageView5->SetPosition(32, 150);
	pImageView5->SetColor(D3DCOLOR_ARGB(255, 61, 183, 204));

	UIImageView* pImageView6 = new UIImageView;
	pImageView6->SetXSize(1.2f);
	pImageView6->SetYSize(1.2f);
	pImageView6->SetPosition(-5, 50);
	pImageView6->SetTexture("Maps/Front/Image/itemframe.png");

	UIImageView* pImageView7 = new UIImageView;
	pImageView7->SetIsBoard(true);
	pImageView7->SetXSize(12.0f);
	pImageView7->SetYSize(2.5f);
	pImageView7->SetPosition(20, 600);
	pImageView7->SetTexture("Maps/Front/Image/ring.png");

	UIImageView* pImageView8 = new UIImageView;
	pImageView8->SetIsBoard(true);
	pImageView8->SetXSize(12.0f);
	pImageView8->SetYSize(2.5f);
	pImageView8->SetPosition(20, 600);
	pImageView8->SetTexture("Maps/Front/Image/ring.png");

	m_pItemImage = new UIImageView;
	m_pItemImage->SetXSize(1.2f);
	m_pItemImage->SetYSize(1.2f);
	m_pItemImage->SetPosition(22, 22);
	m_pItemImage->SetIsItem(true);
	m_pItemImage->SetTexture("Maps/Front/Image/itemlist.png");


	// 속도계 추가
	UIImageView* pSpeedFrame = new UIImageView;
	pSpeedFrame->SetIsSpeedFrame(true);
	pSpeedFrame->SetXSize(1.2f);
	pSpeedFrame->SetYSize(1.2f);
	pSpeedFrame->SetPosition(750, 650);
	pSpeedFrame->SetTexture("Maps/Front/Image/speedFrame.png");

	UIImageView* pSpeedometerImage = new UIImageView;
	pSpeedometerImage->SetIsSpeed(true);
	pSpeedometerImage->SetXSize(1.2f);
	pSpeedometerImage->SetYSize(1.2f);
	pSpeedometerImage->SetPosition(0, 0);
	pSpeedometerImage->SetTexture("Maps/Front/Image/speed.png");

	UITextImageView* pSpeed_mph = new UITextImageView;
	pSpeed_mph->SetTexture("Maps/Front/Image/font2.png");
	pSpeed_mph->SetText("mph");
	pSpeed_mph->SetXSize(1.0f);
	pSpeed_mph->SetYSize(1.0f);
	pSpeed_mph->SetPosition(170, 8);
	pSpeed_mph->SetColor(D3DCOLOR_ARGB(255, 61, 183, 204));

	m_pRootUI->AddChild(pImageView1);
	m_pRootUI->AddChild(pImageView2);
	m_pRootUI->AddChild(pImageView7);
	m_pRootUI->AddChild(pSpeedFrame);
	pImageView1->AddChild(pImageView6);
	pImageView2->AddChild(pImageView3);
	pImageView2->AddChild(pImageView4);
	pImageView2->AddChild(pImageView5);
	pImageView6->AddChild(m_pItemImage);
	pSpeedFrame->AddChild(pSpeedometerImage);
	pSpeedFrame->AddChild(pSpeed_mph);
}

void InGameUI::Update()
{
	if (m_pRootUI)
		m_pRootUI->Update();


}

void InGameUI::Render(LPD3DXSPRITE pSprite)
{
	if (m_pRootUI)
		m_pRootUI->Render(pSprite);

}
