#pragma once

#include "iLobby.h"

class UITextImageView;

class cSelectNetworkLob : public iLobby
{
private:
	UITextImageView* m_pTextIP;
public:
	cSelectNetworkLob();
	virtual ~cSelectNetworkLob();

	virtual void Setup();
	virtual void Update();
	virtual void Render(LPD3DXSPRITE pSprite);

	std::string GetTextIP();
};

