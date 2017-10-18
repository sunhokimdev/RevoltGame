#pragma once

#define g_pFontManager FontManager::GetInstance()

class FontManager
{
public:
	SINGLETONE(FontManager);
	enum eFontType
	{
		E_DEFAULT,
		E_QUEST,
	};
	LPD3DXFONT GetFont(eFontType e);
	void Destroy();
private:
	std::map<eFontType, LPD3DXFONT> m_mapFont;
};

