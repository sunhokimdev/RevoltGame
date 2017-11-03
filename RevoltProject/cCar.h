#pragma once
#include "Object.h"

class cAI;
class TriggerCallback;

struct stCARSPEC
{
	std::vector<NxBoxShapeDesc> vecBoxDesc;
	std::vector<D3DXVECTOR3> vecWheelPos;
};

class cCar : public Object
{
	//자동차 능력치 관련
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

	float m_fCurrentSpeed;
	D3DXVECTOR3 m_szPrevPos[5];

	//AI
	std::vector<cAI*> m_vecAI;
	bool m_isAI = false;

	//track 관련
	bool m_trackOn = true;
	SYNTHESIZE(int, totalCheckBoxNum, TotalCheckBoxNum);
	SYNTHESIZE(int, countChectBox, CountCheckBox);
	SYNTHESIZE(int, countTrack,CountTrackRun);
	
	SYNTHESIZE(float, m_isTimeCount, IsTimeCount);

	//Item 관련
	SYNTHESIZE(eITEM_LIST, m_eHoldItem, HoldItem);
	SYNTHESIZE(int, m_nItemCount, ItemCount);
	
	int countCheckTrack;


public:
	cCar();
	~cCar();

	void SetNxVehicle(NxVehicle* pVehicle) { m_carNxVehicle = pVehicle; }
	NxVehicle* GetNxVehicle() { return m_carNxVehicle; }

	void LoadCar(std::string carName);
	void SetCarValue(float maxRpm, float moterPower, float moterAcc, float breakPower, float wheelAngle, float wheelAcc , bool isAI = false);
	
	void CreateItem();

	void CreatePhsyX(stCARSPEC carspec);
	void LoadMesh(std::string carName);

	void Update();
	void LastUpdate();
	void Render();
	void Destory();


	void CtrlPlayer();
	void CtrlAI();

	void GetRpm();
	void TrackCheck();
	void RunStop();
//	void RunStart();
};