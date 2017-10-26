#include "stdafx.h"
#include "Lobby.h"

/*   UI헤더파일 선언   */
#include "UIObject.h"
#include "UIImageView.h"
#include "UITextImageView.h"

#include "ObjectLoader.h"
#include "MtlTex.h"
#include "Camera.h"

/*      */
#include "Map.h"
#include "Thing.h"

#include "UserFileLoader.h"
#include "ProfileList.h"

Lobby::Lobby()
	: m_pSprite(NULL)
	, m_pObjMesh(NULL)
	, m_stateLobby(INTRO1)
	, m_time(0.0f)
	, m_select(0)
	, m_leftAndrightSelect(0)
	, m_PlayerName("")
	, m_isCreate(false)
	, m_isEnterName(false)
	, m_pfileList(NULL)
	, m_isflag(false)
{
}

Lobby::~Lobby()
{
	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_pObjMesh);

	for each(auto a in m_mapLobby)
	{
		delete[] a.second->m_pNextLob;
		SAFE_DELETE(a.second->m_pObject);
	}
}

void Lobby::Setup()
{
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

	UITextImageView::m_Select = &m_select;
	UITextImageView::m_LeftAndRightSelect = &m_leftAndrightSelect;
	UITextImageView::m_PlayerName = m_PlayerName;
	UITextImageView::m_isCreate = &m_isCreate;
	UITextImageView::m_isflag = &m_isflag;
	Thing::g_LobbyState = &m_stateLobby;
	Thing::g_select = &m_leftAndrightSelect;

	m_pfileList = new ProfileList;
	m_pfileList->ListLoad();
	m_vProfileList = m_pfileList->GetUpdateList();
	
	if (m_vProfileList.size() == 0)
	{
		UserFileLoader*	pCreate = new UserFileLoader;
		pCreate->CreateProfile("Player1");
	}

	SetUpUI();
}

void Lobby::Update()
{
	TimeUpdate();   // 시간 갱신 메서드
	CreateProfile();	// 프로필 생성
	KeyUpdate();   // 키 이벤트 갱신 메서드

	m_mapLobby[m_stateLobby]->m_pObject->Update();
}

void Lobby::Render()
{
	if (m_mapLobby[m_stateLobby]->m_pObject)
		m_mapLobby[m_stateLobby]->m_pObject->Render(m_pSprite);
}

