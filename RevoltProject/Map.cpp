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
	tThing1->SetRotationY(D3DX_PI / 4.0f);

	Thing* tThing2 = new Thing;
	tThing2->SetMesh("Maps/Front/nametire", "nametire.obj");
	tThing2->SetPosition(10.0f, 4.8f, 18.0f);
	tThing2->SetRotationY(D3DX_PI / 4.0f);
	tThing2->SetRotationX(D3DX_PI / 15.0f);
	tThing2->SetIsRot(true);

	m_map[0]->m_vecThing.push_back(tThing1);
	m_map[0]->m_vecThing.push_back(tThing2);
}
