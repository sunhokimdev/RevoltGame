#include "stdafx.h"
#include "Lobby.h"

/*   UI헤더파일 선언   */
#include "UIObject.h"
#include "UIImageView.h"
#include "UITextImageView.h"

#include "ObjectLoader.h"
#include "MtlTex.h"
#include "Camera.h"
#include "SelectMap.h"
//#include "InGameUI.h"

/*      */
#include "Map.h"
#include "Thing.h"
#include "CarBox.h"
#include "WheelTire.h"
#include "cTrack.h"

/*   로비 창 구현   */
#include "ProfileList.h"
#include "UserFileLoader.h"
#include "cSelectCarLob.h"
#include "cCreateProfile.h"
#include "cViewCarLob.h"
#include "cImpact.h"

/*   멀티 플레이어 작업   */
#include "cNetworkLobby.h"
#include "cNetworkInRoom.h"

Lobby::Lobby()
	: m_pSprite(NULL)
	, m_pObjMesh(NULL)
	, m_stateLobby(INTRO1)
	, m_time(0.0f)
	, m_select(0)
	, m_leftAndrightSelect(0)
	, m_stateMapType(NONE)
	, m_pfileList(NULL)
{
}

Lobby::~Lobby()
{
	//SAFE_RELEASE(m_pSprite);
	//SAFE_RELEASE(m_pObjMesh);
	//SAFE_DELETE(m_pSelectMap);
	//SAFE_DELETE(m_multiLobby);
	//SAFE_DELETE(m_pCreateProfileLobby);
	//SAFE_DELETE(m_pSelectCarLobbby);
	//
	//for each(auto a in m_mapLobby)
	//{
	//	delete[] a.second->m_pNextLob;
	//	SAFE_DELETE(a.second->m_pObject);
	//}
}

void Lobby::Setup()
{
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

	UITextImageView::m_Select = &m_select;
	UITextImageView::m_LeftAndRightSelect = &m_leftAndrightSelect;
	Thing::g_LobbyState = &m_stateLobby;
	CarBox::g_select = &m_leftAndrightSelect;
	Map::g_LobbyState = &m_stateLobby;
	iLobby::m_gLobbyState = &m_stateLobby;

	m_pSelectMap = new SelectMap;
	m_pSelectMap->Setup();

	m_multiLobby = new cNetworkLobby;
	m_multiLobby->Setup();

	m_pCreateProfileLobby = new cCreateProfile;
	m_pCreateProfileLobby->Setup();

	m_pSelectCarLobbby = new cSelectCarLob;
	m_pSelectCarLobbby->Setup();

	m_pViewCarLobby = new cViewCarLob;
	m_pViewCarLobby->Setup();

	m_pInRoom = new cNetworkInRoom;
	m_pInRoom->Setup();

	m_pfileList = new ProfileList;
	m_pMap = new Map;

	SetUpUI();

	m_CamLerpSpd = 0.05f;
	m_vCamPos = { 1,2,-55 };
	m_vLookAt = { 0,0,0 };
}

void Lobby::Update()
{
	std::string str;

	// Set Map Type Update
	if (m_stateLobby == SELECT_MAP_LOBBY)
	{
		m_pSelectMap->Update();
		m_pSelectMap->SetMapType(&m_stateMapType, m_leftAndrightSelect);
	}

	else if (m_stateLobby == NETWORK_IN_LOBBY)
	{
		/*    서버에서 recv가 무한대기에 빠지지 않도록 메시지를 계속해서 보낸다    */
	
		bool isNext = true;

		g_pNetworkManager->SendMsg("#");

		if (g_pNetworkManager->RecvMsg())
		{
			m_pInRoom->SetText(g_pNetworkManager->GetMsg().c_str());
		}
		else
		{
			int index = 0;

			for (int i = 0; i < USER_SIZE; i++)
			{
				if (g_pNetworkManager->GetIsClientUse(i))
				{
					if (g_pNetworkManager->GetClientReady(i))
						m_pInRoom->SetUserText(g_pNetworkManager->GetClientList(i), index, D3DCOLOR_ARGB(255, 255, 0, 0));
					else
					{
						m_pInRoom->SetUserText(g_pNetworkManager->GetClientList(i), index, D3DCOLOR_ARGB(255, 255, 255, 255));
						isNext = false;
					}

					index++;
				}
			}
			
			// 만약 다음스테이지로 넘어가기 위한 단계라면
			if (isNext)
			{
				if (m_stateLobby == NETWORK_IN_LOBBY)
					m_stateLobby = SELECT_MAP_LOBBY;
			}
		}
	}

	if (g_pNetworkManager->GetIsInGameNetwork())
	{
		g_SceneManager->ChangeScene("Race");
		return;
	}

	TimeUpdate();   // 시간 갱신 메서드
	KeyUpdate();   // 키 이벤트 갱신 메서드

	if (m_mapLobby[m_stateLobby]->m_pObject)
	{
		m_mapLobby[m_stateLobby]->m_pObject->Update();
	}

	KeyUpdate();   // 키 이벤트 갱신 메서드
		
}

