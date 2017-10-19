#pragma once
class Camera
{
public:
	Camera();
	~Camera();

	void Setup(D3DXVECTOR3*	pvTarget);
	void Update();
	void WndProc(HWND hWnd, UINT message,
		WPARAM wParam, LPARAM lParam);

	void SetLookAt(D3DXVECTOR3 LookAt) { m_vNextLookAT = LookAt; }
private:
	D3DXVECTOR3		m_vEye;
	D3DXVECTOR3		m_vLookAt;
	D3DXVECTOR3		m_vUp;
	D3DXVECTOR3*	m_pvTarget;

	POINT			m_ptPrevMouse;
	bool			m_isLButtonDown;
	float			m_fCameraDistance;
	D3DXVECTOR3		m_vCamRotAngle;

	float m_fTime;
	D3DXVECTOR3 m_vNextLookAT;
};

