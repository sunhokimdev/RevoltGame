#pragma once
#include "Object.h"
class cSkyBox :	public Object
{
public:
	cSkyBox();
	~cSkyBox();

	void Setup(std::string folder, std::string fileName);
	void Update();
	void Destroy();
	void Render();
};

