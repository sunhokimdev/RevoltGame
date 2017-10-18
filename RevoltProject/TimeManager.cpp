#include "stdafx.h"
#include "TimeManager.h"


TimeManager::TimeManager()
{
}


TimeManager::~TimeManager()
{
}

void TimeManager::Update()
{
	DWORD dwCurrentTime = GetTickCount();
	m_fElapsedTime = (dwCurrentTime - m_dwLastUpdateTIme) / 1000.0f;
	m_dwLastUpdateTIme = dwCurrentTime;
}

float TimeManager::GetElapsedTime()
{
	return m_fElapsedTime;
}

float TimeManager::GetLastUpdateTime()
{
	return m_dwLastUpdateTIme / 1000.0f;
}
