#include "stdafx.h"
#include "TimeManager.h"
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")

TimeManager::TimeManager()
{
}

TimeManager::~TimeManager()
{
}

void TimeManager::Setup()
{
	//m_fWorldTime = 0;
	//m_fElapsedTime = 0;

	
	//고성능 타이머가 지원되는 CPU면 초당 밀리세컨 값이 들어감(0.001초)
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&m_PeriodFrequency))
	{
		
		m_isHardware = true;
		QueryPerformanceCounter((LARGE_INTEGER*)&m_LastTime);

		//초당 시간 계산 범위
		m_TimeScale = 1.0f / m_PeriodFrequency;
	}
	else
	{
		m_isHardware = false;

		//밀리세컨드 단위로 강제로 고정
		m_LastTime = timeGetTime();
		m_TimeScale = 0.001f;
	}

	m_FrameRate = 0;
	m_FPSFrameCount = 0;
	m_FPSTimeElapsed = 0;
	m_WorldTime = 0.0f;
}

void TimeManager::Update(float lockFPS/* = 0.0f*/)
{
	//DWORD dwCurrentTime = GetTickCount();
	//m_fElapsedTime = (dwCurrentTime - m_dwLastUpdateTIme) / 1000.0f;
	//m_dwLastUpdateTIme = dwCurrentTime;
	//m_fWorldTime += m_fElapsedTime;

	//고성능타이머지원?
	if (m_isHardware)
	{
		//마이크로초 단위와 동조율이 일치하면
		QueryPerformanceCounter((LARGE_INTEGER*)&m_CurTime);
	}
	else
	{
		//지원하지 않으면 강제로 시간을 맞춘다.
		m_CurTime = timeGetTime();
	}

	//현재시간과 마지막시간의 경과량을 가져온다.
	//여기의 값이 0.001초 단위다
	m_TimeElapsed = (m_CurTime - m_LastTime) * m_TimeScale;

	//여기 범주를 흔히 프레임 스키핑이라고 부름
	if (lockFPS > 0.0f)
	{
		//lockFPS == 프레임 고정범위 값이 들어오면
		while (m_TimeElapsed < (1.0f / lockFPS))
		{
			if (m_isHardware) QueryPerformanceCounter((LARGE_INTEGER*)&m_CurTime);
			else m_CurTime = timeGetTime();

			m_TimeElapsed = (m_CurTime - m_LastTime) * m_TimeScale;
		}
	}

	//한 타임을 돌았을 때
	m_LastTime = m_CurTime;
	m_FPSFrameCount++;
	m_FPSTimeElapsed += m_TimeElapsed;
	m_WorldTime += m_TimeElapsed;

	//1초가 지나면 프레임초기화를 해준다.
	if (m_FPSTimeElapsed > 1.0f)
	{
		m_FrameRate = m_FPSFrameCount;
		m_FPSFrameCount = 0;
		m_FPSTimeElapsed = 0.0f;
	}
}

void TimeManager::Render()
{
	std::string FrameRate = "FrameRate   : " + std::to_string(m_FrameRate);
	std::string ElapsedTime = "ElapsedTime : " + std::to_string(m_TimeElapsed);
	std::string WorldTime = "WorldTime   : " + std::to_string(m_WorldTime);
	g_pTextManager->WriteText(FrameRate, "굴림체_7", 1, 0, C_WHITE);
	g_pTextManager->WriteText(ElapsedTime, "굴림체_7", 1, 12, C_WHITE);
	g_pTextManager->WriteText(WorldTime, "굴림체_7", 1, 24, C_WHITE);
}

//float TimeManager::GetLastUpdateTime()
//{
//	return m_dwLastUpdateTIme / 1000.0f;
//}

unsigned long TimeManager::GetFrameRate(char * str)
{
	if (str != NULL)
	{
		
		//wsprintf(str, "FPS : %d", m_FrameRate);
	}

	return m_FrameRate;
}
