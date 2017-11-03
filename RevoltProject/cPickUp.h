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

	void Update();
	void Render();
};

