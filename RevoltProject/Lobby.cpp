#include "stdafx.h"
#include "Lobby.h"

/*   UI헤더파일 선언   */
#include "UIObject.h"
#include "UIImageView.h"
#include "UITextImageView.h"

#include "ObjectLoader.h"
#include "MtlTex.h"
#include "Camera.h"

#include "TextLoader.h"

Lobby::Lobby()
	: m_pSprite(NULL)
	, m_pObjMesh(NULL)
	, m_stateLobby(INTRO1)
	, m_time(0.0f)
	, m_select(0)
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

	SetUpUI();

	ObjectLoader loader;
	m_pObjMesh = loader.LoadMesh(
		m_vecObjMtlTex,
		"Maps/Front", "Front.obj");
}

void Lobby::Update()
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

	KeyEvent();

		m_mapLobby[m_stateLobby]->m_pObject->Update();
}

void Lobby::Render()
{
	if (m_stateLobby > INTRO3)
	{
		g_pD3DDevice->SetTexture(0, NULL);
		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

		D3DXMATRIXA16	matWorld, matS, matR;

		D3DXMatrixIdentity(&matWorld);

		g_pD3DDevice->SetTransform(D3DTS_WORLD,
			&matWorld);

		for (size_t i = 0; i < m_vecObjMtlTex.size(); ++i)
		{
			g_pD3DDevice->SetMaterial(
				&m_vecObjMtlTex[i]->GetMaterial());

			if (m_vecObjMtlTex[i]->GetTexture() != NULL)
			{
				g_pD3DDevice->SetTexture(
					0,
					m_vecObjMtlTex[i]->GetTexture());
			}
			m_pObjMesh->DrawSubset(i);
		}
	}
	if (m_mapLobby[m_stateLobby]->m_pObject)
		m_mapLobby[m_stateLobby]->m_pObject->Render(m_pSprite);
}

void Lobby::KeyEvent()
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

	/*   엔터 키 눌렀을 때 다음 로비로 들어가는 이벤트   */
	if (g_pKeyManager->isOnceKeyDown(VK_RETURN))
	{
		m_stateLobby = m_mapLobby[m_stateLobby]->m_pNextLob[m_select];
		m_pCamera->Setup(&m_mapLobby[m_stateLobby]->m_target);		// 카메라 변경
		m_pCamera->SetLookAt(m_mapLobby[m_stateLobby]->m_lookAt);
		m_time = 0.0f;

		if(m_stateLobby > INTRO3)
			g_pSoundManager->Play("menuNext.wav", 1.0f);
	}

	/*   ESC 키 눌렀을 때 이전 로비로 들어가는 이벤트   */
	if (g_pKeyManager->isOnceKeyDown(VK_ESCAPE))
	{
		m_stateLobby = m_mapLobby[m_stateLobby]->m_prevLob;
		m_pCamera->Setup(&m_mapLobby[m_stateLobby]->m_target);
		g_pSoundManager->Play("menuNext.wav", 1.0f);
	}

	if (g_pKeyManager->isStayKeyDown(VK_CONTROL))
	{
		m_stateLobby = START_LOBBY;
		m_pCamera->Setup(&m_mapLobby[m_stateLobby]->m_target);
	} 
}

