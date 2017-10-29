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
	
	m_pLightSun = new cLight;
	if (m_pLightSun)
	{
		m_pLightSun->Setup(0, D3DLIGHT_POINT, C_YELLOW, { 0,1,0 });
		m_pLightSun->Switch(true);
	}
}

void RacingScene::Destroy()
{
	SAFE_DESTROY(m_pTrack);
	SAFE_DELETE(m_pTrack);
	SAFE_DELETE(m_pLightSun);
}

void RacingScene::Update()
{
	SAFE_UPDATE(m_pTrack);
}

void RacingScene::Render()
{
	//g_pD3DDevice->SetRenderState(D3DRS_AMBIENT, 0x00202020);
	//g_pD3DDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(200,200,200));
	if (m_pTrack)
	{
		m_pTrack->Render();
	}
}
