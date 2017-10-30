#pragma once
#define g_pLightManager LightManager::GetInstance()

class cLight;

class LightManager
{
	SINGLETONE(LightManager);
	std::map<int, cLight*> m_mapLight;

public:

	void Setup();
	void Update();
	void Destroy();

	void AddLight(int index, cLight* light);
	void DeleteLight(int index);
};

