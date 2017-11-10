#include "stdafx.h"
#include "Map.h"
#include "ObjectLoader.h"
#include "MtlTex.h"
#include "Thing.h"
#include "Car.h"
#include "CarBox.h"
#include "WheelTire.h"
#include "PickUpObject.h"
#include "MapLoader.h"
#include "cTrack.h"
#include "Camera.h"
#include "cSkyBox.h"
LOBBY* Map::g_LobbyState;



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

	m_pObjMesh = loader.LoadMesh(m_vecObjMtlTex, "Maps/Front", "Front.obj");
	SetupThing();

	m_track[0] = new cTrack;
	m_track[1] = new cTrack;
	m_track[2] = new cTrack;
	m_track[3] = new cTrack;
	m_track[4] = new cTrack;

	m_track[0]->trackName = "Front";
	m_track[0]->trackNum = 0;

	m_track[1]->trackName = "Market2";
	m_track[1]->trackNum = 1;
	m_track[2]->trackName = "Garden";
	m_track[2]->trackNum = 2;
	m_track[3]->trackName = "Museum";
	m_track[3]->trackNum = 3;
	m_track[4]->trackName = "Toytanic";
	m_track[4]->trackNum = 4;

	m_pSkyBox = new cSkyBox;
	m_pSkyBox->Setup("Maps/GalaxyBox", "GalaxyBox.obj");
}

void Map::Destroy()
{
	SAFE_DESTROY(m_pSkyBox);
	SAFE_DELETE(m_pSkyBox);
	
	for each(auto p in m_track)
	{
		p.second->Destroy();
		SAFE_DELETE(p.second);
	}
	m_track.clear();
	for each(auto p in m_vecObjMtlTex)
	{
		SAFE_DELETE(p);
	}
	m_vecObjMtlTex.clear();
	for each(auto p in m_vecThing)
	{
		p->Destroy();
		SAFE_DELETE(p);
	}
	m_vecThing.clear();
}

void Map::Update()
{

	if (m_stage == 0)
	{
		for each(Thing* pth in m_vecThing)
		{
			pth->Update();
		}
		if (*g_LobbyState - IN_GAME_MAP < 0)
		{
			m_stage = 0;
		}
		else
		{
			if (m_stage != (*g_LobbyState - IN_GAME_MAP))
			{
				m_stage = *g_LobbyState - IN_GAME_MAP;

				//m_track[m_stage]->LoadTrack(m_track[m_stage]->trackName , g_pCamManager);

//				ObjectLoader::LoadMesh(m_track[m_stage]->GetMeshData(), "Maps", m_track[m_stage]->trackName.c_str());
			}
		}
	}
	else
	{
		//레이싱 화면으로 넘어가면 실행되는 업데이트 부
		m_track[m_stage]->Update();
	}
}

void Map::Render()
{
	g_pD3DDevice->SetTexture(0, NULL);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);

	//스카이박스
	if (m_pSkyBox)
	{
		m_pSkyBox->Render();
	}

	// 맵 렌더

	D3DXMATRIXA16	matWorld, matS, matR;
	D3DXMatrixIdentity(&matWorld);
	if (m_stage == 0)
	{
		/*   오브젝트를 그리는 작업   */
		if(*g_LobbyState != VIEW_CAR_LOBBY)
			for each(Thing* pth in m_vecThing) pth->Render();

		/*	 맵 그리는 작업			 */
		g_pD3DDevice->SetTexture(0, NULL);
		//g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

		D3DXMATRIXA16	matWorld;  D3DXMatrixIdentity(&matWorld);

		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

		for (size_t i = 0; i < m_vecObjMtlTex.size(); ++i)
		{
			g_pD3DDevice->SetMaterial(&m_vecObjMtlTex[i]->GetMaterial());
			if (m_vecObjMtlTex[i]->GetTexture() != NULL) g_pD3DDevice->SetTexture(0, m_vecObjMtlTex[i]->GetTexture());

			m_pObjMesh->DrawSubset(i);

			if (m_vecObjMtlTex[i]->GetTexture() != NULL) g_pD3DDevice->SetTexture(0, NULL);
		}

		/*   오브젝트 거울을 그리는 작업   */
		if (*g_LobbyState >= MAIN_LOBBY3)
			for each(Thing* pth in m_vecThing) pth->MirrorRender();
		
		/*   오브젝트를 그리는 작업   */
		if (*g_LobbyState == VIEW_CAR_LOBBY)
			for each(Thing* pth in m_vecThing) pth->Render();

	}
	else
	{
		//레이싱 화면으로 넘어가면 실행되는 렌더 부
		m_track[m_stage]->Render();
	}
}

