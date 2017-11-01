#include "stdafx.h"
#include "LobbyScene.h"
#include "Map.h"
#include "Lobby.h"
#include "cLight.h"

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

	g_pD3DDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(100, 100, 100));

	SetupLight();
	
}

void LobbyScene::Update()
{
	if (m_pMap)	m_pMap->Update();
	if (m_pLobby) m_pLobby->Update();

	//cLight light;
	//light.SetupPoint(0, C_WHITE, *g_pCamManager->GetCamPos(), 50);
	//light.Switch(true);
}

void LobbyScene::Render()
{
	if (m_pMap)	m_pMap->Render();
	if (m_pLobby) m_pLobby->Render();

	//위치확인용 매시
	//====================================================
	//D3DXMATRIXA16 mat, matT;
	//D3DXMatrixIdentity(&mat);

	//D3DXMatrixTranslation(&matT, 13, 5, 9);

	//mat = matT;

	//g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat);

	//LPD3DXMESH mesh;
	//D3DXCreateSphere(g_pD3DDevice, 0.5, 20, 20, &mesh, NULL);
	//D3DMATERIAL9 mtl;
	//ZeroMemory(&mtl, sizeof(D3DMATERIAL9));
	//mtl.Ambient = D3DXCOLOR(1, 1, 1, 1);
	//mtl.Diffuse = D3DXCOLOR(1, 1, 1, 1);
	//mtl.Specular = D3DXCOLOR(1, 1, 1, 1);

	//g_pD3DDevice->SetMaterial(&mtl);
	//mesh->DrawSubset(0);
	
	//====================================================
}

void LobbyScene::SetupLight()
{
	//WHELL TIRE SPOT LIGHT
	cLight light;
	light.SetupSpot(10, C_WHITE,
		D3DXVECTOR3(WHELLTIRE_POSITION.x, WHELLTIRE_POSITION.y + 5, WHELLTIRE_POSITION.z)
		, D3DXVECTOR3(0, -1, 0), 50);
	light.Switch(true);

	//Main Table
	cLight light2;
	light2.SetupPoint(11, C_WHITE, D3DXVECTOR3(-5,5,0), 10);
	light2.Switch(true);

	//Corridor
	cLight light3;
	light3.SetupSpot(12, C_WHITE, D3DXVECTOR3(0, 5, -40), D3DXVECTOR3(0, -1, 0), 10);
	light3.Switch(true);

	//Car
	cLight light4;
	light4.SetupPoint(13, C_WHITE, D3DXVECTOR3(15, 12, 10), 40);
	light4.Switch(true);

	cLight light6;
	light6.SetupSpot(15, C_WHITE, D3DXVECTOR3(13, 5, 9), D3DXVECTOR3(0, -1, 0), 10,D3DX_PI/4, D3DX_PI/4);
	light6.Switch(true);


	//Screen
	cLight light5;
	light5.SetupSpot(14, C_WHITE, D3DXVECTOR3(20, 5, -15), D3DXVECTOR3(0, -1, 0), 10);
	light5.Switch(true);
}
