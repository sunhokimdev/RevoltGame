#include "stdafx.h"
#include "RacingScene.h"
#include "cTrack.h"
#include "cLight.h"
#include "cCar.h"
#include "InGameUI.h"
#include "UITextImageView.h"
#include "cSkyBox.h"

RacingScene::RacingScene()
	: m_select(99)
	, m_pSkyBox(NULL)
{}

RacingScene::~RacingScene() {}

void RacingScene::Setup()
{

	UITextImageView::m_Select = &m_select;

	D3DXCreateSprite(g_pD3DDevice, &m_Sprite);
	g_pCamManager->SetLookAt(&D3DXVECTOR3(0, 0, 0));
 
	m_pInGameUI = new InGameUI;
	m_pInGameUI->Setup();
	

	m_pTrack = new cTrack;
	if (m_pTrack)
	{
		m_pTrack->Setup();
		m_pTrack->LoadTrack("Market2");
	}
	m_nLightIDCount = 0;

	D3DLIGHT9 light;
	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Ambient = D3DXCOLOR(0.6, 0.6, 0.6, 1);
	light.Diffuse = D3DXCOLOR(0.6, 0.6, 0.6, 1);
	light.Specular = D3DXCOLOR(0.6, 0.6, 0.6, 1);
	D3DXVECTOR3 dir = { 0,-1,0 };
	D3DXVec3Normalize(&dir, &dir);
	light.Direction = dir;
	g_pD3DDevice->SetLight(0, &light);
	g_pD3DDevice->LightEnable(0, true);

	g_pCamManager->SetCamPos(camPos);
	g_pCamManager->SetLookAt(camLookTarget);

	//앰비언트
	//g_pD3DDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(230,230,230));
	g_pD3DDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(50, 50, 50));

	/// car 생성
	{
		cCar* pCar = new cCar;
		pCar->LoadCar("tc1");
	//	pCar->SetTotalCheckBoxNum(m_pTrack->GetTrackCheckBoxSize());
		vecCars.push_back(pCar);
	}
	{
		//	cCar* pCar = new cCar;
		//	pCar->LoadMesh("tc2");
		//	pCar->CreatePhsyX(stCARSPEC());
		//	pCar->SetCarValue(1000, 5000, 0.1, 0, NxPi / 8, NxPi * 0.05f);
		//
		//	pCar->GetPhysXData()->SetPosition(NxVec3(0, 0, 3));
		//	vecCars.push_back(pCar);
	}

	m_pInGameUI->LinkCarPt(vecCars[0]);
	for (int i = 0; i < vecCars.size(); i++)
	{
		vecCars[i]->LinkTrackPt(m_pTrack);
	}

	m_pSkyBox = new cSkyBox;
	m_pSkyBox->Setup();
}

void RacingScene::Destroy()
{
	SAFE_DESTROY(m_pTrack);
	SAFE_DELETE(m_pTrack);
	SAFE_DELETE(m_pLightSun);
	SAFE_DELETE(m_pInGameUI);
	SAFE_DESTROY(m_pSkyBox);
	SAFE_DELETE(m_pSkyBox);
}

void RacingScene::Update()
{
	GameNode::Update();
	SAFE_UPDATE(m_pTrack);
	//SAFE_UPDATE(g_pTimeManager); << 메인에서 돌아가고있음

	for (int i = 0; i < vecCars.size(); i++)
	{
		 if(IsCarRunTrue(vecCars[i])) vecCars[i]->Update();
		 else vecCars[i]->RunEnd();
	}

	if (m_pInGameUI)
	{
		m_pInGameUI->Update();
	}
	
}


void RacingScene::Render()
{
	if (m_pSkyBox)
	{
		m_pSkyBox->Render(); 
	}

	if (m_pTrack)
	{
		m_pTrack->Render();
	}

	for each(cCar* p in vecCars)
	{
		p->Render();
	}

	//D3DXMATRIXA16 matWorld;
	//
	//D3DXMatrixIdentity(&matWorld);
	//
	//g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	m_pInGameUI->Render(m_Sprite);
}

void RacingScene::LastUpdate()
{
	m_pTrack->LastUpdate();

	for each(cCar* p in vecCars)
	{
		p->LastUpdate();
	}

	UpdateCamera();
}

void RacingScene::UpdateCamera()
{
//	return;
#define CAM_X (*camPos).x
#define CAM_Y (*camPos).y
#define CAM_Z (*camPos).z
#define CAM_POS (*camPos)

	//회전 매트릭스 받아옴
	D3DXMATRIXA16 matR = vecCars[0]->GetCarRotMatrix();
	
	//matR = vecCars[0]->GetMatrix(false, true, false); //이걸 사용하면 약간 부정확함

	float distToCar = 5; //차와의 거리
	float Height = 2; //카메라 높이

	D3DXVECTOR3 carDir = { 1,0,0 };
	D3DXVec3TransformNormal(&carDir, &carDir, &matR);

	//자동차 포지션
	D3DXVECTOR3 carPos = { 
		vecCars[0]->GetPosition().x,
		vecCars[0]->GetPosition().y + 0.5f ,
		vecCars[0]->GetPosition().z };

	*camLookTarget = carPos;//D3DXVECTOR3(pos.x, pos.y + 2.f, pos.z);

	D3DXVECTOR3 camDir = (*camLookTarget) - CAM_POS;
	D3DXVec3Normalize(&camDir,&camDir);

	//레이초기화
	NxRay RayCam;
	RayCam.orig = NxVec3(carPos);
	RayCam.dir = NxVec3(-carDir);
	
	NxRaycastHit RayCamHit;
	RayCamHit.shape = NULL;
	g_pPhysXScene->raycastClosestShape(RayCam, NxShapesType::NX_ALL_SHAPES, RayCamHit);

	
	float x = carPos.x - (carDir.x * distToCar);
	float y = carPos.y - (carDir.y * distToCar) + Height;
	float z = carPos.z - (carDir.z * distToCar);

	if (RayCamHit.distance < distToCar)
	{
		if (RayCamHit.shape)
		{
			if (RayCamHit.shape->getActor().getName() == "map")
			{
				x = RayCamHit.worldImpact.x;
				y = carPos.y + Height;//RayCamHit.worldImpact.y;
				z = RayCamHit.worldImpact.z;
			}
		}
	}

	// 카메라 목적지
	D3DXVECTOR3 vDest = { x,y,z };

	//D3DXVECTOR3 moveDir;
	//moveDir = vDest - CAM_POS;
	//D3DXVec3Normalize(&moveDir, &moveDir);

	//D3DXVECTOR3 distToDest = vDest - CAM_POS;

	// 카메라 무빙
	D3DXVec3Lerp(camPos, camPos, &vDest, 0.2f);

	g_pCamManager->SetCamPos(camPos);
	g_pCamManager->SetLookAt(camLookTarget);
}

bool RacingScene::IsCarRunTrue(cCar* pCar)
{
	return m_trackEndCount > pCar->GetCountRapNum();
}
