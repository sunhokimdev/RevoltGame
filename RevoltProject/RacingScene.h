#pragma once
#include "GameNode.h"

class cFirework;
class cTrack;
class cLight;
class cCar;
class InGameUI;
class cSkyBox;

enum eRACE_PROG
{
	RACE_PROG_READY, // 준비
	RACE_PROG_SET, // 프리카운트 321go
	RACE_PROG_GO, // 경기중
	RACE_PROG_FINISH // 경기끝
};

class RacingScene : public GameNode
{
private:
	int playerIndex;

	InGameUI* m_pInGameUI;
	cTrack* m_pTrack;

	std::vector<cCar*> vecCars;

	cLight* m_pLightSun;
	int m_nLightIDCount;
	
	int m_select;
	//
	D3DXVECTOR3* m_camPos;
	D3DXVECTOR3* m_camLookTarget;

	//TrackEndCount 돌아야 되는 바퀴 수	
	SYNTHESIZE(int, m_trackEndCount, trackEndCount);
	
	//빌보드??이펙트??
	LPD3DXSPRITE m_Sprite;

	bool m_isDrift;
	bool m_isPlayBGM;

	cSkyBox* m_pSkyBox;

	SYNTHESIZE(eRACE_PROG, m_eRaceProg, RaceProg);

public:

	RacingScene();
	~RacingScene();

	void Setup();
	void Destroy();
	void Update();
	void Render();
	void LastUpdate();
	void UpdateCamera();
	void UpdateSound();

	//자동차가 계속 달려야하는지를 체크
	bool IsCarRunTrue(cCar* pCar);


//	void CreateCar(int carId) {}
	void CreateCar(D3DXVECTOR3 setPos, int playerID, std::string userName, std::string carName, int trackEndCount, bool isAI, bool isUser = false);
	//void CreateCar(int playerID, std::string carName);
	void LinkUI(int playerID);
	void FindTarget(cCar* MyCar);

	/*   김선호   */
	void NetworkLoop();			// 네트워크 통신하는 부분
	void SetNetworkCarData();		// 자동차 데이터 세팅하는 메서드
};

