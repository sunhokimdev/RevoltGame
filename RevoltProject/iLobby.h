#pragma once

class UIObject;

//===================================================================
// - written by 김선호
// - 모든 UI가 상속받는 기본 UI 클래스
//===================================================================

class iLobby
{
protected:
	UIObject* m_pRootUI;
public:
	iLobby();
	virtual ~iLobby();

	static LOBBY* m_gLobbyState;

	UIObject* GetUIRoot() { return m_pRootUI; }

	virtual void Setup();
	virtual void Update();
	virtual void Render(LPD3DXSPRITE pSprite);
};

