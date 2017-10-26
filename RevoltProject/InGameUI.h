#pragma once

#include "RevoltUIObject.h"

class UIObject;
class UITextImageView;
class UIImageView;

//===================================================================
// - written by 김선호
// - 자동차가 달리는 인게임 내의 클래스 구현
// - 인게임의 이 UI가 실행이 된다.
//===================================================================

class InGameUI : public RevoltUIObject
{
private:
	UIObject*		m_pRootUI;
	UIImageView*	m_pItemImage;

	LOBBY*			m_pLobby;
public:
	InGameUI();
	virtual ~InGameUI();

	virtual void Setup();
	virtual void Update();
	virtual void Render(LPD3DXSPRITE pSprite);

	UIObject* GetUIObject() { return m_pRootUI; }
	void SetLobby(LOBBY* lobby) { m_pLobby = lobby; }
};

