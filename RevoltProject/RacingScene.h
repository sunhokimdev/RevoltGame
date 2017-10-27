#pragma once
#include "GameNode.h"

class cTrack;

class RacingScene : public GameNode
{
private:

	cTrack* m_pTrack;

public:
	RacingScene();
	~RacingScene();

	void Setup();
	void Destroy();
	void Update();
	void Render();
	
};

