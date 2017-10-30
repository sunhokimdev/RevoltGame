#pragma once

#include "iLobby.h"

class UIObject;
class UITextImageView;
class UIImageView;

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

	float m_ElapseTime;						// Elase(x.xx0)
	int m_DotTenth;							//		 x.x0x
	int m_DotMilth;							//		 x.0xx
											
	int m_SecOneth;							//		 0.xxx
	int m_SecTenth;							//		0x.xxx
	int	m_MinOneth;							//	  0.xx.xxx
	int	m_MinTenth;							//	 0x.xx.xxx
						
	int m_SecColon;
	int m_MinColon;

	UITextImageView* m_pElapseTime;   
	UITextImageView* m_pDotTenth;	  
	UITextImageView* m_pDotMilth;	  

	UITextImageView* m_pSecOneth;	  
	UITextImageView* m_pSecTenth;	  

	UITextImageView* m_pMinOneth;	  
	UITextImageView* m_pMinTenth;	  

public:
	InGameUI();
	virtual ~InGameUI();

	virtual void Setup();
	virtual void Update();
	virtual void Render(LPD3DXSPRITE pSprite);
	UIObject* GetUIObject() { return m_pRootUI; }
	void SetLobby(LOBBY* lobby) { m_pLobby = lobby; }
	void UpdateTimeLab();

};

