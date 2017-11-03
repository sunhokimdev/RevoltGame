#pragma once
#include "Object.h"
class cPickUp :
	public Object
{
public:
	cPickUp();
	~cPickUp();

	int m_nLightIndex;
	bool m_isExist;
	float m_fRespawnTime;
	bool m_isTimerRoll;

	void Update();
	void Render();
};

