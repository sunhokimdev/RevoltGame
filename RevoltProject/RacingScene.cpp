#include "stdafx.h"
#include "RacingScene.h"
#include "cTrack.h"
#include "cLight.h"
#include "cCar.h"

RacingScene::RacingScene(){}

RacingScene::~RacingScene(){}

void RacingScene::Setup()
{
	g_pCamManager->SetLookAt(&D3DXVECTOR3(0, 0, 0));
	m_pTrack = new cTrack;
	if (m_pTrack)
	{
		m_pTrack->Setup();
		m_pTrack->LoadTrack("Market2");
	}
	m_nLightIDCount = 0;

	D3DLIGHT9 light;
	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Ambient = D3DXCOLOR(0.6,0.6,0.6,1);
	light.Diffuse = D3DXCOLOR(0.6, 0.6, 0.6, 1);
	light.Specular = D3DXCOLOR(0.6, 0.6, 0.6, 1);
	D3DXVECTOR3 dir = { 0,-1,0 };
	D3DXVec3Normalize(&dir, &dir);
	light.Direction = dir;
	g_pD3DDevice->SetLight(0, &light);
	g_pD3DDevice->LightEnable(0, true);

	g_pCamManager->SetCamPos(camPos);
	g_pCamManager->SetLookAt(camLookTarget);

	//¾Úºñ¾ðÆ®
	//g_pD3DDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(230,230,230));
	g_pD3DDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(50, 50, 50));

	cCar* pCar = new cCar;
	pCar->LoadMesh("tc1");
	pCar->CreatePhsyX();
	pCar->SetCarValue(5000, 0.01, 0, NxPi/4, NxPi * 0.01f);
	vecCars.push_back(pCar);
}

void RacingScene::Destroy()
{
	SAFE_DESTROY(m_pTrack);
	SAFE_DELETE(m_pTrack);
	SAFE_DELETE(m_pLightSun);
}

void RacingScene::Update()
{
	GameNode::Update();
	SAFE_UPDATE(m_pTrack);

	for each(cCar* p in vecCars)
	{
		p->Update();
	}

	UpdateCamera();
	LastUpdate();
}


void RacingScene::Render()
{
	if (m_pTrack)
	{
		m_pTrack->Render();
	}

	for each(cCar* p in vecCars)
	{
		p->Render();
	}
}

void RacingScene::LastUpdate()
{
	m_pTrack->LastUpdate();

	for each(cCar* p in vecCars)
	{
		p->LastUpdate();
	}
}

void RacingScene::UpdateCamera()
{
	
	NxVec3 pos = vecCars[0]->GetNxVehicle()->getGlobalPose().t;

	NxF32 mat[9];

	vecCars[0]->GetNxVehicle()->getGlobalPose().M.getColumnMajor(mat);
	D3DXMATRIXA16 matR;
	D3DXMatrixIdentity(&matR);
	matR._11 = mat[0];
	matR._12 = mat[1];
	matR._13 = mat[2];
	matR._21 = mat[3];
	matR._22 = mat[4];
	matR._23 = mat[5];
	matR._31 = mat[6];
	matR._32 = mat[7];
	matR._33 = mat[8];


	D3DXVECTOR3 dir = { 1,0,1 };
	D3DXVec3TransformNormal(&dir, &dir, &matR);
	D3DXVECTOR3 carPos = { pos.x,pos.y,pos.z };

	float dist = 5;

	float x = carPos.x - (dir.x * dist);
	float y = carPos.y - (dir.y * dist) + 5;
	float z = carPos.z - (dir.z * dist);

	*camPos = { x,y,z };

	*camLookTarget = D3DXVECTOR3(pos.x, pos.y + 1, pos.z);

	g_pCamManager->SetCamPos(camPos);
	g_pCamManager->SetLookAt(camLookTarget);
}
