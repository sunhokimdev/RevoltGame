#include "stdafx.h"
#include "CameraManager.h"
#include "GameNode.h"

CameraManager::CameraManager()
	: m_vEye(0, 2, -20)
	, m_vLookAt(0, 0, 0)
	, m_vUp(0, 1, 0)
	, m_pvTarget(NULL)
	, m_fCameraDistance(50.0f)
	, m_isLButtonDown(false)
	, m_vCamRotAngle(0, 0, 0)
	, m_fCamTime(0.0f)
{
	m_ptPrevMouse.x = 0;
	m_ptPrevMouse.y = 0;
}


CameraManager::~CameraManager()
{
}

void CameraManager::Setup(D3DXVECTOR3* pvTarget)
{
	m_pvTarget = pvTarget;

	m_fCamTime = 0.0f;

	D3DXMATRIXA16	matProj;
	D3DXMatrixPerspectiveFovLH(&matProj,
		D3DX_PI / 4.0f,
		WINSIZEX / (float)WINSIZEY,
		1.0f, 1000.0f);
	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);
}

void CameraManager::Update()
{
	//	Move();

	m_fCamTime += 0.001f;

	D3DXMATRIXA16 matR, matRX, matRY;
	D3DXMatrixRotationX(&matRX, m_vCamRotAngle.x);
	D3DXMatrixRotationY(&matRY, m_vCamRotAngle.y);

	matR = matRX * matRY;

	if (m_pvTarget)
	{
		m_vEye = *m_pvTarget;
		m_vLookAt = m_vNextLootAt;
		//if (g_SceneManager->GetCurrScene()->GetSceneName() == "Race")
		//{
		//	m_vEye = *m_pvTarget;
		//	m_vLookAt = m_vNextLootAt;
		//}
		//else
		//{
		//	D3DXVec3Lerp(&m_vEye, &m_vEye, m_pvTarget, m_fCamTime);
		//	D3DXVec3Lerp(&m_vLookAt, &m_vLookAt, &m_vNextLootAt, m_fCamTime);
		//}
	}
	else m_vEye = D3DXVECTOR3(0, 0, 0);

//	m_vEye = D3DXVECTOR3(0, 9, 0);
//	m_vLookAt = D3DXVECTOR3(1, -1, 0) + m_vEye;

	D3DXVec3TransformCoord(&m_vEye, &m_vEye, &matR);

	D3DXMATRIXA16 matView;
	D3DXMatrixIdentity(&matView);
	D3DXMatrixLookAtLH(&matView, &m_vEye,
		&m_vLookAt, &m_vUp);

	g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);
}

void CameraManager::Destroy()
{

}

void CameraManager::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

}

void CameraManager::Move()
{

}