void Lobby::KeyUpdate()
{
	if (g_pKeyManager->isOnceKeyDown(VK_DOWN))
	{
		m_select++;

		if (m_stateLobby == START_LOBBY)
		{
			if (m_vProfileList.size() <= m_select)
				m_select = 0;
		}
		else
		{
			if (m_mapLobby[m_stateLobby]->m_count <= m_select)
				m_select = 0;
		}
		g_pSoundManager->Play("menuUpDown.wav", 1.0f);
	}

	if (g_pKeyManager->isOnceKeyDown(VK_UP))
	{
		m_select--;

		if (m_stateLobby == START_LOBBY)
		{
			if (m_select < 0)
				m_select = m_vProfileList.size() - 1;
		}
		else
		{
			if (m_select < 0)
				m_select = m_mapLobby[m_stateLobby]->m_count - 1;
		}
		g_pSoundManager->Play("menuUpDown.wav", 1.0f);
	}

	if (g_pKeyManager->isOnceKeyDown(VK_RIGHT))
	{
		if (m_stateLobby == START_LOBBY)
		{
			m_leftAndrightSelect++;

			if (m_mapLobby[m_stateLobby]->m_selectCnt <= m_leftAndrightSelect)
				m_leftAndrightSelect = 0;
		
			g_pSoundManager->Play("menuLeftRight.wav", 1.0f);
		}
		else if (m_stateLobby == CREATE_PROFILE_LOBBY ||
			m_stateLobby == CREATE_PROFILE_LOBBY2)
		{
			Thing::g_xRotAngle += D3DX_PI / 15.0f;
			g_pSoundManager->Play("menuLeftRight.wav", 1.0f);
		}
		else if (m_stateLobby == SELECT_CAR_LOBBY)
		{
			m_leftAndrightSelect++;

			if (m_mapLobby[m_stateLobby]->m_selectCnt <= m_leftAndrightSelect)
				m_leftAndrightSelect = 0;

			g_pSoundManager->Play("boxslide.wav", 1.0f);
		}
	}

	if (g_pKeyManager->isOnceKeyDown(VK_LEFT))
	{
		if (m_stateLobby == START_LOBBY)
		{
			m_leftAndrightSelect--;

			if (m_leftAndrightSelect < 0)
				m_leftAndrightSelect = m_mapLobby[m_stateLobby]->m_selectCnt - 1;

			g_pSoundManager->Play("menuLeftRight.wav", 1.0f);
		}
		else if (m_stateLobby == CREATE_PROFILE_LOBBY ||
			m_stateLobby == CREATE_PROFILE_LOBBY2)
		{
			Thing::g_xRotAngle -= D3DX_PI / 15.0f;
			g_pSoundManager->Play("menuLeftRight.wav", 1.0f);
		}
		else if (m_stateLobby == SELECT_CAR_LOBBY)
		{
			m_leftAndrightSelect--;

			if (m_leftAndrightSelect < 0)
				m_leftAndrightSelect = m_mapLobby[m_stateLobby]->m_selectCnt - 1;

			g_pSoundManager->Play("boxslide.wav", 1.0f);
		}
	}

	/*   엔터 키 눌렀을 때 다음 로비로 들어가는 이벤트   */
	if (g_pKeyManager->isOnceKeyDown(VK_RETURN))
	{
		if (m_mapLobby[m_stateLobby]->m_pNextLob[m_select] != LOBBY_NONE)
		{
			if (m_stateLobby == START_LOBBY)
			{
				if (m_leftAndrightSelect == 0)		// load select
				{
					m_isflag = false;
					UITextImageView::m_isflag = &m_isflag;
					m_pfileList->ListLoad();
					m_vProfileList = m_pfileList->GetUpdateList();
					m_PlayerName = m_vProfileList[m_select].c_str();
					UITextImageView::m_PlayerName = m_PlayerName;
				}
				else if (m_leftAndrightSelect == 2)		// delete select
				{
					if (m_vProfileList.size() > 1)
					{
						UserFileLoader*	pDelete = new UserFileLoader;
						pDelete->DeleteProfile(m_vProfileList[m_select].c_str());
						m_pfileList->ListLoad();
						m_vProfileList = m_pfileList->GetUpdateList();
						m_mapLobby[START_LOBBY]->m_count = m_vProfileList.size();
						m_mapLobby[START_LOBBY]->m_pObject = m_pfileList->GetProfileList();
					}
				}
				m_stateLobby = m_mapLobby[START_LOBBY]->m_pNextLob[m_leftAndrightSelect];
			}
			else if (m_stateLobby == CREATE_PROFILE_LOBBY2)
			{
				m_isCreate = true;
				UITextImageView::m_isCreate = &m_isCreate;

				if (!m_isEnterName)
				{
					m_isEnterName = true;
					m_stateLobby = m_mapLobby[START_LOBBY]->m_pNextLob[1];
				}
			}
			else
			{
				m_stateLobby = m_mapLobby[m_stateLobby]->m_pNextLob[m_select];
			}
			m_pCamera->Setup(&m_mapLobby[m_stateLobby]->m_target);      // 카메라 변경
			m_pCamera->SetLookAt(&m_mapLobby[m_stateLobby]->m_camLookAt);
			m_time = 0.0f;
			m_select = 0;
			m_leftAndrightSelect = 0;

			if (m_stateLobby > INTRO3)
				g_pSoundManager->Play("menuNext.wav", 1.0f);
		}
		else if (m_stateLobby == START_LOBBY)
		{
			m_stateLobby = m_mapLobby[m_stateLobby]->m_pNextLob[m_leftAndrightSelect];
			m_pCamera->Setup(&m_mapLobby[m_stateLobby]->m_target);      // 카메라 변경
			m_pCamera->SetLookAt(&m_mapLobby[m_stateLobby]->m_camLookAt);
			m_time = 0.0f;
			m_select = 0;
			m_leftAndrightSelect = 0;
		
			if (m_stateLobby > INTRO3)
				g_pSoundManager->Play("menuNext.wav", 1.0f);
		}
	}

	/*   ESC 키 눌렀을 때 이전 로비로 들어가는 이벤트   */
	if (g_pKeyManager->isOnceKeyDown(VK_ESCAPE))
	{

		if (m_mapLobby[m_stateLobby]->m_prevLob != LOBBY_NONE)
		{
			m_stateLobby = m_mapLobby[m_stateLobby]->m_prevLob;
			m_pCamera->Setup(&m_mapLobby[m_stateLobby]->m_target);
			m_pCamera->SetLookAt(&m_mapLobby[m_stateLobby]->m_camLookAt);
			g_pSoundManager->Play("menuPrev.wav", 1.0f);
		}
	}

	if (g_pKeyManager->isStayKeyDown(VK_CONTROL))
	{
		m_stateLobby = START_LOBBY;
		m_pCamera->Setup(&m_mapLobby[m_stateLobby]->m_target);
		m_pCamera->SetLookAt(&m_mapLobby[m_stateLobby]->m_camLookAt);
	}
}

