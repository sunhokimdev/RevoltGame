#pragma once
#include "cAI.h"
class cAI_CtrlUseItem :
	public cAI
{
public:
	cAI_CtrlUseItem();
	~cAI_CtrlUseItem();
	bool m_isFire;
	void Update();
	void Render();
};

