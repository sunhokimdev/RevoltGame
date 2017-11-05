#include "stdafx.h"
#include "TimeManager.h"


TimeManager::TimeManager()
	:m_fWorldTime(0)
{
}


TimeManager::~TimeManager()
{
}

void TimeManager::Setup()
{
	m_fWorldTime = 0;
	m_fElapsedTime = 0;
}

void TimeManager::Update()
{
	DWORD dwCurrentTime = GetTickCount();
	m_fElapsedTime = (dwCurrentTime - m_dwLastUpdateTIme) * 0.001f;/// 1000.0f;
	m_dwLastUpdateTIme = dwCurrentTime;
	m_fWorldTime += m_fElapsedTime;
}

void TimeManager::Render()
{
	
}

float TimeManager::GetElapsedTime()
{
	return m_fElapsedTime;
}

float TimeManager::GetLastUpdateTime()
{
	return m_dwLastUpdateTIme / 1000.0f;
}
