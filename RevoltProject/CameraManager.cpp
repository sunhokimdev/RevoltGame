#include "stdafx.h"
#include "CameraManager.h"

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
	Move();

	m_fCamTime += 0.0005f;

	D3DXMATRIXA16 matR, matRX, matRY;
	D3DXMatrixRotationX(&matRX, m_vCamRotAngle.x);
	D3DXMatrixRotationY(&matRY, m_vCamRotAngle.y);

	matR = matRX * matRY;

	if (m_pvTarget)
	{   
		m_vEye = *m_pvTarget;
		m_vLookAt = m_vNextLootAt;

		//D3DXVec3Lerp(&m_vEye, &m_vEye, m_pvTarget, m_fCamTime);
		//D3DXVec3Lerp(&m_vLookAt, &m_vLookAt, &m_vNextLootAt, m_fCamTime);
	}
	else m_vEye = D3DXVECTOR3(0, 0, 0);

//	m_vEye = D3DXVECTOR3(3, 3, -3);
//	m_vLookAt = D3DXVECTOR3(0, 0, 0);

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
	switch (message)
	{
	case WM_LBUTTONDOWN:
		//m_ptPrevMouse.x = LOWORD(lParam);
		//m_ptPrevMouse.y = HIWORD(lParam);
		//m_isLButtonDown = true;
		break;

	case WM_LBUTTONUP:
		//m_isLButtonDown = false;
		break;

	case WM_MOUSEMOVE:
		//if (m_isLButtonDown)
		//{
		//	POINT ptCurrMouse;
		//	ptCurrMouse.x = LOWORD(lParam);
		//	ptCurrMouse.y = HIWORD(lParam);
		//
		//	float fDeltaX = (float)ptCurrMouse.x - m_ptPrevMouse.x;
		//	float fDeltaY = (float)ptCurrMouse.y - m_ptPrevMouse.y;
		//
		//	m_vCamRotAngle.y += (fDeltaX / 100.0f);
		//	m_vCamRotAngle.x += (fDeltaY / 100.0f);
		//	m_ptPrevMouse = ptCurrMouse;
		//}
		break;

	case WM_MOUSEWHEEL:
		//m_fCameraDistance -=
		//	(GET_WHEEL_DELTA_WPARAM(wParam) / 30.0f);
		//
		//if (m_fCameraDistance < 0.0001f)
		//	m_fCameraDistance = 0.0001f;

		break;
	}
}

void CameraManager::Move()
{
	//if (g_pKeyManager->isOnceKeyDown(VK_RBUTTON))
	//{
	//	m_ptPrevMouse = g_ptMouse;
	//}
	float KeyMoveSpd = 0.5f;

	if(g_pKeyManager->isStayKeyDown(VK_LEFT))
	{
		m_vEye.x -= KeyMoveSpd;
		m_vLookAt.x -= KeyMoveSpd;
	}
	if (g_pKeyManager->isStayKeyDown(VK_RIGHT))
	{
		m_vEye.x += KeyMoveSpd;
		m_vLookAt.x += KeyMoveSpd;
	}
	if (g_pKeyManager->isStayKeyDown(VK_DOWN))
	{
		if (g_pKeyManager->isStayKeyDown(VK_CONTROL))
		{
			m_vEye.y -= KeyMoveSpd;
		}
		else
		{
			m_vEye.z -= KeyMoveSpd;
			m_vLookAt.z -= KeyMoveSpd;
		}
	}
	if (g_pKeyManager->isStayKeyDown(VK_UP))
	{
		if (g_pKeyManager->isStayKeyDown(VK_CONTROL))
		{
			m_vEye.y += KeyMoveSpd;
		}
		else
		{
			m_vEye.z += KeyMoveSpd;
			m_vLookAt.z += KeyMoveSpd;
		}
	}
}
