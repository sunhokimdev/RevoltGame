#pragma once

#define g_pTimeManager TimeManager::GetInstance()

class TimeManager
{
private:
	DWORD m_dwLastUpdateTIme;
	float m_fElapsedTime;

public:
	SINGLETONE(TimeManager);

	void Update();
	float GetElapsedTime();
	float GetLastUpdateTime();
};

