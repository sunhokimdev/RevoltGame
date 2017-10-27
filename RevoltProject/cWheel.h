#pragma once
#include "Object.h"
class cCar;
class cWheel : public Object
{
	// 등록된 자동차를 기준하로 하는 로컬값을 저장할 것.

	cCar* m_body;

public:
	cWheel();
	~cWheel();
	void SetBody(cCar* body);
};