void Lobby::SetUpUI()
{
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
	pImageView7->SetPosition(25, 25);
	pImageView7->SetXSize(15.0f);
	pImageView7->SetYSize(1.2f);
	pImageView7->SetTexture("Maps/Front/Image/blueflag.png");

	UIImageView* pImageView8 = new UIImageView;
	pImageView8->SetPosition(350, 250);
	pImageView8->SetXSize(15.0f);
	pImageView8->SetYSize(1.2f);
	pImageView8->SetIsBoard(true);
	pImageView8->SetTexture("Maps/Front/Image/ring.png");

	UITextImageView* pImageView9 = new UITextImageView;
	pImageView9->SetPosition(415, 270);
	pImageView9->SetIndex(INT_MAX);
	pImageView9->SetText("Load Profile");
	pImageView9->SetXSize(1.5f);
	pImageView9->SetYSize(1.5f);
	pImageView9->SetColor(D3DCOLOR_ARGB(255, 242, 150, 97));
	pImageView9->SetTexture("Maps/Front/Image/font2.png");

	pImageView4->AddChild(pImageView5);
	pImageView4->AddChild(pImageView6);
	pImageView4->AddChild(pImageView7);
	pImageView4->AddChild(pImageView8);
	pImageView4->AddChild(pImageView9);
	
///////////////////////////////   구분   /////////////////////////////////////////

	UIImageView* pImageView10 = new UIImageView;
	pImageView10->SetPosition(-10,-140);
	pImageView10->SetTexture("Maps/Front/Image/revoltrogo.png");

	UIImageView* pImageView11 = new UIImageView;
	pImageView11->SetPosition(400, 250);
	pImageView11->SetIsBoard(true);
	pImageView11->SetXSize(11.5f);
	pImageView11->SetYSize(9.5f);
	pImageView11->SetTexture("Maps/Front/Image/ring.png");

	UITextImageView* pImageView12 = new UITextImageView;
	pImageView12->SetIndex(0);
	pImageView12->SetPosition(50, 25);
	pImageView12->SetText("Start Game");
	pImageView12->SetTexture("Maps/Front/Image/font2.png");

	UITextImageView* pImageView13 = new UITextImageView;
	pImageView13->SetIndex(1);
	pImageView13->SetPosition(50, 50);
	pImageView13->SetText("Best Trial Times");
	pImageView13->SetTexture("Maps/Front/Image/font2.png");

	UITextImageView* pImageView14 = new UITextImageView;
	pImageView14->SetIndex(2);
	pImageView14->SetPosition(50, 75);
	pImageView14->SetText("Progress Table");
	pImageView14->SetTexture("Maps/Front/Image/font2.png");

	UITextImageView* pImageView15 = new UITextImageView;
	pImageView15->SetIndex(3);
	pImageView15->SetPosition(50, 100);
	pImageView15->SetText("Options");
	pImageView15->SetTexture("Maps/Front/Image/font2.png");

	UITextImageView* pImageView16 = new UITextImageView;
	pImageView16->SetIndex(4);
	pImageView16->SetPosition(50, 125);
	pImageView16->SetText("Select Profile");
	pImageView16->SetTexture("Maps/Front/Image/font2.png");

	UITextImageView* pImageView17 = new UITextImageView;
	pImageView17->SetIndex(5);
	pImageView17->SetPosition(50, 150);
	pImageView17->SetText("Quit");
	pImageView17->SetTexture("Maps/Front/Image/font2.png");

	pImageView11->AddChild(pImageView12);
	pImageView11->AddChild(pImageView13);
	pImageView11->AddChild(pImageView14);
	pImageView11->AddChild(pImageView15);
	pImageView11->AddChild(pImageView16);
	pImageView11->AddChild(pImageView17);
	pImageView11->AddChild(pImageView10);

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
	m_mapLobby[START_LOBBY]->m_target = D3DXVECTOR3(-1, 2, -17);
	m_mapLobby[START_LOBBY]->m_lookAt = D3DXVECTOR3(0, 0, 0);
	m_mapLobby[START_LOBBY]->m_count = 4;
	m_mapLobby[START_LOBBY]->m_time = 50.0f;
	m_mapLobby[START_LOBBY]->m_pObject = pImageView4;
	m_mapLobby[START_LOBBY]->m_pNextLob = new LOBBY[1];
	m_mapLobby[START_LOBBY]->m_pNextLob[0] = MAIN_LOBBY;

	m_mapLobby[MAIN_LOBBY] = new ST_Object;
	m_mapLobby[MAIN_LOBBY]->m_target = D3DXVECTOR3(1, 8, -1);
	m_mapLobby[MAIN_LOBBY]->m_lookAt = D3DXVECTOR3(0, 0, 0);
	m_mapLobby[MAIN_LOBBY]->m_count = 6;
	m_mapLobby[MAIN_LOBBY]->m_time = 50.0f;
	m_mapLobby[MAIN_LOBBY]->m_pObject = pImageView11;
	m_mapLobby[MAIN_LOBBY]->m_prevLob = START_LOBBY;
	m_mapLobby[MAIN_LOBBY]->m_pNextLob = new LOBBY[6];
	m_mapLobby[MAIN_LOBBY]->m_pNextLob[0] = MAIN_LOBBY2;

	m_mapLobby[MAIN_LOBBY2] = new ST_Object;
	m_mapLobby[MAIN_LOBBY2]->m_target = D3DXVECTOR3(8, 5, 10);
	m_mapLobby[MAIN_LOBBY2]->m_lookAt = D3DXVECTOR3(15, 5, 20);
	m_mapLobby[MAIN_LOBBY2]->m_count = 6;
	m_mapLobby[MAIN_LOBBY2]->m_time = 50.0f;
	m_mapLobby[MAIN_LOBBY2]->m_pObject = pImageView11;
	m_mapLobby[MAIN_LOBBY2]->m_prevLob = MAIN_LOBBY;
	//m_mapLobby[MAIN_LOBBY2]->m_pNextLob = new LOBBY[1];


}
