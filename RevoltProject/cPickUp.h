#pragma once
#include "Object.h"
class cPickUp :
	public Object
{
public:
	cPickUp();
	~cPickUp();

	int m_nLightIndex;

	void Update();
};

