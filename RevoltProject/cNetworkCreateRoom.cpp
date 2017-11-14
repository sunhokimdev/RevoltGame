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

	m_pRoomName = new UITextImageView;
	m_pRoomName->SetIsChatingText(true);
	m_pRoomName->SetTexture("UIImage/font2.png");
	m_pRoomName->SetColor(D3DCOLOR_ARGB(255, 250, 237, 125));
	m_pRoomName->SetPosition(40, 20);

	UIImageView* m_pTitleRing = new UIImageView;
	m_pTitleRing->SetXSize(4.0f);
	m_pTitleRing->SetYSize(4.0f);
	m_pTitleRing->SetPosition(80, 50);
	m_pTitleRing->SetIsBoard(true);
	m_pTitleRing->SetTexture("UIImage/blueRing.png");

	m_pFlag = new UIImageView;
	m_pFlag->SetXSize(1.2f);
	m_pFlag->SetYSize(1.2f);
	m_pFlag->SetPosition(17, 17);
	m_pFlag->SetTexture("UIImage/blueflag.png");

	m_pBoardRing = new UIImageView;
	m_pBoardRing->SetPosition(120, 20);
	m_pBoardRing->SetIsBoard(true);
	m_pBoardRing->SetXSize(25.0f);
	m_pBoardRing->SetYSize(1.0f);
	m_pBoardRing->SetTexture("UIImage/ring.png");

	m_pTitleFont = new UITextImageView;
	m_pTitleFont->SetTexture("UIImage/font1.png");
	m_pTitleFont->SetText("SELECT TRACK");
	m_pTitleFont->SetIndex(INT_MAX);
	m_pTitleFont->SetXSize(1.5f);
	m_pTitleFont->SetYSize(1.5f);
	m_pTitleFont->SetPosition(180, 40);

	m_pMapRing = new UIImageView;
	m_pMapRing->SetPosition(230, 450);
	m_pMapRing->SetIsBoard(true);
	m_pMapRing->SetXSize(25.0f);
	m_pMapRing->SetYSize(10.0f);
	m_pMapRing->SetTexture("UIImage/ring.png");

	m_pLength = new UITextImageView;
	m_pLength->SetTexture("UIImage/font2.png");
	m_pLength->SetText("Length");
	m_pLength->SetIndex(INT_MAX);
	m_pLength->SetPosition(60, 80);

	m_pDifficulty = new UITextImageView;
	m_pDifficulty->SetTexture("UIImage/font2.png");
	m_pDifficulty->SetText("Difficulty");
	m_pDifficulty->SetIndex(INT_MAX);
	m_pDifficulty->SetPosition(60, 105);

	m_pRing = new UIImageView;
	m_pRing->SetPosition(230, 370);
	m_pRing->SetIsBoard(true);
	m_pRing->SetXSize(25.0f);
	m_pRing->SetYSize(0.5f);
	m_pRing->SetTexture("UIImage/ring.png");

	m_pRootUI->AddChild(m_pTitleRing);
	m_pTitleRing->AddChild(m_pFlag);
	m_pTitleRing->AddChild(m_pBoardRing);
	m_pTitleRing->AddChild(m_pTitleFont);
	m_pTitleRing->AddChild(m_pMapRing);
	m_pTitleRing->AddChild(m_pRing);
	m_pMapRing->AddChild(m_pLength);
	m_pMapRing->AddChild(m_pDifficulty);
	m_pRing->AddChild(m_pRoomName);
}

void cNetworkCreateRoom::Update()
{
	iLobby::Update();
}

void cNetworkCreateRoom::Render(LPD3DXSPRITE pSprite)
{
	iLobby::Render(pSprite);
}

void cNetworkCreateRoom::Destroy()
{
	SAFE_DELETE(m_pMapName);
	SAFE_DELETE(m_pMapDifficult);
	SAFE_DELETE(m_pMapLength);
	SAFE_DELETE(m_pRoomName);
	SAFE_DELETE(m_pMapName);
	SAFE_DELETE(m_pMapDifficult);
	SAFE_DELETE(m_pMapLength);
	SAFE_DELETE(m_pRoomName);
	SAFE_DELETE(m_pTitleFont);
	SAFE_DELETE(m_pLength);
	SAFE_DELETE(m_pDifficulty);

	iLobby::Destroy();
}

std::string cNetworkCreateRoom::GetRoomName()
{
	return m_pRoomName->GetChatName();
}

std::string cNetworkCreateRoom::GetImageName()
{
	return std::string("Market");
}
