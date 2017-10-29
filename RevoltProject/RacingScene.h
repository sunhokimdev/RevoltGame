#pragma once
#include "GameNode.h"

class cTrack;
class cLight;

class RacingScene : public GameNode
{
private:

	cTrack* m_pTrack;
	cLight* m_pLightSun;

	LPD3DXMESH TestMesh;

public:

	RacingScene();
	~RacingScene();

	void Setup();
	void Destroy();
	void Update();
	void Render();
	
};

