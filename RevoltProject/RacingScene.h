#pragma once
#include "GameNode.h"

class cTrack;
class cLight;
class cCar;


class RacingScene : public GameNode
{
private:

	cTrack* m_pTrack;
	std::vector<cCar*> vecCars;

	cLight* m_pLightSun;
	int m_nLightIDCount;

	//
	D3DXVECTOR3* camPos = new D3DXVECTOR3(0, 10, 0);
	D3DXVECTOR3* camLookTarget = new D3DXVECTOR3(0, 0, 0);

public:

	RacingScene();
	~RacingScene();

	void Setup();
	void Destroy();
	void Update();
	void Render();
	void LastUpdate();
	void UpdateCamera();
};