void Lobby::Render()
{
	if (m_mapLobby[m_stateLobby]->m_pObject)
		m_mapLobby[m_stateLobby]->m_pObject->Render(m_pSprite);

	if(m_stateLobby > INTRO3)
		m_pSelectMap->Render(m_pSprite);
}

void Lobby::Destroy()
{
	

	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_pObjMesh);

	if(m_pSelectMap)
	{
		m_pSelectMap->Destroy();
		SAFE_DELETE(m_pSelectMap);
	}
	
	if (m_multiLobby)
	{
		//m_multiLobby->Destroy();
		//2(3(0(),0(),0()),2(2(4(0(),0(),0(),0(여기서 터짐)
		SAFE_DELETE(m_multiLobby);
	}

	if (m_pCreateProfileLobby)
	{
		//m_pCreateProfileLobby->Destroy();
		SAFE_DELETE(m_pCreateProfileLobby);
	}

	if (m_pSelectCarLobbby)
	{
		//m_pSelectCarLobbby->Destroy();
		SAFE_DELETE(m_pSelectCarLobbby);
	}
	
	if (m_pViewCarLobby)
	{
		//m_pViewCarLobby->Destroy();
		SAFE_DELETE(m_pViewCarLobby);
	}
	
	if (m_pInRoom)
	{
		//m_pInRoom->Destroy();
		SAFE_DELETE(m_pInRoom);
	}
	
	if (m_pfileList)
	{
		//m_pfileList->Destroy();
		SAFE_DELETE(m_pfileList);
	}

	//if (m_pMap)
	//{
	//	//m_pMap->Destroy();
	//	SAFE_DELETE(m_pMap);
	//}

	//for each(auto a in m_mapLobby)
	//{
	//	delete[] a.second->m_pNextLob;
	//	SAFE_DELETE(a.second->m_pObject);
	//}
	//m_mapLobby.clear();

}

