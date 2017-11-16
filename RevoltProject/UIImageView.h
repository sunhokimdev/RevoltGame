#pragma once
#include "UIObject.h"

#define MAX_ID 11

class UIImageView : public UIObject
{
protected:


	/*   아이템 창 뜨게 하기 위한 작업   */
	int m_itemPrevID;	// 아이템의 이전 아이디
	int m_itemID;		// 아이템의 현재 아이디
	int* m_pitemID;     // 아이템 아이디 포인터
	int m_alpha;			// 알파 값 적용시켜주기
	int m_fTime;			// 알파 값 갱신 해주기 위한 시간 값
	int m_updateTIme;

	/*	속도계	*/
	int m_speedAlpha[7];
	int m_alphaValue;		// 알파값 변경
	int m_Rpm;

	float m_fArrowAngle;

	LPDIRECT3DTEXTURE9		m_pTexture;			// 이미지 그리기 작업

	cCar* m_pCar;

public:
	UIImageView();
	virtual ~UIImageView();
	virtual void SetTexture(char* szFullPath);
	virtual void Update();
	virtual void Render(LPD3DXSPRITE pSprite) override;

	void SetRpmGauge(int rpm) { m_Rpm = rpm; }
	void SetArrowAngle(float angle) { m_fArrowAngle = angle; }

	void LinkItemIDPt(int* item) { m_pitemID = item; }
	void LinkCarPt(cCar* car) { m_pCar = car; }

	SYNTHESIZE(bool, m_isBoard, IsBoard);		
	SYNTHESIZE(bool, m_isItem, IsItem);
	SYNTHESIZE(bool, m_isSpeedFrame, IsSpeedFrame);
	SYNTHESIZE(bool, m_isSpeed, IsSpeed);
	SYNTHESIZE(bool, m_isArrowDir, IsArrowDir);
	SYNTHESIZE(bool, m_isFrameRender, FrameRender);
	SYNTHESIZE(bool, m_isBomb, Bomb);
	SYNTHESIZE(float, m_xSize, XSize);
	SYNTHESIZE(float, m_ySize, YSize);
	SYNTHESIZE(D3DXCOLOR, m_color, Color);

};

