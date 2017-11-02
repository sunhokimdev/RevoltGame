#pragma once
#include "Object.h"

class cWheel;
enum cWheel_ID
{
	fl,	//자동차 바퀴 위치
	fr,	//
	bl,	//
	br,	//
};

class cCar :public Object
{
	NxVehicle* m_carNxVehicle;

	std::vector<Object*> vecWheels;

	float m_moterPower;		// 현재 모터 파워 0~1 비율값
	float m_maxMoterPower;	// 최대 파워값
	float m_moterAcc;		// 가속 0~1

	float m_maxRpm;
	float m_breakPower;		// 손을 때고 있으면 자동으로 걸리게 한다.

	float m_wheelAngle;		//바퀴가 꺽인 정도. (비울) 
	float m_maxWheelAngle;	//바퀴가 꺽이는 최대값. 
	float m_wheelAcc;		//꺽이는 속도	(비율에 더해지는 값)


public:
	cCar();
	~cCar();

	void SetNxVehicle(NxVehicle* pVehicle) { m_carNxVehicle = pVehicle; }
	NxVehicle* GetNxVehicle() { return m_carNxVehicle; }

	void SetCarValue(float maxRpm, float moterPower, float moterAcc, float breakPower, float wheelAngle, float wheelAcc);
	void CreatePhsyX();
	void LoadMesh(std::string carName);

	void Update();
	void LastUpdate();
	void Render();
	void Destory();

};

