#pragma once
#include "cPhysX.h"
#include "cPlayerData.h"

class cCar;
class cCheckBox;

enum AI_TAG
{
	AI_TAG_NONE = -1,
	AI_TAG_RAY = 0,
	AI_TAG_SPEED,
	AI_TAG_HANDLE,
	AI_TAG_FLIP,
	AI_TAG_CTRL,
	AI_TAG_END___,
	AI_TAG_05,
};

struct AI_DATA
{
	cCar* pCar;
	AI_DATA()
	{
		pCar = NULL;
	}
	AI_DATA(cCar* pCar)
	{
		if (pCar) this->pCar = pCar;
	}

	void Destory()
	{
		pCar = NULL;
	}
};

class cAI
{
protected:
	ID3DXMesh* AI_Mesh;

	AI_DATA AI_Data;
	cAI();
	~cAI();
	
public:

	std::vector<cAI*>* familyAI;

	virtual void Setup();
	virtual void Destory();
	virtual void Update();
	virtual void Render();

	cCheckBox* CurrentCheckBox();
	float ScaleValue(float value, float Total, float multiValue = 1.0f);

};

