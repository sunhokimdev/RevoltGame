#pragma once

#define g_pTimeManager TimeManager::GetInstance()

class TimeManager
{
	SINGLETONE(TimeManager);

private:
	//DWORD m_dwLastUpdateTIme;
	//float m_fElapsedTime;
	//float m_fWorldTime;

	bool m_isHardware; //고성능 타이머 사용할지 여부
	float m_TimeScale; //시간 경과량
	float m_TimeElapsed; //마지막 시간과 현재시간 사이의 경과량
	__int64 m_CurTime; //현재시간
	__int64 m_LastTime; //마지막시간
	__int64 m_PeriodFrequency; //동조율

	unsigned long m_FrameRate;
	unsigned long m_FPSFrameCount;
	float m_FPSTimeElapsed;
	float m_WorldTime;

	bool m_isDisplay;

public:
	
	void Setup();
	void Update(float lockFPS = 0.0f);
	void Render();

	inline float GetElapsedTime() {return m_TimeElapsed;}
	//float GetLastUpdateTime();
	unsigned long GetFrameRate(char* str = NULL);
	inline float GetWorldTime() { return m_WorldTime; }
};

