#pragma once

#include "iLobby.h"

class UIObject;
class UITextImageView;
class UIImageView;
class cCar;
class cTrack;
class c321GO;
class RacingScene;

//===================================================================
// - written by 김선호
// - 자동차가 달리는 인게임 내의 클래스 구현
// - 인게임의 이 UI가 실행이 된다.
//===================================================================

class InGameUI : public iLobby
{
private:
	UIImageView*	m_pItemImage;
	LOBBY*			m_pLobby;
	int m_select;
	int m_WorldDotOneth;

	//Lab
	int m_Lab;

	/*          Timer UiTextImageView          */

	//Lab
	UITextImageView* m_pLab;
	UITextImageView* m_pCurrentLab;
	UITextImageView* m_pMaxLab;

	//Last Time
	UITextImageView* m_pLastDotOneTh;
	UITextImageView* m_pLastDotTenth;
	UITextImageView* m_pLastDotMilth;
	UITextImageView* m_pLastSecOneth;
	UITextImageView* m_pLastSecTenth;
	UITextImageView* m_pLastMinOneth;
	UITextImageView* m_pLastMinTenth;


	//Best Time
	UITextImageView* m_pBestDotOneTh;
	UITextImageView* m_pBestDotTenth;
	UITextImageView* m_pBestDotMilth;
	UITextImageView* m_pBestSecOneth;
	UITextImageView* m_pBestSecTenth;
	UITextImageView* m_pBestMinOneth;
	UITextImageView* m_pBestMinTenth;

	//Lab Time
	UITextImageView* m_pLabElapseTime;
	UITextImageView* m_pLabDotTenth;
	UITextImageView* m_pLabDotMilth;
	UITextImageView* m_pLabSecOneth;
	UITextImageView* m_pLabSecTenth;
	UITextImageView* m_pLabMinOneth;
	UITextImageView* m_pLabMinTenth;

	//Race Time
	UITextImageView* m_pElapseTime;
	UITextImageView* m_pDotTenth;
	UITextImageView* m_pDotMilth;
	UITextImageView* m_pSecOneth;
	UITextImageView* m_pSecTenth;
	UITextImageView* m_pMinOneth;
	UITextImageView* m_pMinTenth;

	// 속도계
	UITextImageView* m_pSpeedOne;
	UITextImageView* m_pSpeedTen;
	UITextImageView* m_pSpeedHun;
	UIImageView* m_pSpeedometerImage;

	// 등수, 방향 화살표
	UITextImageView* pITV_Rank;
	UITextImageView* pITV_Rank2;
	UIImageView* pIV_arrowDir;

	//321go
	c321GO* m_p321go;

	int m_arrowIndex;
	cTrack* m_pTrack;
	// 차 정보
	cCar* m_pCar;
	RacingScene* m_pRacingScene;

	// Race Result
	UIImageView* m_pResultRing;
	UITextImageView* m_pRaceResult;

	UITextImageView* m_pFirst;
	UITextImageView* m_pFirstPlayerName;
	UITextImageView* m_pSecond;
	UITextImageView* m_pSndPlayerName;
	UITextImageView* m_pThird;
	UITextImageView* m_pTrdPlayerName;
	UITextImageView* m_pFourth;
	UITextImageView* m_pFourthPlayerName;
	UITextImageView* m_pFifth;
	UITextImageView* m_pFifthPlayerName;
	UITextImageView* m_pSixth;
	UITextImageView* m_pSixthPlayerName;

	//First
	UITextImageView* m_pFirstResultMinTenth;
	UITextImageView* m_pFirstResultMinOneth;
	UITextImageView* m_pFirstResultMinColon;
	UITextImageView* m_pFirstResultSecTenth;
	UITextImageView* m_pFirstResultSecOneth;
	UITextImageView* m_pFirstResultSecColon;
	UITextImageView* m_pFirstResultDotMilth;
	UITextImageView* m_pFirstResultDotTenth;
	UITextImageView* m_pFirstResultDotOneth;

	//Second
	UITextImageView* m_pSndResultMinTenth;
	UITextImageView* m_pSndResultMinOneth;
	UITextImageView* m_pSndResultMinColon;
	UITextImageView* m_pSndResultSecTenth;
	UITextImageView* m_pSndResultSecOneth;
	UITextImageView* m_pSndResultSecColon;
	UITextImageView* m_pSndResultDotMilth;
	UITextImageView* m_pSndResultDotTenth;
	UITextImageView* m_pSndResultDotOneth;

	//Third
	UITextImageView* m_pTrdResultMinTenth;
	UITextImageView* m_pTrdResultMinOneth;
	UITextImageView* m_pTrdResultMinColon;
	UITextImageView* m_pTrdResultSecTenth;
	UITextImageView* m_pTrdResultSecOneth;
	UITextImageView* m_pTrdResultSecColon;
	UITextImageView* m_pTrdResultDotMilth;
	UITextImageView* m_pTrdResultDotTenth;
	UITextImageView* m_pTrdResultDotOneth;

