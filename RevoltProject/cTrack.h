#pragma once
#include "Object.h"
#include "Thing.h"
#include "Camera.h"

#include "cCar.h"


class cTrack : public Object
{
public:
	cTrack();
	~cTrack();
public:
	int trackNum = 0;
	std::string trackName;

	//인게임 에 들어갈 장애물 등등
	std::vector<Object*>	m_vecObject;
	Camera* pCamera;


	cCar* pCar1;
	NxVehicle* pVeh;

	void Update();
	void LastUpdate();
	void Render();

	void SetData();
	void LoadTrack(std::string FileName , Camera* pCam);
	void CreateTrackPhysX();
};

