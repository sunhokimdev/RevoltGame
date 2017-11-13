#pragma once

#include "iLobby.h"

class UIObject;
class UITextImageView;
class UIImageView;
class cNetwork;

class cNetworkLobby : public iLobby
{
private:
	UITextImageView* m_pUserName;
	UITextImageView* m_pCarName;
	UITextImageView* pImageView4;
	UITextImageView* pImageView8;
	UITextImageView* pImageView9;
	UITextImageView* pImageView10;
	UIImageView*	 pImageView1;
	UIImageView*	 pImageView2;
	UIImageView*	 pImageView3;
	UIImageView*	 pImageView5;
	UIImageView*	 pImageView6;
	UIImageView*	 pImageView7;


public:
	cNetworkLobby();
	virtual ~cNetworkLobby();

	/*   기본 루트 메서드   */
	virtual void Setup();
	virtual void Update();
	virtual void Render(LPD3DXSPRITE pSprite);
	virtual void Destroy();

	/*   유저 이름, 자동차 이름 셋업   */
	void SetUserName(std::string Name);
	void SetCarName(std::string pName);
	std::string GetName();
};

// ChatClient.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

