#pragma once

#include "iLobby.h"

class UITextImageView;

class cCreateProfile : public iLobby
{
private:
	UITextImageView* m_pNameText;
public:
	cCreateProfile();
	virtual ~cCreateProfile();

	virtual void Setup();
	virtual void Update();
	virtual void Render(LPD3DXSPRITE pSprite);
	virtual void Destroy();

	std::string GetName();
};

