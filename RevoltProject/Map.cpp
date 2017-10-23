#include "stdafx.h"
#include "Map.h"
#include "ObjectLoader.h"
#include "MtlTex.h"
#include "Thing.h"

LOBBY Map::g_LobbyState;

Map::Map()
	: m_stage(0)
{
}

Map::~Map()
{
}

void Map::Setup()
{
	ObjectLoader loader;
	m_map[0] = new ST_MAP;
	m_map[0]->m_pObjMesh = loader.LoadMesh(
		m_map[0]->m_vecObjMtlTex,
		"Maps/Front", "Front.obj");

	SetupThing();
}

void Map::Update()
{
	if (g_LobbyState <= SELECT_MAP_LOBBY)
		m_stage = 0;
	else if (g_LobbyState > SELECT_MAP_LOBBY)
		m_stage = 1;

	for (int i = 0;i < m_map[m_stage]->m_vecThing.size();i++)
	{
		m_map[m_stage]->m_vecThing[i]->Update();
	}
}

void Map::Render()
{
	g_pD3DDevice->SetTexture(0, NULL);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

	D3DXMATRIXA16	matWorld, matS, matR;

	D3DXMatrixIdentity(&matWorld);

	g_pD3DDevice->SetTransform(D3DTS_WORLD,
		&matWorld);

	for (size_t i = 0; i < m_map[m_stage]->m_vecObjMtlTex.size(); ++i)
	{
		g_pD3DDevice->SetMaterial(
			&m_map[m_stage]->m_vecObjMtlTex[i]->GetMaterial());

		if (m_map[m_stage]->m_vecObjMtlTex[i]->GetTexture() != NULL)
		{
			g_pD3DDevice->SetTexture(
				0,
				m_map[m_stage]->m_vecObjMtlTex[i]->GetTexture());
		}
		m_map[m_stage]->m_pObjMesh->DrawSubset(i);
	}

	/*   오브젝트를 그리는 작업   */
	for (int i = 0;i < m_map[m_stage]->m_vecThing.size();i++)
	{
		m_map[m_stage]->m_vecThing[i]->Render();
	}
}

void Map::SetupThing()
{
	Thing* tThing1 = new Thing;
	tThing1->SetMesh("Maps/Front/namestand", "namestand.obj");
	tThing1->SetPosition(10.0f, 0.0f, 18.0f);
	tThing1->SetLobby(CREATE_PROFILE_LOBBY);
	tThing1->SetRotationY(D3DX_PI / 4.0f);
	
	Thing* tThing2 = new Thing;
	tThing2->SetMesh("Maps/Front/nametire", "nametire.obj");
	tThing2->SetPosition(10.0f, 4.8f, 18.0f);
	tThing2->SetRotationY(D3DX_PI / 4.0f);
	tThing2->SetLobby(CREATE_PROFILE_LOBBY);
	tThing2->SetRotationX(-D3DX_PI / 15.0f);
	tThing2->SetIsRot(true);

	Thing* tThing3 = new Thing;
	tThing3->SetMesh("Maps/Front/plainbox", "plainbox.obj");
	tThing3->SetPosition(15.0f, 4.7f, 17.0f);
	tThing3->SetRotationY(-D3DX_PI / 100.0f);

	Thing* tThing4 = new Thing;
	tThing4->SetMesh("Maps/Front/plainbox", "plainbox.obj");
	tThing4->SetPosition(16.5f, 6.5f, 17.0f);
	tThing4->SetRotationY(-D3DX_PI / 120.0f);

	Thing* tThing5 = new Thing;
	tThing5->SetMesh("Maps/Front/carbox", "carbox.obj");
	tThing5->SetTarget(14.0f, 9.8f, 9.0f);
	tThing5->SetLobby(SELECT_CAR_LOBBY);
	tThing5->SetIndex(0);
	tThing5->SetPosition(13.0f, 0.8f, 15.2f);
	tThing5->SetRotationY(-D3DX_PI / 110.0f);

	Thing* tThing6 = new Thing;
	tThing6->SetMesh("Maps/Front/carbox", "carbox.obj");
	tThing6->SetTarget(14.0f, 9.8f, 9.0f);
	tThing6->SetLobby(SELECT_CAR_LOBBY);
	tThing6->SetIndex(1);
	tThing6->SetPosition(15.05f, 0.8f, 15.0f);
	tThing6->SetRotationY(D3DX_PI / 14.0f);

	Thing* tThing7 = new Thing;
	tThing7->SetMesh("Maps/Front/carbox", "carbox.obj");
	tThing7->SetTarget(14.0f, 9.8f, 9.0f);
	tThing7->SetLobby(SELECT_CAR_LOBBY);
	tThing7->SetIndex(2);
	tThing7->SetPosition(17.0f, 0.8f, 14.1f);
	tThing7->SetRotationY(D3DX_PI / 5.0f);

	Thing* tThing8 = new Thing;
	tThing8->SetMesh("Maps/Front/carbox", "carbox.obj");
	tThing8->SetTarget(14.0f, 9.8f, 9.0f);
	tThing8->SetLobby(SELECT_CAR_LOBBY);
	tThing8->SetIndex(3);
	tThing8->SetPosition(18.4f, 0.8f, 12.5f);
	tThing8->SetRotationY(D3DX_PI / 3.0f);

	Thing* tThing9 = new Thing;
	tThing9->SetMesh("Maps/Front/carbox", "carbox.obj");
	tThing9->SetTarget(14.0f, 9.8f, 9.0f);
	tThing9->SetLobby(SELECT_CAR_LOBBY);
	tThing9->SetIndex(4);
	tThing9->SetPosition(19.0f, 0.8f, 10.3f);
	tThing9->SetRotationY(D3DX_PI / 2.0f);

	Thing* tThing10 = new Thing;
	tThing10->SetMesh("Maps/Front/carbox", "carbox.obj");
	tThing10->SetTarget(14.0f, 9.8f, 9.0f);
	tThing10->SetLobby(SELECT_CAR_LOBBY);
	tThing10->SetIndex(5);
	tThing10->SetPosition(19.0f, 0.8f, 8.5f);
	tThing10->SetRotationY(D3DX_PI / 2.0f);

	m_map[0]->m_vecThing.push_back(tThing1);
	m_map[0]->m_vecThing.push_back(tThing2);
	m_map[0]->m_vecThing.push_back(tThing3);
	m_map[0]->m_vecThing.push_back(tThing4);
	m_map[0]->m_vecThing.push_back(tThing5);
	m_map[0]->m_vecThing.push_back(tThing6);
	m_map[0]->m_vecThing.push_back(tThing7);
	m_map[0]->m_vecThing.push_back(tThing8);
	m_map[0]->m_vecThing.push_back(tThing9);
	m_map[0]->m_vecThing.push_back(tThing10);
}
