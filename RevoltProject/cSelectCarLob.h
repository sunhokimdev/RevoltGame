#pragma once

#include "iLobby.h"

class UITextImageView;

class cSelectCarLob : public iLobby
{
private:
	UITextImageView* m_pCarName;
public:
	cSelectCarLob();
	virtual ~cSelectCarLob();

	virtual void Setup();
	virtual void Update();
	virtual void Render(LPD3DXSPRITE pSprite);

	std::string GetCarName();
};

