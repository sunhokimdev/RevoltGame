#include "stdafx.h"
#include "MainGame.h"

#include "Camera.h"
#include "Grid.h"

#include "Lobby.h"
#include "Map.h"

//======================================
// - written by 김선호
// - MainGame -> 게임시작
//======================================




MainGame::MainGame()
	: m_pCamera(NULL)
	, m_pGrid(NULL)
{
}

MainGame::~MainGame()
{
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pGrid);
	SAFE_DELETE(m_pLobby);
	SAFE_DELETE(m_pMap);
}

void MainGame::Setup()
{
	//PhysX 초가화
	g_pPhysX->InitNxPhysX();

	//======================================
	// - written by 김선호
	// - MainGame -> 초기화 작업
	//======================================

	/*   카메라 클래스 초기화   */
	m_pCamera = new Camera;
	m_pCamera->Setup(NULL);

	/*   그리드 초기화   */
	m_pGrid = new Grid;
 	m_pGrid->Setup();

	/*   로비 클래스 초기화   */
	m_pLobby = new Lobby;
	m_pLobby->Setup();
	m_pLobby->SetUpCamera(m_pCamera);

	m_pMap = new Map;
	m_pMap->Setup();
	m_pMap->SetUpCamera(m_pCamera);
	/*   사운드 초기화 작업   */
	SetAddSound();

}

void MainGame::Update()
{
	if(m_pCamera)	m_pCamera->Update();
	if(m_pMap)		m_pMap->Update();
	if(m_pLobby)	m_pLobby->Update();
}

void MainGame::Render()
{
	g_pD3DDevice->Clear(NULL, NULL,	D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,	D3DCOLOR_XRGB(47, 121, 112),1.0F, 0);
	g_pD3DDevice->BeginScene();
	// 그리기 시작
	m_pGrid->Render();
	m_pMap->Render();
	m_pLobby->Render();
	// 그리기 종료

	//PhysX 디버깅 렌더
	//MgrD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pPhysX->Render();
	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);


	//PhysX 시뮬 런
	MgrPhysXScene->simulate((float)(1.0f/60.f));	//프레임 지정
	MgrPhysXScene->flushStream();
	MgrPhysXScene->fetchResults(NX_RIGID_BODY_FINISHED, true);
}

void MainGame::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if(m_pCamera)
		m_pCamera->WndProc(hWnd, msg, wParam, lParam);
}

void MainGame::SetAddSound()
{
	g_pSoundManager->LoadSound("Sound", "menuUpDown.wav", false);
	g_pSoundManager->LoadSound("Sound", "menuNext.wav",false);
	g_pSoundManager->LoadSound("Sound", "menuPrev.wav", false);
	g_pSoundManager->LoadSound("Sound", "menuLeftRight.wav", false);
	g_pSoundManager->LoadSound("Sound", "boxslide.wav", false);
	g_pSoundManager->LoadSound("Sound", "honkgood.wav", false);
}


