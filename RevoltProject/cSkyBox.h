#pragma once
#include "Object.h"
class cSkyBox :	public Object
{
public:
	cSkyBox();
	~cSkyBox();

	void Setup();
	void Update();
	void Destroy();
	void Render();
};

