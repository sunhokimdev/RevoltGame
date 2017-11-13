#pragma once
#include "Thing.h"

#define SELECT_YANGLE 3.7f

class WheelTire : public Thing
{
public:
	static float g_xRotAngle;		// 로비에서 왼,오른쪽 키 눌렀을 시 회전값

	WheelTire();
	virtual ~WheelTire();

	virtual void Setup();
	virtual void Update();
	virtual void Render();
	virtual void Destroy();
};

