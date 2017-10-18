#pragma once
#include "UIObject.h"
#include "FontManager.h"

class UITextView : public UIObject
{
public:
	UITextView();
	virtual ~UITextView();

	virtual void Render(LPD3DXSPRITE pSprite) override;
protected:
	SYNTHESIZE(FontManager::eFontType, m_eFontType, FontType);
	SYNTHESIZE(std::string, m_sText, Text);
	SYNTHESIZE(DWORD, m_dwDrawTextFormat, DrawTextFormat);
	SYNTHESIZE(D3DCOLOR, m_dwTextColor, TextColor);
};

