#pragma once

#define g_pTimeManager TimeManager::GetInstance()

class TimeManager
{
private:
	DWORD m_dwLastUpdateTIme;
	float m_fElapsedTime;
	float m_fWorldTime;

public:
	SINGLETONE(TimeManager);

	void Setup();
	void Update();
	void Render();

	float GetElapsedTime();
	float GetLastUpdateTime();

	inline float GetWorldTime() { return m_fWorldTime; }
};

