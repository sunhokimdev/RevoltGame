#include "stdafx.h"
#include "cPickUp.h"


cPickUp::cPickUp()
	:m_isExist(true)
	,m_isTimerRoll(false)
	,m_fRespawnTime(0)
	,m_fAngle(0)
{
}


cPickUp::~cPickUp()
{
}

void cPickUp::Update()
{
	if (GetPhysXData()->m_pUserData->IsPickUp == NX_FALSE)
	{
		if (m_isExist)
		{
			g_pSoundManager->Play("pickup.wav", 0.8f,GetPosition());
		}
		m_isExist = false;
		m_isTimerRoll = true;
	}
	else
	{
		m_isExist = true;
	}

	if (m_isTimerRoll)
	{
		m_fRespawnTime += g_pTimeManager->GetElapsedTime();
		if (m_fRespawnTime > 10)
		{
			GetPhysXData()->m_pUserData->IsPickUp = NX_TRUE;
			m_isTimerRoll = false;
			m_fRespawnTime = 0;
			g_pSoundManager->Play("pickgen.wav",0.8f, GetPosition());
		}
	}
		
	//m_isEnable 체크후
	//lightIndex를 이용해 라이트 온/오프
}

void cPickUp::Render()
{
	if (m_isExist)
	{
		m_fAngle += 0.05f;
		if (m_fAngle > D3DX_PI * 2) m_fAngle -= D3DX_PI*2;
		
		D3DXMATRIX mat;
		D3DXMatrixRotationY(&mat, m_fAngle);
		
		cTransform::SetQuaternion(mat);
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat);
		Object::Render();
	}
}
