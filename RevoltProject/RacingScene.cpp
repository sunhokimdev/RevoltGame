#include "stdafx.h"
#include "RacingScene.h"
#include "cTrack.h"
#include "cLight.h"

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
	light.Ambient = D3DXCOLOR(0.8,0.8,0.8,1);
	light.Diffuse = D3DXCOLOR(0.8, 0.8, 0.8, 1);
	light.Specular = D3DXCOLOR(0.8, 0.8, 0.8, 1);
	D3DXVECTOR3 dir = { 0,-1,0 };
	D3DXVec3Normalize(&dir, &dir);
	light.Direction = dir;
	g_pD3DDevice->SetLight(0, &light);
	g_pD3DDevice->LightEnable(0, true);

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
}

void RacingScene::Render()
{
	//¾Úºñ¾ğÆ®
	g_pD3DDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(230,230,230));

	if (m_pTrack)
	{
		m_pTrack->Render();
	}
}
