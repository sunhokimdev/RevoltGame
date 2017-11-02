#pragma once

#include "cItem.h"

class cFirework : public cItem
{
private:
	std::vector<ST_PHYSX*>	m_vecPhysX;
public:
	cFirework();
	virtual ~cFirework();

	virtual void Setup();
	virtual void Update();
	virtual void Render();
	virtual void Create();
};

