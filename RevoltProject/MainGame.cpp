#include "stdafx.h"
#include "MainGame.h"
#include "Grid.h"

#include "LobbyScene.h"
#include "RacingScene.h"

#include "cCar.h"

//======================================
// - written by 김선호
// - MainGame -> 게임시작
//======================================

MainGame::MainGame()
	:m_pGrid(NULL)
{
}

MainGame::~MainGame()
{

}

void MainGame::Setup()
{
	//PhysX 초가화
	g_pPhysX->InitNxPhysX();


	//======================================
	// - written by 김선호
	// - MainGame -> 초기화 작업
	//======================================

	//======================================
	// - written by 이태섭
	// - MainGame -> 
	// 기존의 메인게임에서 불러오던 Lobby와 Map을 LobbyScene으로 통합
	// SceneManager에서 통합 씬처리
	// Camera 클래스 매니저로 등록
	//======================================

	//m_pGrid = new Grid;
	//m_pGrid->Setup();

	g_SceneManager->AddScene("Lobby", new LobbyScene);
	g_SceneManager->AddScene("Race", new RacingScene);
	g_SceneManager->ChangeScene("Race");

	g_pCamManager->Setup(NULL);
	g_pItemManager->Init();
	g_pTimeManager->Setup();
	//
	//	SetAddSound();
	//	MgrPhysXScene->setUserTriggerReport(new TriggerCallback());
	IsUpdate = false;

	g_pTextManager->AddFont(L"굴림체", "굴림체_7", 7);
}

void MainGame::Update()
{
	if (IsUpdate == true) return;
	IsUpdate = true;
	SAFE_UPDATE(g_pTimeManager);

	SAFE_UPDATE(g_SceneManager);
	SAFE_UPDATE(g_pLightManager);
	SAFE_UPDATE(g_pItemManager);

	//PhysX 시뮬 런
	//g_pTimeManager->GetElapsedTime());//
//	MgrPhysXScene->simulate((1.f/60.f));	//프레임 지정

	MgrPhysXScene->simulate((float)(1.f/60.f));	//프레임 지정
	MgrPhysXScene->flushStream();
	MgrPhysXScene->fetchResults(NX_RIGID_BODY_FINISHED, true);
	//	MgrPhysXScene->checkResults(NX_RIGID_BODY_FINISHED, true);


		//PhysX와 정보 동기화
	if (g_SceneManager) g_SceneManager->LastUpdate();
	SAFE_UPDATE(g_pCamManager);
}

void MainGame::Render()
{
	if (IsUpdate == false) return;
	IsUpdate = false;

	SAFE_RENDER(g_pTimeManager);

	g_pD3DDevice->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(47, 121, 112), 1.0F, 0);
		// 그리기 시작
	g_pD3DDevice->BeginScene();

	SAFE_RENDER(g_SceneManager);

	g_pItemManager->Render();

	g_pPhysX->Render();

	// 타임 매니저 랜더 해야함

	g_pTimeManager->Render();

	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void MainGame::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

}

void MainGame::SetAddSound()
{
	g_pSoundManager->LoadSound("Sound", "menuUpDown.wav", false);
	g_pSoundManager->LoadSound("Sound", "menuNext.wav", false);
	g_pSoundManager->LoadSound("Sound", "menuPrev.wav", false);
	g_pSoundManager->LoadSound("Sound", "menuLeftRight.wav", false);
	g_pSoundManager->LoadSound("Sound", "boxslide.wav", false);
	g_pSoundManager->LoadSound("Sound", "honkgood.wav", false);
}