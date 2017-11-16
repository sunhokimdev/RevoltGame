#pragma once
#include "cAI.h"

class cPickUp;

class cAI_CtrlCompete :
	public cAI
{
public:
	D3DXVECTOR3 POS_ITEMPOS;
	D3DXVECTOR3 POS_THISPOSDIR;
	D3DXVECTOR3 POS_CARPOSDIR;

	float maxDistance;
	
	cPickUp* closePickup;
	float HandleValue;


	float PickupAngle;

	float PickupValue;
	float CarsValue;

	//다른차와 경쟁하려는 수치값
	//높을 수록 아이템을 먹으로 가거나 
	//다른 차를 피하지 않으려 한다.
	//0~1;
	float Competitive;


	cAI_CtrlCompete();
	~cAI_CtrlCompete();

	void Update();
	void Render();
};