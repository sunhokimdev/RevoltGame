#pragma once

#include "iLobby.h"

class UIObject;
class UITextImageView;
class UIImageView;
class cCar;

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

	//Lab
	int m_Lab;

	//Colon	
	int m_SecColon;							// SecColon		xx:xx
	int m_MinColon;							// MinColon	 xx:xx:xx

	int m_LabSecColon;							// SecColon		xx:xx
	int m_LabMinColon;							// MinColon	 xx:xx:xx


	/*          Timer UiTextImageView          */

	//Lab
	UITextImageView* m_pLab;

	UITextImageView* m_pLabElapseTime;
	UITextImageView* m_pLabDotTenth;
	UITextImageView* m_pLabDotMilth;
	UITextImageView* m_pLabSecOneth;
	UITextImageView* m_pLabSecTenth;
	UITextImageView* m_pLabMinOneth;
	UITextImageView* m_pLabMinTenth;

	UITextImageView* m_pElapseTime;   
	UITextImageView* m_pDotTenth;	  
	UITextImageView* m_pDotMilth;	  
	UITextImageView* m_pSecOneth;	  
	UITextImageView* m_pSecTenth;	  
	UITextImageView* m_pMinOneth;	  
	UITextImageView* m_pMinTenth;	  

	UITextImageView* pSpeed;
	UITextImageView* pSpeed2;
	UIImageView* pSpeedometerImage;
	UIImageView* pIV_arrowDir;

	cCar* m_pCar;

public:
	InGameUI();
	virtual ~InGameUI();

	virtual void Setup();
	virtual void Update();
	virtual void Render(LPD3DXSPRITE pSprite);
	UIObject* GetUIObject() { return m_pRootUI; }
	void SetLobby(LOBBY* lobby) { m_pLobby = lobby; }

	void UpdateSpeed();
	void UpdateRaceTime();									// UpdateTimer
	void UpdateArrowDir();									// 화살표 방향
	void UpdateLapTime();										// void Update
	SYNTHESIZE(int, m_LabCnt, LabCnt);							// Lab Count

																//Lab
	SYNTHESIZE(float, m_LabElapseTime, LabElapseTime);
	SYNTHESIZE(int, m_LabDotTenth, LabDotTenth);
	SYNTHESIZE(int, m_LabDotMilth, LabDotMilth);
	SYNTHESIZE(int, m_LabSecOneth, LabSecOneth);
	SYNTHESIZE(int, m_LabSecTenth, LabSecTenth);
	SYNTHESIZE(int, m_LabMinOneth, LabMinOneth);
	SYNTHESIZE(int, m_LabMinTenth, LabMinTenth);

	//Race
	SYNTHESIZE(float, m_ElapseTime, ElapseTime);
	SYNTHESIZE(int, m_DotTenth, DotTenth);
	SYNTHESIZE(int, m_DotMilth, DotMilth);
	SYNTHESIZE(int, m_SecOneth, SecOneth);
	SYNTHESIZE(int, m_SecTenth, SecTenth);
	SYNTHESIZE(int, m_MinOneth, MinOneth);
	SYNTHESIZE(int, m_MinTenth, MinTenth);

	void LinkCarPt(cCar* car) { m_pCar = car; }

};

