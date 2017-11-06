#include "stdafx.h"
#include "TimeManager.h"


float g_timeFix;
TimeManager::TimeManager()
	:m_fWorldTime(0)
{
	g_timeFix = -1.0f;
}


TimeManager::~TimeManager()
{
}

void TimeManager::Setup()
{
	m_fWorldTime = 0;
	m_fElapsedTime = 0;

	g_timeFix = (float)(1.f / 60.f);
}

void TimeManager::Update()
{
	DWORD dwCurrentTime = GetTickCount();
	m_fElapsedTime = (dwCurrentTime - m_dwLastUpdateTIme) * 0.001f;/// 1000.0f;

	if (m_fElapsedTime > g_timeFix * 1.5f || m_fElapsedTime > 100.f || m_fElapsedTime < 0.00001)
		m_fElapsedTime = g_timeFix;
	else
		g_timeFix = m_fElapsedTime;



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
	return m_dwLastUpdateTIme * 0.001f;
}
