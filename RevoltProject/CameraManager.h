#pragma once
#define g_pCamManager CameraManager::GetInstance()

class CameraManager
{
	SINGLETONE(CameraManager);
public:

	void Setup(D3DXVECTOR3*	pvTarget);
	void Update();
	void Destroy();
	void WndProc(HWND hWnd, UINT message,
		WPARAM wParam, LPARAM lParam);


	void SetLookAt(D3DXVECTOR3* pvLookAt) { m_vNextLootAt = *pvLookAt; }
	void SetCamPos(D3DXVECTOR3* pvCamPos) { m_pvTarget = pvCamPos; }
	void SetCamEye(D3DXVECTOR3 camPos) { m_vEye = camPos; }

	void Move();
	D3DXVECTOR3* GetLookAt() { return &m_vLookAt; }
	D3DXVECTOR3* GetCamPos() { return &m_vEye; };

private:
	D3DXVECTOR3		m_vEye;
	D3DXVECTOR3		m_vLookAt;
	D3DXVECTOR3		m_vUp;
	D3DXVECTOR3*	m_pvTarget;
	D3DXVECTOR3		m_vNextLootAt;

	POINT			m_ptPrevMouse;
	bool			m_isLButtonDown;
	float			m_fCameraDistance;
	float			m_fCamTime;
	D3DXVECTOR3		m_vCamRotAngle;
};

