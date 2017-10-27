#include "stdafx.h"
#include "RacingScene.h"
#include "cTrack.h"

RacingScene::RacingScene(){}

RacingScene::~RacingScene(){}

void RacingScene::Setup()
{
	m_pTrack = new cTrack;
	if (m_pTrack)
	{
		m_pTrack->Setup();
		m_pTrack->LoadTrack("Market2");
	}
	g_CamManager->SetLookAt(&D3DXVECTOR3(0, 0, 0));
}

void RacingScene::Destroy()
{
	SAFE_DESTROY(m_pTrack);
	SAFE_DELETE(m_pTrack);
}

void RacingScene::Update()
{
	SAFE_UPDATE(m_pTrack);
}

void RacingScene::Render()
{
	SAFE_RENDER(m_pTrack);
}
