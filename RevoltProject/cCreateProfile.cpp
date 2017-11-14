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

	m_pIV_CP_BodyRing = new UIImageView;
	m_pIV_CP_BodyRing->SetPosition(300, 180);
	m_pIV_CP_BodyRing->SetIsBoard(true);
	m_pIV_CP_BodyRing->SetXSize(25.0f);
	m_pIV_CP_BodyRing->SetYSize(3.0f);
	m_pIV_CP_BodyRing->SetTexture("UIImage/ring.png");

	m_pTIV_CP_BodyFont = new UITextImageView;
	m_pTIV_CP_BodyFont->SetIndex(INT_MAX);
	m_pTIV_CP_BodyFont->SetColor(D3DCOLOR_ARGB(255, 242, 150, 97));
	m_pTIV_CP_BodyFont->SetPosition(30, 40);
	m_pTIV_CP_BodyFont->SetText("Player Name : ");
	m_pTIV_CP_BodyFont->SetTexture("UIImage/font2.png");

	m_pNameText = new UITextImageView;
	m_pNameText->SetIndex(INT_MAX);
	m_pNameText->SetPosition(160, 40);
	m_pNameText->SetIsChatingText(true);
	m_pNameText->SetTexture("UIImage/font2.png");
	m_pNameText->SetColor(D3DCOLOR_ARGB(255, 250, 237, 125));

	m_pIV_CP_BlueRing = new UIImageView;
	m_pIV_CP_BlueRing->SetPosition(-220, -130);
	m_pIV_CP_BlueRing->SetXSize(4.0f);
	m_pIV_CP_BlueRing->SetYSize(4.0f);
	m_pIV_CP_BlueRing->SetIsBoard(true);
	m_pIV_CP_BlueRing->SetTexture("UIImage/blueRing.png");

	m_pIV_CP_HeadRing = new UIImageView;
	m_pIV_CP_HeadRing->SetPosition(120, 25);
	m_pIV_CP_HeadRing->SetIsBoard(true);
	m_pIV_CP_HeadRing->SetXSize(23.0f);
	m_pIV_CP_HeadRing->SetYSize(1.0f);
	m_pIV_CP_HeadRing->SetTexture("UIImage/ring.png");

	m_pTIV_CP_HeadFont = new UITextImageView;
	m_pTIV_CP_HeadFont->SetIndex(INT_MAX);
	m_pTIV_CP_HeadFont->SetTexture("UIImage/font1.png");
	m_pTIV_CP_HeadFont->SetText("CREATE PROFILE");
	m_pTIV_CP_HeadFont->SetXSize(1.5f);
	m_pTIV_CP_HeadFont->SetYSize(1.5f);
	m_pTIV_CP_HeadFont->SetPosition(150, 45);

	m_pIV_CP_BlueToy = new UIImageView;
	m_pIV_CP_BlueToy->SetXSize(1.2f);
	m_pIV_CP_BlueToy->SetYSize(1.2f);
	m_pIV_CP_BlueToy->SetPosition(17, 17);
	m_pIV_CP_BlueToy->SetTexture("UIImage/bluetoy.png");

	m_pRootUI->AddChild(m_pIV_CP_BodyRing);
	m_pIV_CP_BodyRing->AddChild(m_pTIV_CP_BodyFont);
	m_pIV_CP_BodyRing->AddChild(m_pIV_CP_BlueRing);
	m_pIV_CP_BodyRing->AddChild(m_pNameText);

	m_pIV_CP_BlueRing->AddChild(m_pIV_CP_HeadRing);
	m_pIV_CP_BlueRing->AddChild(m_pTIV_CP_HeadFont);
	m_pIV_CP_BlueRing->AddChild(m_pIV_CP_BlueToy);
}

void cCreateProfile::Update()
{
	iLobby::Update();
}

void cCreateProfile::Render(LPD3DXSPRITE pSprite)
{
	iLobby::Render(pSprite);
}

void cCreateProfile::Destroy()
{
	SAFE_DELETE(m_pNameText);
	SAFE_DELETE(m_pNameText);
	SAFE_DELETE(m_pTIV_CP_BodyFont);
	SAFE_DELETE(m_pTIV_CP_HeadFont);
	SAFE_DELETE(m_pIV_CP_BodyRing);
	SAFE_DELETE(m_pIV_CP_BlueRing);
	SAFE_DELETE(m_pIV_CP_HeadRing);
	SAFE_DELETE(m_pIV_CP_BlueToy);
	iLobby::Destroy();
}

std::string cCreateProfile::GetName()
{
	return m_pNameText->GetChatName();
}
