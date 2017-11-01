#include "stdafx.h"
#include "RacingScene.h"
#include "cTrack.h"
#include "cLight.h"
#include "Effect.h"

RacingScene::RacingScene()
	: m_Sprite(NULL)
{}

RacingScene::~RacingScene(){}

void RacingScene::Setup()
{
	D3DXCreateSprite(g_pD3DDevice, &m_Sprite);

	m_pEffect = new Effect;
	m_pEffect->SetFrameRender(true);
	m_pEffect->SetFrameTexture("Objects/wbomb/wbombEffect.png", 16);

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

	


	pCar1 = new cCar;
	pCar1->LoadMesh("tc1");
//	m_vecObject.push_back(pCar1);


	//자동차 추가
	pVeh = MgrPhysX->createCarWithDesc(NxVec3(0, 2, 0), true, true, false, false, false, MgrPhysXSDK);



	g_pCamManager->SetCamPos(camPos);
	g_pCamManager->SetLookAt(camLookTarget);

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
	m_pEffect->FrameUpdate();

	if (g_pKeyManager->isOnceKeyDown('Z'))
	{
		if (!m_pEffect->GetActive())
			m_pEffect->SetActive(true);
		else
			m_pEffect->SetActive(false);
	}

	//TEST
	if (pVeh)
	{
		NxVec3 pos = pVeh->getGlobalPose().t;
		//*camPos = D3DXVECTOR3(pos.x - 5, pos.y + 5, pos.z);
		//*camLookTarget = D3DXVECTOR3(pos.x, pos.y + 3, pos.z);
		//g_pCamManager->SetCamPos(camPos);
		//g_pCamManager->SetLookAt(camLookTarget);

		static float angle = 0;
		if (g_pKeyManager->isStayKeyDown('A'))
		{
			angle += 0.1;
			camPos->z -= 1.0f;
		}
		if (g_pKeyManager->isStayKeyDown('D'))
		{
			angle -= 0.1;
			camPos->z += 1.0f;
		}
		NxWheel* wheel = pVeh->getWheel(0);
		wheel->setAngle(angle);

		wheel = pVeh->getWheel(1);
		wheel->setAngle(angle);

		pVeh->getActor()->addForce(NxVec3(0, 1, 0));

		if (g_pKeyManager->isStayKeyDown('S'))
		{
			camPos->x += 1.0f;
			NxWheel* wheel = pVeh->getWheel(0);
			wheel->tick(false, (NxReal)-1000, (NxReal)0, (NxReal)1.f / 60.f);
			wheel->setAngle(angle);

			wheel = pVeh->getWheel(1);
			wheel->tick(false, (NxReal)-1000, (NxReal)0, (NxReal)1.f / 60.f);
			wheel->setAngle(angle);

			wheel = pVeh->getWheel(2);
			wheel->tick(false, (NxReal)-1000, (NxReal)0, (NxReal)1.f / 60.f);

			wheel = pVeh->getWheel(3);
			wheel->tick(false, (NxReal)-1000, (NxReal)0, (NxReal)1.f / 60.f);
		}

		if (g_pKeyManager->isOnceKeyDown(VK_SPACE))
		{
			NxWheel* wheel = pVeh->getWheel(0);
			wheel->tick(false, (NxReal)0, (NxReal)1000, (NxReal)1.f / 60.f);

			wheel = pVeh->getWheel(1);
			wheel->tick(false, (NxReal)0, (NxReal)1000, (NxReal)1.f / 60.f);

			wheel = pVeh->getWheel(2);
			wheel->tick(false, (NxReal)0, (NxReal)1000, (NxReal)1.f / 60.f);

			wheel = pVeh->getWheel(3);
			wheel->tick(false, (NxReal)0, (NxReal)1000, (NxReal)1.f / 60.f);
		}

		if (g_pKeyManager->isStayKeyDown('W'))
		{
			camPos->x -= 1.0f;
			NxWheel* wheel = pVeh->getWheel(0);
			wheel->tick(false, (NxReal)1000, (NxReal)0, (NxReal)1.f / 60.f);

			wheel = pVeh->getWheel(1);
			wheel->tick(false, (NxReal)1000, (NxReal)0, (NxReal)1.f / 60.f);

			wheel = pVeh->getWheel(2);
			wheel->tick(false, (NxReal)1000, (NxReal)0, (NxReal)1.f / 60.f);

			wheel = pVeh->getWheel(3);
			wheel->tick(false, (NxReal)1000, (NxReal)0, (NxReal)1.f / 60.f);
		}
	}
}

void RacingScene::Render()
{
	//앰비언트
	g_pD3DDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(230,230,230));

	m_pEffect->BillboardRender(m_Sprite, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f);

	if (m_pTrack)
	{
		m_pTrack->Render();
	}
}