void Lobby::KeyUpdate()
{
	std::string str;

	if (g_pKeyManager->isOnceKeyDown(VK_DOWN))
	{
		m_select++;

		if (m_stateLobby == START_LOBBY)
		{
	
		}
		else
		{
			if (m_mapLobby[m_stateLobby]->m_count <= m_select)
				m_select = 0;
		}
		g_pSoundManager->Play("menuUpDown.wav", 0.8f);
	}

	if (g_pKeyManager->isOnceKeyDown(VK_UP))
	{
		m_select--;

		if (m_stateLobby == START_LOBBY)
		{
	
		}
		else
		{
			if (m_select < 0)
				m_select = m_mapLobby[m_stateLobby]->m_count - 1;
		}
		g_pSoundManager->Play("menuUpDown.wav", 0.8f);
	}

	if (g_pKeyManager->isOnceKeyDown(VK_RIGHT))
	{
		if (m_stateLobby == START_LOBBY ||
			m_stateLobby == SELECT_CAR_LOBBY)
		{
			m_leftAndrightSelect++;

			if (m_mapLobby[m_stateLobby]->m_selectCnt <= m_leftAndrightSelect)
				m_leftAndrightSelect = 0;

			g_pSoundManager->Play("boxslide.wav", 0.8f);
		}
		else if (m_stateLobby == CREATE_PROFILE_LOBBY)
		{
			WheelTire::g_xRotAngle += D3DX_PI / 15.0f;
			g_pSoundManager->Play("menuLeftRight.wav", 0.8f);
		}
		else if (m_stateLobby == SELECT_MAP_LOBBY)
		{
			m_leftAndrightSelect++;

			//m_pSelectMap->GetmagImage()->SetIsMove(true);
			m_pSelectMap->SetMove(true);

			if (m_mapLobby[m_stateLobby]->m_selectCnt <= m_leftAndrightSelect)
				m_leftAndrightSelect = 0;

			g_pSoundManager->Play("tvstatic.wav", 0.8f);
		}

	}

	if (g_pKeyManager->isOnceKeyDown(VK_LEFT))
	{
		if (m_stateLobby == START_LOBBY ||
			m_stateLobby == SELECT_CAR_LOBBY)
		{
			m_leftAndrightSelect--;

			if (m_leftAndrightSelect < 0)
				m_leftAndrightSelect = m_mapLobby[m_stateLobby]->m_selectCnt - 1;

			g_pSoundManager->Play("boxslide.wav", 0.8f);
		}
		else if (m_stateLobby == CREATE_PROFILE_LOBBY)
		{
			WheelTire::g_xRotAngle -= D3DX_PI / 15.0f;
			g_pSoundManager->Play("menuLeftRight.wav", 0.8f);
		}

		else if (m_stateLobby == SELECT_MAP_LOBBY)
		{
			m_leftAndrightSelect--;

			//m_pSelectMap->GetmagImage()->SetIsMove(true);
			m_pSelectMap->SetMove(true);

			if (m_leftAndrightSelect < 0)
				m_leftAndrightSelect = m_mapLobby[m_stateLobby]->m_selectCnt - 1;

			g_pSoundManager->Play("tvstatic.wav", 0.8f);
		}
	}

	/*   엔터 키 눌렀을 때 다음 로비로 들어가는 이벤트   */
	if (g_pKeyManager->isOnceKeyDown(VK_RETURN))
	{
		if (m_stateLobby == SELECT_MAP_LOBBY)
		{
			if (g_pNetworkManager->GetIsNetwork())
			{
				g_pNetworkManager->SendMsg("@Start!");
				g_pNetworkManager->SetIsInGameNetwork(true);
				g_pNetworkManager->SetIsNextStage(true);
			}

			std::map<int, cTrack*> trackName = m_pMap->GetMapName();
			int index = m_leftAndrightSelect + 1;
			if (index > m_mapLobby[m_stateLobby]->m_selectCnt)
				index = 1;
			else if (index < 0)
				index = m_mapLobby[m_stateLobby]->m_selectCnt;

			m_pfileList->SetMapName(trackName[index]->trackName);

			m_time = 0.0f;
			m_select = 0;
			m_leftAndrightSelect = 0;

			//유저데이터에 자동차 선택한거 넘겨주고
			//씬변경

			g_pDataManager->mapName = m_pfileList->GetMapName();

			g_pDataManager->vecPlayerData.push_back(new cPlayerData("", "", m_pfileList->GetCarName(), false));
			g_pDataManager->vecPlayerData.push_back(new cPlayerData("", "", "tc1", true));
			//g_pDataManager->vecPlayerData.push_back(new cPlayerData("", "", "tc2", true));
			//g_pDataManager->vecPlayerData.push_back(new cPlayerData("", "", "tc3", true));
			//g_pDataManager->vecPlayerData.push_back(new cPlayerData("", "", "tc4", true));
			//g_pDataManager->vecPlayerData.push_back(new cPlayerData("", "", "tc5", true));
		
			g_SceneManager->ChangeScene("Race");

			return;
		}
		else if (m_stateLobby == SELECT_CAR_LOBBY)
		{
			if (g_pNetworkManager->GetIsNetwork())
			{
				g_pNetworkManager->SetCarName(m_pSelectCarLobbby->GetCarName());
			}
			switch (m_leftAndrightSelect)
			{
			case 0:	m_pfileList->SetCarName("tc1"); break;
			case 1: m_pfileList->SetCarName("tc2"); break;
			case 2: m_pfileList->SetCarName("tc3"); break;
			case 3: m_pfileList->SetCarName("tc4"); break;
			case 4: m_pfileList->SetCarName("tc5"); break;
			case 5: m_pfileList->SetCarName("tc6"); break;
			}
		}
		else if (m_stateLobby == MAIN_LOBBY2)
		{
			if (m_select == 2)
			{
				g_pNetworkManager->SetIsNetwork(true);
			}
			else
			{
				if (g_pNetworkManager->GetIsNetwork())
				{
					g_pNetworkManager->Release();			// 소켓 해제
				}
				g_pNetworkManager->SetIsNetwork(false);
			}
		}

		else if (m_stateLobby == VIEW_CAR_LOBBY)
		{
			if (g_pNetworkManager->GetIsNetwork())
			{
				m_mapLobby[m_stateLobby]->m_pNextLob[m_select] = NETWORK_LOBBY;
			}
		}

		else if (m_stateLobby == NETWORK_IN_LOBBY)
		{
			g_pNetworkManager->SendMsg(m_pInRoom->GetMsg().c_str());
			m_pInRoom->SetResetCharText();

			return;
		}

		else if (m_stateLobby == CREATE_PROFILE_LOBBY)
		{
			// 프로필 파일생성 없이 사용한 메서드
			if (g_pNetworkManager->GetIsNetwork())
			{
				g_pNetworkManager->SetClientName(m_pCreateProfileLobby->GetName());
			}
		}

		else if (m_stateLobby == NETWORK_LOBBY)
		{
			g_pNetworkManager->SetServerIP(m_multiLobby->GetServerIP());
			g_pNetworkManager->Start();
			//g_pNetworkManager->SendMsg(g_pNetworkManager->GetClientIP().c_str());
		}

		m_stateLobby = m_mapLobby[m_stateLobby]->m_pNextLob[m_select];

		if (m_stateLobby > INTRO3)
		{
			//g_pSoundManager->Play("menuNext.wav", 1.0f);
			g_pSoundManager->Play("menuPrev.wav", 0.6f);
			
			m_time = 0.0f;
			m_select = 0;

			if (m_stateLobby != VIEW_CAR_LOBBY)
				m_leftAndrightSelect = 0;
		}
	}
	/*   ESC 키 눌렀을 때 이전 로비로 들어가는 이벤트   */
	if (g_pKeyManager->isOnceKeyDown(VK_ESCAPE))
	{
		if (m_mapLobby[m_stateLobby]->m_prevLob != LOBBY_NONE)
		{
			if (m_stateLobby == NETWORK_IN_LOBBY)
			{
				g_pNetworkManager->SetIsUse(false);
				g_pNetworkManager->Release();
				m_pInRoom->SetResetData();
			}
			else if (m_stateLobby == SELECT_MAP_LOBBY)
			{
				if (g_pNetworkManager->GetIsNetwork())
				{
					m_stateLobby = NETWORK_IN_LOBBY;
					m_time = 0.0f;
					m_select = 0;
					m_leftAndrightSelect = 0;

					return;
				}
			}

			m_stateLobby = m_mapLobby[m_stateLobby]->m_prevLob;

			m_time = 0.0f;
			m_select = 0;
			m_leftAndrightSelect = 0;
			g_pSoundManager->Play("menuPrev.wav", 0.8f);
		}
	}
	if (g_pKeyManager->isOnceKeyDown(VK_F5))
	{
		if (m_stateLobby == NETWORK_IN_LOBBY)
		{
			g_pNetworkManager->SetUserReady();
			g_pNetworkManager->SendClientData();

		}
	}

	D3DXVec3Lerp(&m_vCamPos, &m_vCamPos, &m_mapLobby[m_stateLobby]->m_target, m_CamLerpSpd);
	D3DXVec3Lerp(&m_vLookAt, &m_vLookAt, &m_mapLobby[m_stateLobby]->m_camLookAt, m_CamLerpSpd);

	g_pCamManager->SetCamPos(&m_vCamPos);
	//g_pCamManager->SetLookAt(&m_mapLobby[m_stateLobby]->m_camLookAt);
	g_pCamManager->SetLookAt(&m_vLookAt);
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
			g_pCamManager->Setup(&m_mapLobby[m_stateLobby]->m_target);
			g_pCamManager->SetLookAt(&m_mapLobby[m_stateLobby]->m_camLookAt);
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

	/*   Start Lobby   */

	UIImageView* pImageView4 = new UIImageView;
	pImageView4->SetPosition(40, 40);
	pImageView4->SetXSize(4.0f);
	pImageView4->SetYSize(4.0f);
	pImageView4->SetIsBoard(true);
	pImageView4->SetTexture("UIImage/blueRing.png");

	UIImageView* pImageView5 = new UIImageView;
	pImageView5->SetPosition(120, 20);
	pImageView5->SetXSize(24.0f);
	pImageView5->SetYSize(1.2f);
	pImageView5->SetIsBoard(true);
	pImageView5->SetTexture("UIImage/ring.png");

	UITextImageView* pImageView6 = new UITextImageView;
	pImageView6->SetIndex(INT_MAX);
	pImageView6->SetPosition(150, 40);
	pImageView6->SetXSize(1.5f);
	pImageView6->SetYSize(1.5f);
	pImageView6->SetText("SELECT PROFILE");
	pImageView6->SetTexture("UIImage/font1.png");

	UIImageView* pImageView7 = new UIImageView;
	pImageView7->SetPosition(18, 18);
	pImageView7->SetXSize(1.2f);
	pImageView7->SetYSize(1.2f);
	pImageView7->SetTexture("UIImage/blueflag.png");

	UIImageView* pImageView8 = new UIImageView;
	pImageView8->SetPosition(350, 180);
	pImageView8->SetXSize(15.0f);
	pImageView8->SetYSize(1.2f);
	pImageView8->SetIsBoard(true);
	pImageView8->SetTexture("UIImage/ring.png");

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
	pImageView9->SetTexture("UIImage/font2.png");

	UIImageView* pImageView10 = new UIImageView;
	pImageView10->SetPosition(220, 22);
	pImageView10->SetXSize(1.5f);
	pImageView10->SetYSize(1.5f);
	pImageView10->SetTexture("UIImage/arrowright.png");

	UIImageView* pImageView11 = new UIImageView;
	pImageView11->SetPosition(30, 22);
	pImageView11->SetXSize(1.5f);
	pImageView11->SetYSize(1.5f);
	pImageView11->SetTexture("UIImage/arrowleft.png");

	UIImageView* pImageView12 = new UIImageView;
	pImageView12->SetPosition(50, 100);
	pImageView12->SetIsBoard(true);
	pImageView12->SetXSize(8.0f);
	pImageView12->SetYSize(12.0f);
	pImageView12->SetTexture("UIImage/ring.png");

	UIImageView* pImageView13 = new UIImageView;
	pImageView13->SetPosition(70, 10);
	pImageView13->SetXSize(1.5f);
	pImageView13->SetYSize(1.5f);
	pImageView13->SetTexture("UIImage/arrowup.png");

	UIImageView* pImageView14 = new UIImageView;
	pImageView14->SetPosition(70, 190);
	pImageView14->SetXSize(1.5f);
	pImageView14->SetYSize(1.5f);
	pImageView14->SetTexture("UIImage/arrowdown.png");

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

	/*   Main Lobby 1  */

	///////////////////////////////   구분   /////////////////////////////////////////

	UIImageView* pImageView100 = new UIImageView;
	pImageView100->SetPosition(-10, -140);
	pImageView100->SetTexture("UIImage/revoltrogo.png");

	UIImageView* pImageView110 = new UIImageView;
	pImageView110->SetPosition(400, 250);
	pImageView110->SetIsBoard(true);
	pImageView110->SetXSize(11.5f);
	pImageView110->SetYSize(9.5f);
	pImageView110->SetTexture("UIImage/ring.png");

	UITextImageView* pImageView120 = new UITextImageView;
	pImageView120->SetIndex(0);
	pImageView120->SetPosition(50, 25);
	pImageView120->SetText("Start Game");
	pImageView120->SetTexture("UIImage/font2.png");

	UITextImageView* pImageView130 = new UITextImageView;
	pImageView130->SetIndex(1);
	pImageView130->SetPosition(50, 50);
	pImageView130->SetText("Best Trial Times");
	pImageView130->SetTexture("UIImage/font2.png");

	UITextImageView* pImageView140 = new UITextImageView;
	pImageView140->SetIndex(2);
	pImageView140->SetPosition(50, 75);
	pImageView140->SetText("Progress Table");
	pImageView140->SetTexture("UIImage/font2.png");

	UITextImageView* pImageView150 = new UITextImageView;
	pImageView150->SetIndex(3);
	pImageView150->SetPosition(50, 100);
	pImageView150->SetText("Options");
	pImageView150->SetTexture("UIImage/font2.png");

	UITextImageView* pImageView160 = new UITextImageView;
	pImageView160->SetIndex(4);
	pImageView160->SetPosition(50, 125);
	pImageView160->SetText("Select Profile");
	pImageView160->SetTexture("UIImage/font2.png");

	UITextImageView* pImageView170 = new UITextImageView;
	pImageView170->SetIndex(5);
	pImageView170->SetPosition(50, 150);
	pImageView170->SetText("Quit");
	pImageView170->SetTexture("UIImage/font2.png");

	pImageView110->AddChild(pImageView120);
	pImageView110->AddChild(pImageView130);
	pImageView110->AddChild(pImageView140);
	pImageView110->AddChild(pImageView150);
	pImageView110->AddChild(pImageView160);
	pImageView110->AddChild(pImageView170);
	pImageView110->AddChild(pImageView100);

	/*   Main Lobby 2  */

	///////////////////////////////   구분   /////////////////////////////////////////

	UIImageView* pImageView18 = new UIImageView;
	pImageView18->SetPosition(-10, -140);
	pImageView18->SetTexture("UIImage/revoltrogo.png");

	UIImageView* pImageView19 = new UIImageView;
	pImageView19->SetPosition(400, 250);
	pImageView19->SetIsBoard(true);
	pImageView19->SetXSize(11.5f);
	pImageView19->SetYSize(9.5f);
	pImageView19->SetTexture("UIImage/ring.png");

	UITextImageView* pImageView20 = new UITextImageView;
	pImageView20->SetIndex(0);
	pImageView20->SetPosition(50, 25);
	pImageView20->SetText("Start Race");
	pImageView20->SetTexture("UIImage/font2.png");

	UITextImageView* pImageView21 = new UITextImageView;
	pImageView21->SetIndex(1);
	pImageView21->SetPosition(50, 50);
	pImageView21->SetText("Championship");
	pImageView21->SetTexture("UIImage/font2.png");

	UITextImageView* pImageView22 = new UITextImageView;
	pImageView22->SetIndex(2);
	pImageView22->SetPosition(50, 75);
	pImageView22->SetText("Multi-Player");
	pImageView22->SetTexture("UIImage/font2.png");

	UITextImageView* pImageView23 = new UITextImageView;
	pImageView23->SetIndex(3);
	pImageView23->SetPosition(50, 100);
	pImageView23->SetText("Time Trial");
	pImageView23->SetTexture("UIImage/font2.png");

	UITextImageView* pImageView24 = new UITextImageView;
	pImageView24->SetIndex(4);
	pImageView24->SetPosition(50, 125);
	pImageView24->SetText("Practice");
	pImageView24->SetTexture("UIImage/font2.png");

	UITextImageView* pImageView25 = new UITextImageView;
	pImageView25->SetIndex(5);
	pImageView25->SetPosition(50, 150);
	pImageView25->SetText("Stunt Arena");
	pImageView25->SetTexture("UIImage/font2.png");

	pImageView19->AddChild(pImageView20);
	pImageView19->AddChild(pImageView21);
	pImageView19->AddChild(pImageView22);
	pImageView19->AddChild(pImageView23);
	pImageView19->AddChild(pImageView24);
	pImageView19->AddChild(pImageView25);
	pImageView19->AddChild(pImageView18);

	/*   Main Lobby 3  */

	UIImageView* pImageView26 = new UIImageView;
	pImageView26->SetPosition(-10, -140);
	pImageView26->SetTexture("UIImage/revoltrogo.png");

	UIImageView* pImageView27 = new UIImageView;
	pImageView27->SetPosition(400, 250);
	pImageView27->SetIsBoard(true);
	pImageView27->SetXSize(11.5f);
	pImageView27->SetYSize(9.5f);
	pImageView27->SetTexture("UIImage/ring.png");

	UITextImageView* pImageView28 = new UITextImageView;
	pImageView28->SetIndex(0);
	pImageView28->SetPosition(50, 25);
	pImageView28->SetText("Simulation");
	pImageView28->SetTexture("UIImage/font2.png");

	UITextImageView* pImageView29 = new UITextImageView;
	pImageView29->SetIndex(1);
	pImageView29->SetPosition(50, 50);
	pImageView29->SetText("Arcade");
	pImageView29->SetTexture("UIImage/font2.png");

	UITextImageView* pImageView30 = new UITextImageView;
	pImageView30->SetIndex(2);
	pImageView30->SetPosition(50, 75);
	pImageView30->SetText("Console");
	pImageView30->SetTexture("UIImage/font2.png");

	UITextImageView* pImageView31 = new UITextImageView;
	pImageView31->SetIndex(3);
	pImageView31->SetPosition(50, 100);
	pImageView31->SetText("Junior RC");
	pImageView31->SetTexture("UIImage/font2.png");

	pImageView27->AddChild(pImageView28);
	pImageView27->AddChild(pImageView29);
	pImageView27->AddChild(pImageView30);
	pImageView27->AddChild(pImageView31);
	pImageView27->AddChild(pImageView26);

	/*  Select Map Lobby  */

	//=========================================== Add Lobby Ui ===========================================//

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
	m_mapLobby[INTRO3]->m_target = D3DXVECTOR3(-1, 2, -55);

	m_mapLobby[START_LOBBY] = new ST_Object;
	m_mapLobby[START_LOBBY]->m_target = D3DXVECTOR3(-1, 2, -55);
	m_mapLobby[START_LOBBY]->m_count = 1;
	m_mapLobby[START_LOBBY]->m_selectCnt = 3;
	m_mapLobby[START_LOBBY]->m_pNextLob = new LOBBY[3];
	m_mapLobby[START_LOBBY]->m_prevLob = LOBBY_NONE;
	m_mapLobby[START_LOBBY]->m_time = 50.0f;
	m_mapLobby[START_LOBBY]->m_pNextLob[0] = MAIN_LOBBY;
	m_mapLobby[START_LOBBY]->m_pNextLob[1] = CREATE_PROFILE_LOBBY;
	m_mapLobby[START_LOBBY]->m_pNextLob[2] = START_LOBBY;
	m_mapLobby[START_LOBBY]->m_pObject = pImageView4;
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
	m_mapLobby[MAIN_LOBBY]->m_pNextLob[5] = GAME_QUIT;

	m_mapLobby[MAIN_LOBBY2] = new ST_Object;
	m_mapLobby[MAIN_LOBBY2]->m_target = D3DXVECTOR3(1, 10, -2);
	m_mapLobby[MAIN_LOBBY2]->m_count = 6;
	m_mapLobby[MAIN_LOBBY2]->m_pNextLob = new LOBBY[6];
	m_mapLobby[MAIN_LOBBY2]->m_time = 50.0f;
	m_mapLobby[MAIN_LOBBY2]->m_pObject = pImageView19;
	m_mapLobby[MAIN_LOBBY2]->m_pNextLob[0] = MAIN_LOBBY3;
	m_mapLobby[MAIN_LOBBY2]->m_pNextLob[1] = MAIN_LOBBY3;
	m_mapLobby[MAIN_LOBBY2]->m_pNextLob[2] = CREATE_PROFILE_LOBBY;
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
	m_mapLobby[CREATE_PROFILE_LOBBY]->m_pObject = m_pCreateProfileLobby->GetUIRoot();
	m_mapLobby[CREATE_PROFILE_LOBBY]->m_camLookAt = D3DXVECTOR3(14, 4, 22);
	m_mapLobby[CREATE_PROFILE_LOBBY]->m_pNextLob[0] = SELECT_CAR_LOBBY;
	m_mapLobby[CREATE_PROFILE_LOBBY]->m_prevLob = MAIN_LOBBY3;

	m_mapLobby[NETWORK_LOBBY] = new ST_Object;
	m_mapLobby[NETWORK_LOBBY]->m_target = D3DXVECTOR3(4, 8, -5);
	m_mapLobby[NETWORK_LOBBY]->m_count = 1;
	m_mapLobby[NETWORK_LOBBY]->m_pNextLob = new LOBBY[1];
	m_mapLobby[NETWORK_LOBBY]->m_time = 50.0f;
	m_mapLobby[NETWORK_LOBBY]->m_pObject = m_multiLobby->GetUIRoot();
	m_mapLobby[NETWORK_LOBBY]->m_camLookAt = D3DXVECTOR3(14, 4, 8);
	m_mapLobby[NETWORK_LOBBY]->m_pNextLob[0] = NETWORK_IN_LOBBY;
	m_mapLobby[NETWORK_LOBBY]->m_prevLob = VIEW_CAR_LOBBY;

	m_mapLobby[NETWORK_IN_LOBBY] = new ST_Object;
	m_mapLobby[NETWORK_IN_LOBBY]->m_target = D3DXVECTOR3(4, 8, -5);
	m_mapLobby[NETWORK_IN_LOBBY]->m_count = 1;
	m_mapLobby[NETWORK_IN_LOBBY]->m_pNextLob = new LOBBY[1];
	m_mapLobby[NETWORK_IN_LOBBY]->m_time = 500.0f;
	m_mapLobby[NETWORK_IN_LOBBY]->m_pObject = m_pInRoom->GetUIRoot();
	m_mapLobby[NETWORK_IN_LOBBY]->m_camLookAt = D3DXVECTOR3(14, 4, 8);
	m_mapLobby[NETWORK_IN_LOBBY]->m_pNextLob[0] = IN_GAME_MAP;
	m_mapLobby[NETWORK_IN_LOBBY]->m_prevLob = NETWORK_LOBBY;

	m_mapLobby[SELECT_CAR_LOBBY] = new ST_Object;
	m_mapLobby[SELECT_CAR_LOBBY]->m_target = D3DXVECTOR3(10, 14, 8);
	m_mapLobby[SELECT_CAR_LOBBY]->m_camLookAt = D3DXVECTOR3(20, -2, 16);
	m_mapLobby[SELECT_CAR_LOBBY]->m_pObject = m_pSelectCarLobbby->GetUIRoot();
	m_mapLobby[SELECT_CAR_LOBBY]->m_count = 1;
	m_mapLobby[SELECT_CAR_LOBBY]->m_selectCnt = 6;
	m_mapLobby[SELECT_CAR_LOBBY]->m_pNextLob = new LOBBY[1];
	m_mapLobby[SELECT_CAR_LOBBY]->m_pNextLob[0] = VIEW_CAR_LOBBY;
	m_mapLobby[SELECT_CAR_LOBBY]->m_time = 50.0f;
	m_mapLobby[SELECT_CAR_LOBBY]->m_prevLob = CREATE_PROFILE_LOBBY;

	m_mapLobby[SELECT_MAP_LOBBY] = new ST_Object;
	m_mapLobby[SELECT_MAP_LOBBY]->m_target = D3DXVECTOR3(12, 3, -18);
	m_mapLobby[SELECT_MAP_LOBBY]->m_count = 1;
	m_mapLobby[SELECT_MAP_LOBBY]->m_selectCnt = 4;
	m_mapLobby[SELECT_MAP_LOBBY]->m_pNextLob = new LOBBY[2];
	m_mapLobby[SELECT_MAP_LOBBY]->m_time = 5000.0f;
	m_mapLobby[SELECT_MAP_LOBBY]->m_pObject = m_pSelectMap->GetmapParent();
	m_mapLobby[SELECT_MAP_LOBBY]->m_camLookAt = D3DXVECTOR3(23, 5, -12);
	m_mapLobby[SELECT_MAP_LOBBY]->m_prevLob = VIEW_CAR_LOBBY;
	m_mapLobby[SELECT_MAP_LOBBY]->m_pNextLob[0] = MARKET_MAP;
	m_mapLobby[SELECT_MAP_LOBBY]->m_pNextLob[1] = GARDEN_MAP;

	m_mapLobby[VIEW_CAR_LOBBY] = new ST_Object;
	m_mapLobby[VIEW_CAR_LOBBY]->m_target = D3DXVECTOR3(10, 4, 8);
	m_mapLobby[VIEW_CAR_LOBBY]->m_camLookAt = D3DXVECTOR3(20, -3, 10);
	m_mapLobby[VIEW_CAR_LOBBY]->m_pObject = m_pViewCarLobby->GetUIRoot();
	m_mapLobby[VIEW_CAR_LOBBY]->m_count = 1;
	m_mapLobby[VIEW_CAR_LOBBY]->m_pNextLob = new LOBBY[1];
	m_mapLobby[VIEW_CAR_LOBBY]->m_prevLob = SELECT_CAR_LOBBY;
	m_mapLobby[VIEW_CAR_LOBBY]->m_pNextLob[0] = SELECT_MAP_LOBBY;

	m_mapLobby[IN_GAME_MAP] = new ST_Object;
	m_mapLobby[IN_GAME_MAP]->m_target = D3DXVECTOR3(0, 0, -15);
	m_mapLobby[IN_GAME_MAP]->m_camLookAt = D3DXVECTOR3(0, 0, 0);
	m_mapLobby[IN_GAME_MAP]->m_prevLob = SELECT_MAP_LOBBY;
	m_mapLobby[IN_GAME_MAP]->m_pObject = NULL;
}
