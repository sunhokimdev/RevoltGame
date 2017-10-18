#pragma once
#include "UIObject.h"

class UITextChating : public UIObject
{
private:
	bool							m_isLButtonDown;
	LPDIRECT3DTEXTURE9	m_aTexture;
	ST_SIZE						m_stSize;
public:
	UITextChating();
	virtual ~UITextChating();
	virtual void Update();
	virtual void Render(LPD3DXSPRITE pSprite);

	void SetTexture(char* szFile);

	SYNTHESIZE(FontManager::eFontType, m_eFontType, FontType);
	SYNTHESIZE(std::string, m_sText, Text);
	SYNTHESIZE(DWORD, m_dwDrawTextFormat, DrawTextFormat);
	SYNTHESIZE(D3DCOLOR, m_dwTextColor, TextColor);
};

