#pragma once

#include "iLobby.h"

class UIImageView;
class UITextImageView;

class cViewCarLob : public iLobby
{
private :
	UIImageView*		 pImageView1;
	UIImageView*		 pImageView2;
	UIImageView*		 pImageView3;
	UITextImageView*	 pImageView4;

public:
	cViewCarLob();
	virtual ~cViewCarLob();

	virtual void Setup();
	virtual void Update();
	virtual void Render(LPD3DXSPRITE pSprite);
	virtual void Destroy();

	SYNTHESIZE(bool, m_isNetwork, IsNetwork); // 멀티 플레이 게임이라면
};

