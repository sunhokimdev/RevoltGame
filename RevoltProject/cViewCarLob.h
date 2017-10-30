#pragma once

#include "iLobby.h"

class cViewCarLob : public iLobby
{
public:
	cViewCarLob();
	virtual ~cViewCarLob();

	virtual void Setup();
	virtual void Update();
	virtual void Render(LPD3DXSPRITE pSprite);

	SYNTHESIZE(bool, m_isNetwork, IsNetwork); // 멀티 플레이 게임이라면
};

