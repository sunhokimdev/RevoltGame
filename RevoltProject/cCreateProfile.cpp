#include "stdafx.h"
#include "cCreateProfile.h"
#include "UIImageView.h"
#include "UITextImageView.h"

cCreateProfile::cCreateProfile()
{
}

cCreateProfile::~cCreateProfile()
{
}

void cCreateProfile::Setup()
{
	iLobby::Setup();

	UIImageView* pIV_CP_BodyRing = new UIImageView;
	pIV_CP_BodyRing->SetPosition(300, 180);
	pIV_CP_BodyRing->SetIsBoard(true);
	pIV_CP_BodyRing->SetXSize(25.0f);
	pIV_CP_BodyRing->SetYSize(3.0f);
	pIV_CP_BodyRing->SetTexture("UIImage/ring.png");

	UITextImageView* pTIV_CP_BodyFont = new UITextImageView;
	pTIV_CP_BodyFont->SetIndex(INT_MAX);
	pTIV_CP_BodyFont->SetColor(D3DCOLOR_ARGB(255, 242, 150, 97));
	pTIV_CP_BodyFont->SetPosition(30, 40);
	pTIV_CP_BodyFont->SetText("Player Name : ");
	pTIV_CP_BodyFont->SetTexture("UIImage/font2.png");

	m_pNameText = new UITextImageView;
	m_pNameText->SetIndex(INT_MAX);
	m_pNameText->SetPosition(160, 40);
	m_pNameText->SetIsChatingText(true);
	m_pNameText->SetTexture("UIImage/font2.png");
	m_pNameText->SetColor(D3DCOLOR_ARGB(255, 250, 237, 125));

	UIImageView* pIV_CP_BlueRing = new UIImageView;
	pIV_CP_BlueRing->SetPosition(-220, -130);
	pIV_CP_BlueRing->SetXSize(4.0f);
	pIV_CP_BlueRing->SetYSize(4.0f);
	pIV_CP_BlueRing->SetIsBoard(true);
	pIV_CP_BlueRing->SetTexture("UIImage/blueRing.png");

	UIImageView* pIV_CP_HeadRing = new UIImageView;
	pIV_CP_HeadRing->SetPosition(120, 25);
	pIV_CP_HeadRing->SetIsBoard(true);
	pIV_CP_HeadRing->SetXSize(23.0f);
	pIV_CP_HeadRing->SetYSize(1.0f);
	pIV_CP_HeadRing->SetTexture("UIImage/ring.png");

	UITextImageView* pTIV_CP_HeadFont = new UITextImageView;
	pTIV_CP_HeadFont->SetIndex(INT_MAX);
	pTIV_CP_HeadFont->SetTexture("UIImage/font1.png");
	pTIV_CP_HeadFont->SetText("CREATE PROFILE");
	pTIV_CP_HeadFont->SetXSize(1.5f);
	pTIV_CP_HeadFont->SetYSize(1.5f);
	pTIV_CP_HeadFont->SetPosition(150, 45);

	UIImageView* pIV_CP_BlueToy = new UIImageView;
	pIV_CP_BlueToy->SetXSize(1.2f);
	pIV_CP_BlueToy->SetYSize(1.2f);
	pIV_CP_BlueToy->SetPosition(17, 17);
	pIV_CP_BlueToy->SetTexture("UIImage/bluetoy.png");

	m_pRootUI->AddChild(pIV_CP_BodyRing);
	pIV_CP_BodyRing->AddChild(pTIV_CP_BodyFont);
	pIV_CP_BodyRing->AddChild(pIV_CP_BlueRing);
	pIV_CP_BodyRing->AddChild(m_pNameText);

	pIV_CP_BlueRing->AddChild(pIV_CP_HeadRing);
	pIV_CP_BlueRing->AddChild(pTIV_CP_HeadFont);
	pIV_CP_BlueRing->AddChild(pIV_CP_BlueToy);
}

void cCreateProfile::Update()
{
	iLobby::Update();
}

void cCreateProfile::Render(LPD3DXSPRITE pSprite)
{
	iLobby::Render(pSprite);
}

std::string cCreateProfile::GetName()
{
	return m_pNameText->GetChatName();
}