	//Fourth
	UITextImageView* m_pFourthResultMinTenth;
	UITextImageView* m_pFourthResultMinOneth;
	UITextImageView* m_pFourthResultMinColon;
	UITextImageView* m_pFourthResultSecTenth;
	UITextImageView* m_pFourthResultSecOneth;
	UITextImageView* m_pFourthResultSecColon;
	UITextImageView* m_pFourthResultDotMilth;
	UITextImageView* m_pFourthResultDotTenth;
	UITextImageView* m_pFourthResultDotOneth;

	//Fifth
	UITextImageView* m_pFifthResultMinTenth;
	UITextImageView* m_pFifthResultMinOneth;
	UITextImageView* m_pFifthResultMinColon;
	UITextImageView* m_pFifthResultSecTenth;
	UITextImageView* m_pFifthResultSecOneth;
	UITextImageView* m_pFifthResultSecColon;
	UITextImageView* m_pFifthResultDotMilth;
	UITextImageView* m_pFifthResultDotTenth;
	UITextImageView* m_pFifthResultDotOneth;

	//Sixth
	UITextImageView* m_pSixthResultMinTenth;
	UITextImageView* m_pSixthResultMinOneth;
	UITextImageView* m_pSixthResultMinColon;
	UITextImageView* m_pSixthResultSecTenth;
	UITextImageView* m_pSixthResultSecOneth;
	UITextImageView* m_pSixthResultSecColon;
	UITextImageView* m_pSixthResultDotMilth;
	UITextImageView* m_pSixthResultDotTenth;
	UITextImageView* m_pSixthResultDotOneth;

	UITextImageView* m_pSecondRetired;
	UITextImageView* m_pThridRetired;
	UITextImageView* m_pFourthRetired;
	UITextImageView* m_pFifthRetired;
	UITextImageView* m_pSixthRetired;
	/*          SYNTHESIZE          */

	// Lab Count
	SYNTHESIZE(int, m_LabCnt, LabCnt);

	// LastTime
	SYNTHESIZE(int, m_LastDotOneTh, LastDotOneTh);
	SYNTHESIZE(int, m_LastDotTenth, LastDotTenth);
	SYNTHESIZE(int, m_LastDotMilth, LastDotMilth);
	SYNTHESIZE(int, m_LastSecOneth, LastSecOneth);
	SYNTHESIZE(int, m_LastSecTenth, LastSecTenth);
	SYNTHESIZE(int, m_LastMinOneth, LastMinOneth);
	SYNTHESIZE(int, m_LastMinTenth, LastMinTenth);

	// BestTime
	SYNTHESIZE(int, m_BestDotOneTh, BestDotOneTh);
	SYNTHESIZE(int, m_BestDotTenth, BestDotTenth);
	SYNTHESIZE(int, m_BestDotMilth, BestDotMilth);
	SYNTHESIZE(int, m_BestSecOneth, BestSecOneth);
	SYNTHESIZE(int, m_BestSecTenth, BestSecTenth);
	SYNTHESIZE(int, m_BestMinOneth, BestMinOneth);
	SYNTHESIZE(int, m_BestMinTenth, BestMinTenth);

	// Lab
	SYNTHESIZE(float, m_LabElapseTime, LabElapseTime);
	SYNTHESIZE(int, m_LabDotTenth, LabDotTenth);
	SYNTHESIZE(int, m_LabDotMilth, LabDotMilth);
	SYNTHESIZE(int, m_LabSecOneth, LabSecOneth);
	SYNTHESIZE(int, m_LabSecTenth, LabSecTenth);
	SYNTHESIZE(int, m_LabMinOneth, LabMinOneth);
	SYNTHESIZE(int, m_LabMinTenth, LabMinTenth);

	// Race
	SYNTHESIZE(float, m_ElapseTime, ElapseTime);
	SYNTHESIZE(int, m_DotTenth, DotTenth);
	SYNTHESIZE(int, m_DotMilth, DotMilth);
	SYNTHESIZE(int, m_SecOneth, SecOneth);
	SYNTHESIZE(int, m_SecTenth, SecTenth);
	SYNTHESIZE(int, m_MinOneth, MinOneth);
	SYNTHESIZE(int, m_MinTenth, MinTenth);
public:
	InGameUI();
	virtual ~InGameUI();

	virtual void Setup();
	virtual void Update();
	virtual void Render(LPD3DXSPRITE pSprite);
	virtual void Destroy();

	UIObject* GetUIObject() { return m_pRootUI; }
	void SetLobby(LOBBY* lobby) { m_pLobby = lobby; }

	void UpdateSpeed();
	void UpdateLabCount();									// UpdateCurrentLab
	void UpdateLastTime();									// UpdateLastTimer
	void CompareBestTime();									// UpdateBestTimer(Compare BestLab with CurrentLab)
	void UpdateLabTime();									// UpdateLabTimer
	void UpdateRaceTime();									// UpdateRaceTimer
	void UpdateArrowDir();									// 화살표 방향
	void RaceResults();

	void LinkCarPt(cCar* car);
	void LinkTrack(cTrack* track) { m_pTrack = track; }
	void LinkRacingScene(RacingScene* rc) { m_pRacingScene = rc; }
	c321GO* Get321goPt() { return m_p321go; }
};

