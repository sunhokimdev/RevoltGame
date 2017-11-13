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
	float m_fAngle;

	void Update();
	void Render();

	bool IsShow() { return m_isExist; }
};