void Lobby::TimeUpdate()
{
	if (m_time > m_mapLobby[m_stateLobby]->m_time)
	{
		m_time = 0.0f;

		if (m_stateLobby == INTRO1)
			m_stateLobby = INTRO2;
		else if (m_stateLobby == INTRO2)
			m_stateLobby = INTRO3;
		else if (m_stateLobby == INTRO3)
		{
			m_stateLobby = START_LOBBY;
			m_pCamera->Setup(&m_mapLobby[m_stateLobby]->m_target);
			m_pCamera->SetLookAt(&m_mapLobby[m_stateLobby]->m_camLookAt);
		}
	}
	else
	{
		m_time++;
	}
}

void Lobby::SetUpUI()
{
	//===================================================================
	// - ## 10.15.19 ##
	// - written by 김선호
	// - @@ UI 추가작업은 여기서만 진행해야 한다.
	//===================================================================

	///////////////////////////////   구분   /////////////////////////////////////////

	/*   인트로 이미지   */
	UIImageView* pImageView1 = new UIImageView;
	pImageView1->SetPosition(0, 0);
	pImageView1->SetTexture("Maps/Front/Image/intro1.png");

	UIImageView* pImageView2 = new UIImageView;
	pImageView2->SetPosition(0, 0);
	pImageView2->SetTexture("Maps/Front/Image/intro2.png");

	UIImageView* pImageView3 = new UIImageView;
	pImageView3->SetPosition(0, 0);
	pImageView3->SetTexture("Maps/Front/Image/intro3.png");

	///////////////////////////////   구분   /////////////////////////////////////////

	UIImageView* pImageView100 = new UIImageView;
	pImageView100->SetPosition(-10, -140);
	pImageView100->SetTexture("Maps/Front/Image/revoltrogo.png");

	UIImageView* pImageView110 = new UIImageView;
	pImageView110->SetPosition(400, 250);
	pImageView110->SetIsBoard(true);
	pImageView110->SetXSize(11.5f);
	pImageView110->SetYSize(9.5f);
	pImageView110->SetTexture("Maps/Front/Image/ring.png");

	UITextImageView* pImageView120 = new UITextImageView;
	pImageView120->SetIndex(0);
	pImageView120->SetPosition(50, 25);
	pImageView120->SetText("Start Game");
	pImageView120->SetTexture("Maps/Front/Image/font2.png");

	UITextImageView* pImageView130 = new UITextImageView;
	pImageView130->SetIndex(1);
	pImageView130->SetPosition(50, 50);
	pImageView130->SetText("Best Trial Times");
	pImageView130->SetTexture("Maps/Front/Image/font2.png");

	UITextImageView* pImageView140 = new UITextImageView;
	pImageView140->SetIndex(2);
	pImageView140->SetPosition(50, 75);
	pImageView140->SetText("Progress Table");
	pImageView140->SetTexture("Maps/Front/Image/font2.png");

	UITextImageView* pImageView150 = new UITextImageView;
	pImageView150->SetIndex(3);
	pImageView150->SetPosition(50, 100);
	pImageView150->SetText("Options");
	pImageView150->SetTexture("Maps/Front/Image/font2.png");

	UITextImageView* pImageView160 = new UITextImageView;
	pImageView160->SetIndex(4);
	pImageView160->SetPosition(50, 125);
	pImageView160->SetText("Select Profile");
	pImageView160->SetTexture("Maps/Front/Image/font2.png");

	UITextImageView* pImageView170 = new UITextImageView;
	pImageView170->SetIndex(5);
	pImageView170->SetPosition(50, 150);
	pImageView170->SetText("Quit");
	pImageView170->SetTexture("Maps/Front/Image/font2.png");

	pImageView110->AddChild(pImageView120);
	pImageView110->AddChild(pImageView130);
	pImageView110->AddChild(pImageView140);
	pImageView110->AddChild(pImageView150);
	pImageView110->AddChild(pImageView160);
	pImageView110->AddChild(pImageView170);
	pImageView110->AddChild(pImageView100);

	///////////////////////////////   구분   /////////////////////////////////////////

	UIImageView* pImageView18 = new UIImageView;
	pImageView18->SetPosition(-10, -140);
	pImageView18->SetTexture("Maps/Front/Image/revoltrogo.png");

	UIImageView* pImageView19 = new UIImageView;
	pImageView19->SetPosition(400, 250);
	pImageView19->SetIsBoard(true);
	pImageView19->SetXSize(11.5f);
	pImageView19->SetYSize(9.5f);
	pImageView19->SetTexture("Maps/Front/Image/ring.png");

	UITextImageView* pImageView20 = new UITextImageView;
	pImageView20->SetIndex(0);
	pImageView20->SetPosition(50, 25);
	pImageView20->SetText("Start Race");
	pImageView20->SetTexture("Maps/Front/Image/font2.png");

	UITextImageView* pImageView21 = new UITextImageView;
	pImageView21->SetIndex(1);
	pImageView21->SetPosition(50, 50);
	pImageView21->SetText("Championship");
	pImageView21->SetTexture("Maps/Front/Image/font2.png");

	UITextImageView* pImageView22 = new UITextImageView;
	pImageView22->SetIndex(2);
	pImageView22->SetPosition(50, 75);
	pImageView22->SetText("Multi-Player");
	pImageView22->SetTexture("Maps/Front/Image/font2.png");

	UITextImageView* pImageView23 = new UITextImageView;
	pImageView23->SetIndex(3);
	pImageView23->SetPosition(50, 100);
	pImageView23->SetText("Time Trial");
	pImageView23->SetTexture("Maps/Front/Image/font2.png");

	UITextImageView* pImageView24 = new UITextImageView;
	pImageView24->SetIndex(4);
	pImageView24->SetPosition(50, 125);
	pImageView24->SetText("Practice");
	pImageView24->SetTexture("Maps/Front/Image/font2.png");

	UITextImageView* pImageView25 = new UITextImageView;
	pImageView25->SetIndex(5);
	pImageView25->SetPosition(50, 150);
	pImageView25->SetText("Stunt Arena");
	pImageView25->SetTexture("Maps/Front/Image/font2.png");

	pImageView19->AddChild(pImageView20);
	pImageView19->AddChild(pImageView21);
	pImageView19->AddChild(pImageView22);
	pImageView19->AddChild(pImageView23);
	pImageView19->AddChild(pImageView24);
	pImageView19->AddChild(pImageView25);
	pImageView19->AddChild(pImageView18);

	UIImageView* pImageView26 = new UIImageView;
	pImageView26->SetPosition(-10, -140);
	pImageView26->SetTexture("Maps/Front/Image/revoltrogo.png");

	UIImageView* pImageView27 = new UIImageView;
	pImageView27->SetPosition(400, 250);
	pImageView27->SetIsBoard(true);
	pImageView27->SetXSize(11.5f);
	pImageView27->SetYSize(9.5f);
	pImageView27->SetTexture("Maps/Front/Image/ring.png");

	UITextImageView* pImageView28 = new UITextImageView;
	pImageView28->SetIndex(0);
	pImageView28->SetPosition(50, 25);
	pImageView28->SetText("Simulation");
	pImageView28->SetTexture("Maps/Front/Image/font2.png");

	UITextImageView* pImageView29 = new UITextImageView;
	pImageView29->SetIndex(1);
	pImageView29->SetPosition(50, 50);
	pImageView29->SetText("Arcade");
	pImageView29->SetTexture("Maps/Front/Image/font2.png");

	UITextImageView* pImageView30 = new UITextImageView;
	pImageView30->SetIndex(2);
	pImageView30->SetPosition(50, 75);
	pImageView30->SetText("Console");
	pImageView30->SetTexture("Maps/Front/Image/font2.png");

	UITextImageView* pImageView31 = new UITextImageView;
	pImageView31->SetIndex(3);
	pImageView31->SetPosition(50, 100);
	pImageView31->SetText("Junior RC");
	pImageView31->SetTexture("Maps/Front/Image/font2.png");

	pImageView27->AddChild(pImageView28);
	pImageView27->AddChild(pImageView29);
	pImageView27->AddChild(pImageView30);
	pImageView27->AddChild(pImageView31);
	pImageView27->AddChild(pImageView26);

	UIImageView* pImageView32 = new UIImageView;
	pImageView26->SetPosition(-10, -140);
	pImageView26->SetTexture("Maps/Front/Image/revoltrogo.png");

	UIImageView* pImageView33 = new UIImageView;
	pImageView33->SetPosition(300, 180);
	pImageView33->SetIsBoard(true);
	pImageView33->SetXSize(25.0f);
	pImageView33->SetYSize(3.0f);
	pImageView33->SetTexture("Maps/Front/Image/ring.png");

	UITextImageView* pImageView34 = new UITextImageView;
	pImageView34->SetIndex(INT_MAX);
	pImageView34->SetColor(D3DCOLOR_ARGB(255, 242, 150, 97));
	pImageView34->SetPosition(30, 40);
	pImageView34->SetText("Player Name : ");
	pImageView34->SetTexture("Maps/Front/Image/font2.png");

	UIImageView* pImageView35 = new UIImageView;
	pImageView35->SetPosition(-220, -130);
	pImageView35->SetXSize(4.0f);
	pImageView35->SetYSize(4.0f);
	pImageView35->SetIsBoard(true);
	pImageView35->SetTexture("Maps/Front/Image/blueRing.png");

	UIImageView* pImageView36 = new UIImageView;
	pImageView36->SetPosition(120, 25);
	pImageView36->SetIsBoard(true);
	pImageView36->SetXSize(20.0f);
	pImageView36->SetYSize(1.0f);
	pImageView36->SetTexture("Maps/Front/Image/ring.png");

	UITextImageView* pImageView37 = new UITextImageView;
	pImageView37->SetTexture("Maps/Front/Image/font1.png");
	pImageView37->SetText("ENTER NAME");
	pImageView37->SetXSize(1.5f);
	pImageView37->SetYSize(1.5f);
	pImageView37->SetPosition(180, 45);

	UIImageView* pImageView38 = new UIImageView;
	pImageView38->SetXSize(1.2f);
	pImageView38->SetYSize(1.2f);
	pImageView38->SetPosition(17, 17);
	pImageView38->SetTexture("Maps/Front/Image/bluetoy.png");

	UITextImageView* pImageView39 = new UITextImageView;
	pImageView39->SetIndex(INT_MAX);
	pImageView39->SetPosition(160, 40);
	pImageView39->SetIsChatingText(true);
	pImageView39->SetTexture("Maps/Front/Image/font2.png");
	pImageView39->SetColor(D3DCOLOR_ARGB(255, 250, 237, 125));

	pImageView33->AddChild(pImageView32);
	pImageView33->AddChild(pImageView34);
	pImageView33->AddChild(pImageView35);
	pImageView35->AddChild(pImageView36);
	pImageView35->AddChild(pImageView37);
	pImageView35->AddChild(pImageView38);
	pImageView33->AddChild(pImageView39);

	UIImageView* pIV_CP_BodyRing = new UIImageView;
	pIV_CP_BodyRing->SetPosition(300, 180);
	pIV_CP_BodyRing->SetIsBoard(true);
	pIV_CP_BodyRing->SetXSize(25.0f);
	pIV_CP_BodyRing->SetYSize(3.0f);
	pIV_CP_BodyRing->SetTexture("Maps/Front/Image/ring.png");

	UITextImageView* pTIV_CP_BodyFont = new UITextImageView;
	pTIV_CP_BodyFont->SetIndex(INT_MAX);
	pTIV_CP_BodyFont->SetColor(D3DCOLOR_ARGB(255, 242, 150, 97));
	pTIV_CP_BodyFont->SetPosition(30, 40);
	pTIV_CP_BodyFont->SetText("Player Name : ");
	pTIV_CP_BodyFont->SetTexture("Maps/Front/Image/font2.png");

	UITextImageView* pTIV_CP_Chating = new UITextImageView;
	pTIV_CP_Chating->SetIndex(INT_MAX);
	pTIV_CP_Chating->SetPosition(160, 40);
	pTIV_CP_Chating->SetIsChatingText(true);
	pTIV_CP_Chating->SetTexture("Maps/Front/Image/font2.png");
	pTIV_CP_Chating->SetColor(D3DCOLOR_ARGB(255, 250, 237, 125));

	UIImageView* pIV_CP_BlueRing = new UIImageView;
	pIV_CP_BlueRing->SetPosition(-220, -130);
	pIV_CP_BlueRing->SetXSize(4.0f);
	pIV_CP_BlueRing->SetYSize(4.0f);
	pIV_CP_BlueRing->SetIsBoard(true);
	pIV_CP_BlueRing->SetTexture("Maps/Front/Image/blueRing.png");

	UIImageView* pIV_CP_HeadRing = new UIImageView;
	pIV_CP_HeadRing->SetPosition(120, 25);
	pIV_CP_HeadRing->SetIsBoard(true);
	pIV_CP_HeadRing->SetXSize(23.0f);
	pIV_CP_HeadRing->SetYSize(1.0f);
	pIV_CP_HeadRing->SetTexture("Maps/Front/Image/ring.png");

	UITextImageView* pTIV_CP_HeadFont = new UITextImageView;
	pTIV_CP_HeadFont->SetTexture("Maps/Front/Image/font1.png");
	pTIV_CP_HeadFont->SetText("CREATE PROFILE");
	pTIV_CP_HeadFont->SetXSize(1.5f);
	pTIV_CP_HeadFont->SetYSize(1.5f);
	pTIV_CP_HeadFont->SetPosition(150, 45);

	UIImageView* pIV_CP_BlueToy = new UIImageView;
	pIV_CP_BlueToy->SetXSize(1.2f);
	pIV_CP_BlueToy->SetYSize(1.2f);
	pIV_CP_BlueToy->SetPosition(17, 17);
	pIV_CP_BlueToy->SetTexture("Maps/Front/Image/bluetoy.png");

	pIV_CP_BodyRing->AddChild(pTIV_CP_BodyFont);
	pIV_CP_BodyRing->AddChild(pIV_CP_BlueRing);
	pIV_CP_BodyRing->AddChild(pTIV_CP_Chating);
	pIV_CP_BlueRing->AddChild(pIV_CP_HeadRing);
	pIV_CP_BlueRing->AddChild(pTIV_CP_HeadFont);
	pIV_CP_BlueRing->AddChild(pIV_CP_BlueToy);

	///////////////////////////////   구분   /////////////////////////////////////////

	UIImageView* pImageView40 = new UIImageView;
	pImageView40->SetPosition(80, 50);
	pImageView40->SetXSize(4.0f);
	pImageView40->SetYSize(4.0f);
	pImageView40->SetIsBoard(true);
	pImageView40->SetTexture("Maps/Front/Image/blueRing.png");

	UIImageView* pImageView41 = new UIImageView;
	pImageView41->SetXSize(1.2f);
	pImageView41->SetYSize(1.2f);
	pImageView41->SetPosition(17, 17);
	pImageView41->SetTexture("Maps/Front/Image/bluecar.png");

	UIImageView* pImageView42 = new UIImageView;
	pImageView42->SetPosition(120, 25);
	pImageView42->SetIsBoard(true);
	pImageView42->SetXSize(20.0f);
	pImageView42->SetYSize(1.0f);
	pImageView42->SetTexture("Maps/Front/Image/ring.png");

	UITextImageView* pImageView43 = new UITextImageView;
	pImageView43->SetTexture("Maps/Front/Image/font1.png");
	pImageView43->SetText("SELECT CAR");
	pImageView43->SetXSize(1.5f);
	pImageView43->SetYSize(1.5f);
	pImageView43->SetPosition(180, 45);

	UIImageView* pImageView44 = new UIImageView;
	pImageView44->SetPosition(50, 130);
	pImageView44->SetIsBoard(true);
	pImageView44->SetXSize(28.0f);
	pImageView44->SetYSize(16.0f);
	pImageView44->SetTexture("Maps/Front/Image/ring.png");

	UITextImageView* pImageView45 = new UITextImageView;
	pImageView45->SetTexture("Maps/Front/Image/font2.png");
	pImageView45->SetText("Class");
	pImageView45->SetPosition(60, 100);

	UITextImageView* pImageView46 = new UITextImageView;
	pImageView46->SetTexture("Maps/Front/Image/font2.png");
	pImageView46->SetText("Rating");
	pImageView46->SetPosition(60, 125);

	UITextImageView* pImageView47 = new UITextImageView;
	pImageView47->SetTexture("Maps/Front/Image/font2.png");
	pImageView47->SetText("Speed");
	pImageView47->SetPosition(60, 150);

	UITextImageView* pImageView48 = new UITextImageView;
	pImageView48->SetTexture("Maps/Front/Image/font2.png");
	pImageView48->SetText("Acc");
	pImageView48->SetPosition(60, 175);

	UITextImageView* pImageView49 = new UITextImageView;
	pImageView49->SetTexture("Maps/Front/Image/font2.png");
	pImageView49->SetText("Weight");
	pImageView49->SetPosition(60, 200);

	UITextImageView* pImageView50 = new UITextImageView;
	pImageView50->SetTexture("Maps/Front/Image/font2.png");
	pImageView50->SetText("Trans");
	pImageView50->SetPosition(60, 225);

	pImageView40->AddChild(pImageView41);
	pImageView40->AddChild(pImageView42);
	pImageView40->AddChild(pImageView43);
	pImageView40->AddChild(pImageView44);
	pImageView44->AddChild(pImageView45);
	pImageView44->AddChild(pImageView46);
	pImageView44->AddChild(pImageView47);
	pImageView44->AddChild(pImageView48);
	pImageView44->AddChild(pImageView49);
	pImageView44->AddChild(pImageView50);

	///////////////////////////////   구분   /////////////////////////////////////////
	/*   로비 UI 추가하기   */

	m_mapLobby[INTRO1] = new ST_Object;
	m_mapLobby[INTRO1]->m_time = 100.0f;
	m_mapLobby[INTRO1]->m_pObject = pImageView1;
	m_mapLobby[INTRO1]->m_pNextLob = new LOBBY[1];
	m_mapLobby[INTRO1]->m_pNextLob[0] = INTRO2;

	m_mapLobby[INTRO2] = new ST_Object;
	m_mapLobby[INTRO2]->m_time = 100.0f;
	m_mapLobby[INTRO2]->m_pObject = pImageView2;
	m_mapLobby[INTRO2]->m_pNextLob = new LOBBY[1];
	m_mapLobby[INTRO2]->m_pNextLob[0] = INTRO3;

	m_mapLobby[INTRO3] = new ST_Object;
	m_mapLobby[INTRO3]->m_time = 100.0f;
	m_mapLobby[INTRO3]->m_pObject = pImageView3;
	m_mapLobby[INTRO3]->m_pNextLob = new LOBBY[1];
	m_mapLobby[INTRO3]->m_pNextLob[0] = START_LOBBY;

	m_mapLobby[START_LOBBY] = new ST_Object;
	m_mapLobby[START_LOBBY]->m_target = D3DXVECTOR3(-1, 2, -55);
	m_mapLobby[START_LOBBY]->m_count = m_vProfileList.size();
	m_mapLobby[START_LOBBY]->m_selectCnt = 3;
	m_mapLobby[START_LOBBY]->m_pNextLob = new LOBBY[3];
	m_mapLobby[START_LOBBY]->m_prevLob = LOBBY_NONE;
	m_mapLobby[START_LOBBY]->m_time = 50.0f;
	m_mapLobby[START_LOBBY]->m_pNextLob[0] = MAIN_LOBBY;
	m_mapLobby[START_LOBBY]->m_pNextLob[1] = CREATE_PROFILE_LOBBY2;
	m_mapLobby[START_LOBBY]->m_pNextLob[2] = START_LOBBY;
	m_mapLobby[START_LOBBY]->m_pObject = m_pfileList->GetProfileList();
	m_mapLobby[START_LOBBY]->m_prevLob = START_LOBBY;

	m_mapLobby[MAIN_LOBBY] = new ST_Object;
	m_mapLobby[MAIN_LOBBY]->m_target = D3DXVECTOR3(-1, 2, -20);
	m_mapLobby[MAIN_LOBBY]->m_count = 6;
	m_mapLobby[MAIN_LOBBY]->m_time = 50.0f;
	m_mapLobby[MAIN_LOBBY]->m_pObject = pImageView110;
	m_mapLobby[MAIN_LOBBY]->m_pNextLob = new LOBBY[6];
	m_mapLobby[MAIN_LOBBY]->m_prevLob = MAIN_LOBBY;
	m_mapLobby[MAIN_LOBBY]->m_pNextLob[0] = MAIN_LOBBY2;
	m_mapLobby[MAIN_LOBBY]->m_pNextLob[1] = LOBBY_NONE;
	m_mapLobby[MAIN_LOBBY]->m_pNextLob[2] = LOBBY_NONE;
	m_mapLobby[MAIN_LOBBY]->m_pNextLob[3] = LOBBY_NONE;
	m_mapLobby[MAIN_LOBBY]->m_pNextLob[4] = START_LOBBY;
	m_mapLobby[MAIN_LOBBY]->m_pNextLob[5] = LOBBY_NONE;

	m_mapLobby[MAIN_LOBBY2] = new ST_Object;
	m_mapLobby[MAIN_LOBBY2]->m_target = D3DXVECTOR3(1, 10, -1);
	m_mapLobby[MAIN_LOBBY2]->m_count = 6;
	m_mapLobby[MAIN_LOBBY2]->m_pNextLob = new LOBBY[1];
	m_mapLobby[MAIN_LOBBY2]->m_time = 50.0f;
	m_mapLobby[MAIN_LOBBY2]->m_pObject = pImageView19;
	m_mapLobby[MAIN_LOBBY2]->m_pNextLob[0] = MAIN_LOBBY3;
	m_mapLobby[MAIN_LOBBY2]->m_prevLob = MAIN_LOBBY;

	m_mapLobby[MAIN_LOBBY3] = new ST_Object;
	m_mapLobby[MAIN_LOBBY3]->m_target = D3DXVECTOR3(1, 10, -1);
	m_mapLobby[MAIN_LOBBY3]->m_count = 4;
	m_mapLobby[MAIN_LOBBY3]->m_pNextLob = new LOBBY[1];
	m_mapLobby[MAIN_LOBBY3]->m_time = 50.0f;
	m_mapLobby[MAIN_LOBBY3]->m_pObject = pImageView27;
	m_mapLobby[MAIN_LOBBY3]->m_pNextLob[0] = CREATE_PROFILE_LOBBY;
	m_mapLobby[MAIN_LOBBY3]->m_prevLob = MAIN_LOBBY2;

	m_mapLobby[CREATE_PROFILE_LOBBY] = new ST_Object;
	m_mapLobby[CREATE_PROFILE_LOBBY]->m_target = D3DXVECTOR3(4, 8, 12);
	m_mapLobby[CREATE_PROFILE_LOBBY]->m_count = 1;
	m_mapLobby[CREATE_PROFILE_LOBBY]->m_pNextLob = new LOBBY[1];
	m_mapLobby[CREATE_PROFILE_LOBBY]->m_time = 50.0f;
	m_mapLobby[CREATE_PROFILE_LOBBY]->m_pObject = pImageView33;
	m_mapLobby[CREATE_PROFILE_LOBBY]->m_camLookAt = D3DXVECTOR3(14, 4, 22);
	m_mapLobby[CREATE_PROFILE_LOBBY]->m_pNextLob[0] = SELECT_CAR_LOBBY;
	m_mapLobby[CREATE_PROFILE_LOBBY]->m_prevLob = MAIN_LOBBY3;

	m_mapLobby[SELECT_CAR_LOBBY] = new ST_Object;
	m_mapLobby[SELECT_CAR_LOBBY]->m_target = D3DXVECTOR3(10, 14, 8);
	m_mapLobby[SELECT_CAR_LOBBY]->m_camLookAt = D3DXVECTOR3(20, -2, 16);
	m_mapLobby[SELECT_CAR_LOBBY]->m_pObject = pImageView40;
	m_mapLobby[SELECT_CAR_LOBBY]->m_count = 1;
	m_mapLobby[SELECT_CAR_LOBBY]->m_selectCnt = 6;
	m_mapLobby[SELECT_CAR_LOBBY]->m_pNextLob = new LOBBY[1];
	m_mapLobby[SELECT_CAR_LOBBY]->m_time = 50.0f;
	m_mapLobby[SELECT_CAR_LOBBY]->m_prevLob = CREATE_PROFILE_LOBBY;

	m_mapLobby[CREATE_PROFILE_LOBBY2] = new ST_Object;
	m_mapLobby[CREATE_PROFILE_LOBBY2]->m_target = D3DXVECTOR3(4, 8, 12);
	m_mapLobby[CREATE_PROFILE_LOBBY2]->m_count = 1;
	m_mapLobby[CREATE_PROFILE_LOBBY2]->m_pNextLob = new LOBBY[1];
	m_mapLobby[CREATE_PROFILE_LOBBY2]->m_time = 50.0f;
	m_mapLobby[CREATE_PROFILE_LOBBY2]->m_pObject = pIV_CP_BodyRing;
	m_mapLobby[CREATE_PROFILE_LOBBY2]->m_camLookAt = D3DXVECTOR3(14, 4, 22);
	m_mapLobby[CREATE_PROFILE_LOBBY2]->m_pNextLob[0] = START_LOBBY;
	m_mapLobby[CREATE_PROFILE_LOBBY2]->m_prevLob = START_LOBBY;
}

void Lobby::CreateProfile()
{
	if (m_isEnterName)
	{
		m_isEnterName = false;
		m_stateLobby = START_LOBBY;
		m_pfileList->ListLoad();
		m_vProfileList = m_pfileList->GetUpdateList();
		m_mapLobby[START_LOBBY]->m_count = m_vProfileList.size();
		m_mapLobby[START_LOBBY]->m_pObject = m_pfileList->GetProfileList();
		m_pCamera->Setup(&m_mapLobby[m_stateLobby]->m_target);
		m_pCamera->SetLookAt(&m_mapLobby[m_stateLobby]->m_camLookAt);

	}
}
