#pragma once

#include "iLobby.h"

class UITextImageView;
class UIImageView;

class cCreateProfile : public iLobby
{
private:
	UITextImageView* m_pNameText;
	UITextImageView* m_pTIV_CP_BodyFont;
	UITextImageView* m_pTIV_CP_HeadFont;
	UIImageView*	 m_pIV_CP_BodyRing;
	UIImageView*	 m_pIV_CP_BlueRing;
	UIImageView*	 m_pIV_CP_HeadRing;
	UIImageView*	 m_pIV_CP_BlueToy;



public:
	cCreateProfile();
	virtual ~cCreateProfile();

	virtual void Setup();
	virtual void Update();
	virtual void Render(LPD3DXSPRITE pSprite);
	virtual void Destroy();

	std::string GetName();
};

