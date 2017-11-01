#pragma once

class cImpact;
#define g_pImpactManager cImapactManager::GetInstance()

class cImapactManager
{
private:
	std::vector<cImpact*> m_vecImpact;
public:
	SINGLETONE(cImapactManager);
};

