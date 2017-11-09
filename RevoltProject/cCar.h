#pragma once
#include "Object.h"

class cAI;
class TriggerCallback;
class cTrack;
class cSkidMark;
class InGameUI;

struct stCARSPEC
{
	std::vector<NxBoxShapeDesc> vecBoxDesc;
	std::vector<D3DXVECTOR3> vecWheelPos;
};

class cCar : public Object
{
	ST_KEYSET m_keySet;
public:
	std::bitset<BITESET_8_SIZE> INPUT_KEY;
private:
	//바퀴 매쉬용 백터
	std::vector<cMesh*> vecWheels;

	//자동차 능력치 관련
	NxVehicle* m_carNxVehicle;

	//float m_moterPower;		
	SYNTHESIZE(float, m_moterPower, MoterPower); // 현재 모터 파워 0~1 비율값
	float m_maxMoterPower;	// 최대 파워값
	float m_moterAcc;		// 가속 0~1

	float m_maxRpm;
	float m_breakPower;		// 손을 때고 있으면 자동으로 걸리게 한다.

	//float m_wheelAngle;		
	SYNTHESIZE(float, m_wheelAngle, WheelAngle); //바퀴가 꺾인 정도. (비울) 
	float m_maxWheelAngle;	//바퀴가 꺽이는 최대값. 
	float m_wheelAcc;		//꺽이는 속도	(비율에 더해지는 값)

	//속도 계산
	SYNTHESIZE(float, m_fCurrentSpeed, CurrentSpeed);
	D3DXVECTOR3 m_szPrevPos[5];

	SYNTHESIZE(D3DXMATRIX, m_matCarRotation, CarRotMatrix); // 자동차 전용 정확한 회전 매트릭스

	//자동차 뒤집힘?
	bool isFliping;

	//AI
	std::vector<cAI*> m_vecAI;
	bool m_isAI = false;

	//Track 정보
	cTrack* m_pTrack;
	SYNTHESIZE(int, m_currCheckBoxID, CurrCheckBoxID);			//최근에 체크된 박스
	SYNTHESIZE(int, m_nextCheckBoxID, NextCheckBoxID);			//드음에 체크할 박스
	SYNTHESIZE(int, m_countRapNum, CountRapNum);				//돈 바퀴수

	SYNTHESIZE(float, m_rapTimeCount, RapTimeCount);			//현제 렙 시간
	SYNTHESIZE(float, m_bastRapTimeCount, BastRapTimeCount);	//가장 짭은 랩 시간
	SYNTHESIZE(float, m_totlaTimeCount, TotlaTimeCount);		//총 경과된 랩 시간

	//Item 관련
	SYNTHESIZE(eITEM_LIST, m_eHoldItem, HoldItem);
	SYNTHESIZE(int, m_nItemCount, ItemCount);

	cSkidMark* m_pSkidMark;

	//InGame UI
	InGameUI* m_pInGameUI;

public:
	cCar();
	~cCar();

	void SetNxVehicle(NxVehicle* pVehicle) { m_carNxVehicle = pVehicle; }
	NxVehicle* GetNxVehicle() { return m_carNxVehicle; }

	void LoadCar(std::string carName);
	void SetCarValue(float maxRpm, float moterPower, float moterAcc, float breakPower, float wheelAngle, float wheelAcc, bool isAI = false);
	void SetAI(bool isAI);
	void CreateItem();

	void CreatePhsyX(stCARSPEC carspec);
	void LoadMesh(std::string carName);
	void LoadWheel(std::string carName);

	void Update();
	void LastUpdate();
	void Render();
	void Destory();


	void CtrlPlayer();
	void CtrlAI();

	float GetRpm();

	void TrackCheck();
	void RunEnd();
	void CarRunStop();
	void DrawSkidMark();
	void LinkTrackPt(cTrack* track) { m_pTrack = track; }
	eITEM_LIST* GetHoldItemPt() { return &m_eHoldItem; }
	void LinkUI(InGameUI* ingameUi) { m_pInGameUI = ingameUi; }
	//	void RunStart();

	void SpeedMath();
	void CreateSkidMark();
	void CollidePickUp();
	void SettingCarPos();

	void CarMove();
	void UsedItem();
	void RePosition();
	void CarFlip();

	/*   김선호   */
	void SetResetNetworkKey();
	void SetNetworkKey(std::string);

	SYNTHESIZE(bool, m_isUser, IsUser);
	//e
	NxVec3 CarArrow(float radianAngle = 0);
	NxVec3 WheelArrow(float degAngle = 0 , bool back = false);
};