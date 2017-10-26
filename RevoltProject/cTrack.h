#pragma once
#include "Object.h"
#include "Thing.h"

class cTrack : public Object
{
public:
	cTrack();
	~cTrack();
public:
	int trackNum = 0;
	//인게임 에 들어갈 장애물 등등
	//인게임 에 들어갈 장애물 등등
	std::vector<Object*>	m_vecObject;

	void Update();
	void Render();
};