void Map::SetupThing()
{
	Thing* tThing1 = new Thing;
	tThing1->SetMesh("Maps/Front/namestand", "namestand.obj");
	tThing1->SetPosition(10.0f, 0.0f, 18.0f);
	tThing1->SetRotationY(D3DX_PI / 4.0f);

	WheelTire* tThing2 = new WheelTire;
	tThing2->SetMesh("Maps/Front/nametire", "nametire.obj");
	tThing2->SetPosition(10.0f, 4.8f, 18.0f);
	tThing2->SetRotationY(D3DX_PI / 4.0f);
	tThing2->SetRotationX(-D3DX_PI / 15.0f);

	Thing* tThing3 = new Thing;
	tThing3->SetMesh("Maps/Front/plainbox", "plainbox.obj");
	tThing3->SetPosition(15.0f, 4.7f, 17.0f);
	tThing3->SetRotationY(-D3DX_PI / 100.0f);

	Thing* tThing4 = new Thing;
	tThing4->SetMesh("Maps/Front/plainbox", "plainbox.obj");
	tThing4->SetPosition(16.5f, 6.5f, 17.0f);
	tThing4->SetRotationY(-D3DX_PI / 120.0f);

	CarBox* tThing5 = new CarBox;
	tThing5->SetTextFile("Cars/tc1");
	tThing5->SetTarget(14.0f, 9.8f, 9.0f);
	tThing5->SetIndex(0);
	tThing5->SetPosition(13.0f, 0.8f, 15.2f);
	tThing5->SetRotationY(-D3DX_PI / 110.0f);

	CarBox* tThing6 = new CarBox;
	tThing6->SetTextFile("Cars/tc2");
	tThing6->SetTarget(14.0f, 9.8f, 9.0f);
	tThing6->SetIndex(1);
	tThing6->SetPosition(15.05f, 0.8f, 15.0f);
	tThing6->SetRotationY(D3DX_PI / 14.0f);

	CarBox* tThing7 = new CarBox;
	tThing7->SetTextFile("Cars/tc3");
	tThing7->SetTarget(14.0f, 9.8f, 9.0f);
	tThing7->SetIndex(2);
	tThing7->SetPosition(17.0f, 0.8f, 14.1f);
	tThing7->SetRotationY(D3DX_PI / 5.0f);

	CarBox* tThing8 = new CarBox;
	tThing8->SetTextFile("Cars/tc4");
	tThing8->SetTarget(14.0f, 9.8f, 9.0f);
	tThing8->SetIndex(3);
	tThing8->SetPosition(18.4f, 0.8f, 12.5f);
	tThing8->SetRotationY(D3DX_PI / 3.0f);

	CarBox* tThing9 = new CarBox;
	tThing9->SetTextFile("Cars/tc5");
	tThing9->SetMesh("Maps/Front/carbox", "carbox.obj");
	tThing9->SetTarget(14.0f, 9.8f, 9.0f);
	tThing9->SetIndex(4);
	tThing9->SetPosition(19.0f, 0.8f, 10.3f);
	tThing9->SetRotationY(D3DX_PI / 2.0f);

	CarBox* tThing10 = new CarBox;
	tThing10->SetTextFile("Cars/tc6");
	tThing10->SetMesh("Maps/Front/carbox", "carbox.obj");
	tThing10->SetTarget(14.0f, 9.8f, 9.0f);
	tThing10->SetIndex(5);
	tThing10->SetPosition(19.0f, 0.8f, 8.5f);
	tThing10->SetRotationY(D3DX_PI / 2.0f);

	PickUpObject* tThing11 = new PickUpObject;
	tThing11->Setup();
	tThing11->SetTarget(14.0f, 9.8f, 9.0f);
	tThing11->SetPosition(0.0f, 0.8f, -15.5f);

	m_vecThing.push_back(tThing1);
	m_vecThing.push_back(tThing2);
	m_vecThing.push_back(tThing3);
	m_vecThing.push_back(tThing4);
	m_vecThing.push_back(tThing5);
	m_vecThing.push_back(tThing6);
	m_vecThing.push_back(tThing7);
	m_vecThing.push_back(tThing8);
	m_vecThing.push_back(tThing9);
	m_vecThing.push_back(tThing10);
	m_vecThing.push_back(tThing11);
}



