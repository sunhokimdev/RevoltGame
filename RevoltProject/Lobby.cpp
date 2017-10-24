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
#include "CarBox.h"
#include "WheelTire.h"

Lobby::Lobby()
	: m_pSprite(NULL)
	, m_pObjMesh(NULL)
	, m_stateLobby(INTRO1)
	, m_time(0.0f)
	, m_select(0)
	, m_leftAndrightSelect(0)
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
	Thing::g_LobbyState = &m_stateLobby;
	CarBox::g_select = &m_leftAndrightSelect;

	SetUpUI();
}

void Lobby::Update()
{

	TimeUpdate();	// 시간 갱신 메서드
	KeyUpdate();	// 키 이벤트 갱신 메서드

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

		if (m_mapLobby[m_stateLobby]->m_count <= m_select)
			m_select = 0;
		g_pSoundManager->Play("menuUpDown.wav", 1.0f);
	}
	
	if (g_pKeyManager->isOnceKeyDown(VK_UP))
	{
		m_select--;

		if (m_select < 0)
			m_select = m_mapLobby[m_stateLobby]->m_count - 1;
	
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
		else if (m_stateLobby == CREATE_PROFILE_LOBBY)
		{
			WheelTire::g_xRotAngle += D3DX_PI / 15.0f;
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
		else if (m_stateLobby == CREATE_PROFILE_LOBBY)
		{
			WheelTire::g_xRotAngle -= D3DX_PI / 15.0f;
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
		if (m_stateLobby == START_LOBBY)
		{
			m_stateLobby = m_mapLobby[m_stateLobby]->m_pNextLob[m_leftAndrightSelect];
			m_pCamera->Setup(&m_mapLobby[m_stateLobby]->m_target);		// 카메라 변경
			m_time = 0.0f;
			m_select = 0;
			m_leftAndrightSelect = 0;

			if (m_stateLobby > INTRO3)
				g_pSoundManager->Play("menuNext.wav", 1.0f);
		}

		else if (m_stateLobby == SELECT_CAR_LOBBY)
		{
			m_stateLobby = m_mapLobby[m_stateLobby]->m_pNextLob[0];
			m_pCamera->Setup(&m_mapLobby[m_stateLobby]->m_target);		// 카메라 변경
			m_time = 0.0f;

			if (m_stateLobby > INTRO3)
				g_pSoundManager->Play("menuNext.wav", 1.0f);
		}

		else if (m_mapLobby[m_stateLobby]->m_pNextLob[m_select] != LOBBY_NONE)
		{
			m_stateLobby = m_mapLobby[m_stateLobby]->m_pNextLob[m_select];
			m_pCamera->Setup(&m_mapLobby[m_stateLobby]->m_target);		// 카메라 변경
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
		m_stateLobby = m_mapLobby[m_stateLobby]->m_prevLob;
		m_pCamera->Setup(&m_mapLobby[m_stateLobby]->m_target);
		m_pCamera->SetLookAt(&m_mapLobby[m_stateLobby]->m_camLookAt);
		g_pSoundManager->Play("menuPrev.wav", 1.0f);
	}

	if (g_pKeyManager->isStayKeyDown(VK_CONTROL))
	{
		m_stateLobby = START_LOBBY;
		m_pCamera->Setup(&m_mapLobby[m_stateLobby]->m_target);
	}	m_pCamera->SetLookAt(&m_mapLobby[m_stateLobby]->m_camLookAt);
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

	UIImageView* pImageView4 = new UIImageView;
	pImageView4->SetPosition(40, 40);
	pImageView4->SetXSize(4.0f);
	pImageView4->SetYSize(4.0f);
	pImageView4->SetIsBoard(true);
	pImageView4->SetTexture("Maps/Front/Image/blueRing.png");

	UIImageView* pImageView5 = new UIImageView;
	pImageView5->SetPosition(120, 20);
	pImageView5->SetXSize(24.0f);
	pImageView5->SetYSize(1.2f);
	pImageView5->SetIsBoard(true);
	pImageView5->SetTexture("Maps/Front/Image/ring.png");

	UITextImageView* pImageView6 = new UITextImageView;
	pImageView6->SetIndex(INT_MAX);
	pImageView6->SetPosition(150, 40);
	pImageView6->SetXSize(1.5f);
	pImageView6->SetYSize(1.5f);
	pImageView6->SetText("SELECT PROFILE");
	pImageView6->SetTexture("Maps/Front/Image/font1.png");

	UIImageView* pImageView7 = new UIImageView;
	pImageView7->SetPosition(18, 18);
	pImageView7->SetXSize(1.2f);
	pImageView7->SetYSize(1.2f);
	pImageView7->SetTexture("Maps/Front/Image/blueflag.png");

	UIImageView* pImageView8 = new UIImageView;
	pImageView8->SetPosition(350, 180);
	pImageView8->SetXSize(15.0f);
	pImageView8->SetYSize(1.2f);
	pImageView8->SetIsBoard(true);
	pImageView8->SetTexture("Maps/Front/Image/ring.png");

	UITextImageView* pImageView9 = new UITextImageView;
	pImageView9->SetPosition(90, 25);
	pImageView9->SetIndex(INT_MAX);
	pImageView9->SetIsVectorText(true);
	pImageView9->SetAddText("Load Profile");
	pImageView9->SetAddText("Create Profile");
	pImageView9->SetAddText("Delete Profile");
	pImageView9->SetXSize(1.0f);
	pImageView9->SetYSize(1.0f);
	pImageView9->SetColor(D3DCOLOR_ARGB(255, 242, 150, 97));
	pImageView9->SetTexture("Maps/Front/Image/font2.png");

	UIImageView* pImageView10 = new UIImageView;
	pImageView10->SetPosition(220, 22);
	pImageView10->SetXSize(1.5f);
	pImageView10->SetYSize(1.5f);
	pImageView10->SetTexture("Maps/Front/Image/arrowright.png");

	UIImageView* pImageView11 = new UIImageView;
	pImageView11->SetPosition(30, 22);
	pImageView11->SetXSize(1.5f);
	pImageView11->SetYSize(1.5f);
	pImageView11->SetTexture("Maps/Front/Image/arrowleft.png");

	UIImageView* pImageView12 = new UIImageView;
	pImageView12->SetPosition(50, 100);
	pImageView12->SetIsBoard(true);
	pImageView12->SetXSize(8.0f);
	pImageView12->SetYSize(12.0f);
	pImageView12->SetTexture("Maps/Front/Image/ring.png");

	UIImageView* pImageView13 = new UIImageView;
	pImageView13->SetPosition(70, 10);
	pImageView13->SetXSize(1.5f);
	pImageView13->SetYSize(1.5f);
	pImageView13->SetTexture("Maps/Front/Image/arrowup.png");

	UIImageView* pImageView14 = new UIImageView;
	pImageView14->SetPosition(70, 190);
	pImageView14->SetXSize(1.5f);
	pImageView14->SetYSize(1.5f);
	pImageView14->SetTexture("Maps/Front/Image/arrowdown.png");

	pImageView4->AddChild(pImageView5);
	pImageView4->AddChild(pImageView6);
	pImageView4->AddChild(pImageView7);
	pImageView4->AddChild(pImageView8);
	pImageView8->AddChild(pImageView9);
	pImageView8->AddChild(pImageView10);
	pImageView8->AddChild(pImageView11);
	pImageView8->AddChild(pImageView12);
	pImageView12->AddChild(pImageView13);
	pImageView12->AddChild(pImageView14);

///////////////////////////////   구분   /////////////////////////////////////////

	UIImageView* pImageView100 = new UIImageView;
	pImageView100->SetPosition(-10,-140);
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

	UITextImageView* pImageView51 = new UITextImageView;
	pImageView51->SetTexture("Maps/Front/Image/font2.png");
	pImageView51->SetCarIndex(1);
	pImageView51->SetIsRealTime(true);
	pImageView51->SetPosition(200, 100);
	pImageView51->SetColor(D3DCOLOR_ARGB(255, 250, 237, 125));

	UITextImageView* pImageView52 = new UITextImageView;
	pImageView52->SetTexture("Maps/Front/Image/font2.png");
	pImageView52->SetCarIndex(2);
	pImageView52->SetIsRealTime(true);
	pImageView52->SetPosition(200, 125);
	pImageView52->SetColor(D3DCOLOR_ARGB(255, 250, 237, 125));

	UITextImageView* pImageView53 = new UITextImageView;
	pImageView53->SetTexture("Maps/Front/Image/font2.png");
	pImageView53->SetCarIndex(3);
	pImageView53->SetIsRealTime(true);
	pImageView53->SetPosition(200, 150);
	pImageView53->SetColor(D3DCOLOR_ARGB(255, 250, 237, 125));

	UITextImageView* pImageView54 = new UITextImageView;
	pImageView54->SetTexture("Maps/Front/Image/font2.png");
	pImageView54->SetCarIndex(4);
	pImageView54->SetIsRealTime(true);
	pImageView54->SetPosition(200, 175);
	pImageView54->SetColor(D3DCOLOR_ARGB(255, 250, 237, 125));

	UITextImageView* pImageView55 = new UITextImageView;
	pImageView55->SetTexture("Maps/Front/Image/font2.png");
	pImageView55->SetCarIndex(5);
	pImageView55->SetIsRealTime(true);
	pImageView55->SetPosition(200, 200);
	pImageView55->SetColor(D3DCOLOR_ARGB(255, 250, 237, 125));

	UITextImageView* pImageView56 = new UITextImageView;
	pImageView56->SetTexture("Maps/Front/Image/font2.png");
	pImageView56->SetCarIndex(6);
	pImageView56->SetIsRealTime(true);
	pImageView56->SetPosition(200, 225);
	pImageView56->SetColor(D3DCOLOR_ARGB(255, 250, 237, 125));


	UITextImageView* pImageView57 = new UITextImageView;
	pImageView57->SetTexture("Maps/Front/Image/font2.png");
	pImageView57->SetCarIndex(0);
	pImageView57->SetIsRealTime(true);
	pImageView57->SetPosition(50, 50);
	pImageView57->SetColor(D3DCOLOR_ARGB(255, 250, 237, 125));

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
	pImageView44->AddChild(pImageView51);
	pImageView44->AddChild(pImageView52);
	pImageView44->AddChild(pImageView53);
	pImageView44->AddChild(pImageView54);
	pImageView44->AddChild(pImageView55);
	pImageView44->AddChild(pImageView56);
	pImageView44->AddChild(pImageView57);

	UIImageView* pImageView58 = new UIImageView;
	pImageView58->SetPosition(80, 50);
	pImageView58->SetXSize(4.0f);
	pImageView58->SetYSize(4.0f);
	pImageView58->SetIsBoard(true);
	pImageView58->SetTexture("Maps/Front/Image/blueRing.png");

	UIImageView* pImageView59 = new UIImageView;
	pImageView59->SetXSize(1.2f);
	pImageView59->SetYSize(1.2f);
	pImageView59->SetPosition(17, 17);
	pImageView59->SetTexture("Maps/Front/Image/bluecar.png");

	UIImageView* pImageView60 = new UIImageView;
	pImageView60->SetPosition(120, 25);
	pImageView60->SetIsBoard(true);
	pImageView60->SetXSize(20.0f);
	pImageView60->SetYSize(1.0f);
	pImageView60->SetTexture("Maps/Front/Image/ring.png");

	UITextImageView* pImageView61 = new UITextImageView;
	pImageView61->SetTexture("Maps/Front/Image/font1.png");
	pImageView61->SetText("SELECT CAR");
	pImageView61->SetXSize(1.5f);
	pImageView61->SetYSize(1.5f);
	pImageView61->SetPosition(180, 45);

	pImageView58->AddChild(pImageView59);
	pImageView58->AddChild(pImageView60);
	pImageView58->AddChild(pImageView61);

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
	m_mapLobby[START_LOBBY]->m_count = 1;
	m_mapLobby[START_LOBBY]->m_selectCnt = 3;
	m_mapLobby[START_LOBBY]->m_pNextLob = new LOBBY[3];
	m_mapLobby[START_LOBBY]->m_prevLob = LOBBY_NONE;
	m_mapLobby[START_LOBBY]->m_time = 50.0f;
	m_mapLobby[START_LOBBY]->m_pNextLob[0] = MAIN_LOBBY;
	m_mapLobby[START_LOBBY]->m_pNextLob[1] = MAIN_LOBBY;
	m_mapLobby[START_LOBBY]->m_pNextLob[2] = MAIN_LOBBY;
	m_mapLobby[START_LOBBY]->m_pObject = pImageView4;
	m_mapLobby[START_LOBBY]->m_prevLob = START_LOBBY;

	m_mapLobby[MAIN_LOBBY] = new ST_Object;
	m_mapLobby[MAIN_LOBBY]->m_target = D3DXVECTOR3(-1, 2, -20);
	m_mapLobby[MAIN_LOBBY]->m_count = 6;
	m_mapLobby[MAIN_LOBBY]->m_time = 50.0f;
	m_mapLobby[MAIN_LOBBY]->m_pObject = pImageView110;
	m_mapLobby[MAIN_LOBBY]->m_pNextLob = new LOBBY[6];
	m_mapLobby[MAIN_LOBBY]->m_prevLob = START_LOBBY;
	m_mapLobby[MAIN_LOBBY]->m_pNextLob[0] = MAIN_LOBBY2;
	m_mapLobby[MAIN_LOBBY]->m_pNextLob[1] = LOBBY_NONE;
	m_mapLobby[MAIN_LOBBY]->m_pNextLob[2] = LOBBY_NONE;
	m_mapLobby[MAIN_LOBBY]->m_pNextLob[3] = LOBBY_NONE;
	m_mapLobby[MAIN_LOBBY]->m_pNextLob[4] = START_LOBBY;
	m_mapLobby[MAIN_LOBBY]->m_pNextLob[5] = LOBBY_NONE;

	m_mapLobby[MAIN_LOBBY2] = new ST_Object;
	m_mapLobby[MAIN_LOBBY2]->m_target = D3DXVECTOR3(-1, 10, -2);
	m_mapLobby[MAIN_LOBBY2]->m_count = 6;
	m_mapLobby[MAIN_LOBBY2]->m_pNextLob = new LOBBY[1];
	m_mapLobby[MAIN_LOBBY2]->m_time = 50.0f;
	m_mapLobby[MAIN_LOBBY2]->m_pObject = pImageView19;
	m_mapLobby[MAIN_LOBBY2]->m_pNextLob[0] = MAIN_LOBBY3;
	m_mapLobby[MAIN_LOBBY2]->m_prevLob = MAIN_LOBBY;

	m_mapLobby[MAIN_LOBBY3] = new ST_Object;
	m_mapLobby[MAIN_LOBBY3]->m_target = D3DXVECTOR3(-1, 10, -2);
	m_mapLobby[MAIN_LOBBY3]->m_count = 4;
	m_mapLobby[MAIN_LOBBY3]->m_pNextLob = new LOBBY[1];
	m_mapLobby[MAIN_LOBBY3]->m_time = 50.0f;
	m_mapLobby[MAIN_LOBBY3]->m_pObject = pImageView27;
	m_mapLobby[MAIN_LOBBY3]->m_pNextLob[0] = CREATE_PROFILE_LOBBY;
	m_mapLobby[MAIN_LOBBY3]->m_prevLob = MAIN_LOBBY2;

	m_mapLobby[CREATE_PROFILE_LOBBY] = new ST_Object;
	m_mapLobby[CREATE_PROFILE_LOBBY]->m_target = D3DXVECTOR3(6, 12, 14);
	m_mapLobby[CREATE_PROFILE_LOBBY]->m_count = 1;
	m_mapLobby[CREATE_PROFILE_LOBBY]->m_pNextLob = new LOBBY[1];
	m_mapLobby[CREATE_PROFILE_LOBBY]->m_time = 50.0f;
	m_mapLobby[CREATE_PROFILE_LOBBY]->m_pObject = pImageView33;
	m_mapLobby[CREATE_PROFILE_LOBBY]->m_camLookAt = D3DXVECTOR3(14, -4, 22);
	m_mapLobby[CREATE_PROFILE_LOBBY]->m_pNextLob[0] = SELECT_CAR_LOBBY;
	m_mapLobby[CREATE_PROFILE_LOBBY]->m_prevLob = MAIN_LOBBY3;

	m_mapLobby[SELECT_CAR_LOBBY] = new ST_Object;
	m_mapLobby[SELECT_CAR_LOBBY]->m_target = D3DXVECTOR3(10, 14, 8);
	m_mapLobby[SELECT_CAR_LOBBY]->m_camLookAt = D3DXVECTOR3(20, -2, 16);
	m_mapLobby[SELECT_CAR_LOBBY]->m_pObject = pImageView40;
	m_mapLobby[SELECT_CAR_LOBBY]->m_count = 1;
	m_mapLobby[SELECT_CAR_LOBBY]->m_selectCnt = 6;
	m_mapLobby[SELECT_CAR_LOBBY]->m_pNextLob = new LOBBY[1];
	m_mapLobby[SELECT_CAR_LOBBY]->m_pNextLob[0] = VIEW_CAR_LOBBY;
	m_mapLobby[SELECT_CAR_LOBBY]->m_time = 50.0f;
	m_mapLobby[SELECT_CAR_LOBBY]->m_prevLob = MAIN_LOBBY3;

	m_mapLobby[VIEW_CAR_LOBBY] = new ST_Object;
	m_mapLobby[VIEW_CAR_LOBBY]->m_target = D3DXVECTOR3(10, 4, 8);
	m_mapLobby[VIEW_CAR_LOBBY]->m_camLookAt = D3DXVECTOR3(20, -3, 10);
	m_mapLobby[VIEW_CAR_LOBBY]->m_pObject = pImageView58;
	m_mapLobby[VIEW_CAR_LOBBY]->m_count = 1;
	m_mapLobby[VIEW_CAR_LOBBY]->m_prevLob = SELECT_CAR_LOBBY;
}

