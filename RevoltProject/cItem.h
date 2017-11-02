#pragma once

#include "Object.h"

class cItem : public Object
{
private:
	int m_id;
public:
	cItem();
	virtual ~cItem();

	virtual void Setup();
	virtual void Update();
	virtual void Render();
	virtual void Create();

	void SetActorGroup(NxActor * actor, NxCollisionGroup group);
};

