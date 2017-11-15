#pragma once
#include "cPhysX.h"
#include "cPlayerData.h"

class cCar;
class cTrack;
class cCheckBox;

enum AI_TAG
{
	AI_TAG_NONE = -1,
	AI_TAG_RAY = 0,
	AI_TAG_SPEED,
	AI_TAG_HANDLE,
	AI_TAG_FLIP,
	AI_TAG_COMPET,
	AI_TAG_USEITEM,

	AI_TAG_CTRL,
	AI_TAG_END___,
	AI_TAG_05,
};

struct AI_DATA
{
	cCar* pCar;
	cTrack* pTrack;
	std::vector<cCar*>* pCars;

	AI_DATA()
	{
		pCar = NULL;
		pTrack = NULL;
		pCars = NULL;
	}
	AI_DATA(cCar* pCar, cTrack* pTrack, std::vector<cCar*>* pCars);
	void Destroy()
	{
		pCar = NULL;
		pTrack = NULL;
		pCars = NULL;
	}
};

class cAI
{
public:
	ID3DXMesh* AI_Mesh;
	AI_DATA* AI_Data;
	std::vector<cAI*>* familyAI;

	cAI();
	~cAI();

public:
	virtual void Setup();
	virtual void Destroy();
	virtual void Update();
	virtual void Render();

	cCheckBox* CurrentCheckBox();
	float ScaleValue(float value, float Total, float multiValue = 1.0f);
	float GetRpmRate();
};

