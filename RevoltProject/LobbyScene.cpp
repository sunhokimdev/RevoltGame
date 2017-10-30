#include "stdafx.h"
#include "LobbyScene.h"
#include "Map.h"
#include "Lobby.h"


LobbyScene::LobbyScene()
	: m_pMap(NULL)
	, m_pLobby(NULL)
{
}


LobbyScene::~LobbyScene()
{
	SAFE_DELETE(m_pMap);
	SAFE_DELETE(m_pLobby);
}

void LobbyScene::Setup()
{
	m_pMap = new Map;
	m_pMap->Setup();

	m_pLobby = new Lobby;
	m_pLobby->Setup();
}

void LobbyScene::Update()
{
	if (m_pMap)	m_pMap->Update();
	if (m_pLobby) m_pLobby->Update();
}

void LobbyScene::Render()
{
	if (m_pMap)	m_pMap->Render();
	if (m_pLobby) m_pLobby->Render();
}
