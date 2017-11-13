#pragma once
#include "Object.h"
class cCheckBox :
	public Object
{
	SYNTHESIZE(cCheckBox*, m_nextCheckBox, NextCheckBox);
public:
	cCheckBox();
	~cCheckBox();

	D3DXVECTOR3 ToNextCheckBoxDir();
//	void Update();
};

