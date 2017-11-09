#pragma once
#include "cPhysX.h"
#include "cPlayerData.h"

class cCar;

enum AI_TAG
{
	AI_TAG_MASTER = 0,
	AI_TAG_SPEED,
	AI_TAG_HANDLE,
	AI_TAG_03,
	AI_TAG_04,
	AI_TAG_05,
};

class cAI
{
public:
	AI_TAG AITag;

	cCar* m_pAICar;
	NxActor* m_pAICarActor;

	std::vector<cAI*> chiledAI;

	ID3DXMesh* pMesh;

	cAI();
	~cAI();

	virtual void SetCar(cCar* m_pAICar);
	virtual void Destory();
	virtual void Update();
	virtual void Render();
	virtual void AddAICtrl(cAI* pAI);

	void TEST()
	{

	}

	void SetBitKey(eBIT_KEY keySet, bool onoff);
	bool GetBytKey(eBIT_KEY keyGet);


	void RayHitPos(NxRaycastHit* Ray, D3DXVECTOR3* pos);
	void RayHitDist(NxRaycastHit* Ray, float* dist);

};

