#include "stdafx.h"
#include "cPickUp.h"


cPickUp::cPickUp()
	:m_isExist(true)
	,m_isTimerRoll(false)
	,m_fRespawnTime(0)
{
}


cPickUp::~cPickUp()
{
}

void cPickUp::Update()
{
	if (GetPhysXData()->m_pUserData->IsPickUp == NX_FALSE)
	{
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
	}

	if (m_fRespawnTime > 10)
	{
		GetPhysXData()->m_pUserData->IsPickUp = NX_TRUE;
		m_isTimerRoll = false;
		m_fRespawnTime = 0;
	}

	
	//m_isEnable 체크후
	//lightIndex를 이용해 라이트 온/오프
}

void cPickUp::Render()
{
	if (m_isExist)
	{
		Object::Render();
	}
}
