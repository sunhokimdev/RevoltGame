#pragma once

#include "iLobby.h"

class cIntroLob : public iLobby
{
public:
	cIntroLob();
	virtual ~cIntroLob();

	virtual void Setup();
	virtual void Update();
	virtual void Render(LPD3DXSPRITE pSprite);
	virtual void Destroy();
};

