#pragma once

#define g_pTextManager TextManager::GetInstance()

//======================================
// - ## 10.11.17 ##
// - written by 이태섭
// - 텍스트 출력 매니저
//======================================

struct FONT
{
	LPD3DXFONT font;
	D3DXFONT_DESC fd;
};

class TextManager
{
private:
	SINGLETONE(TextManager);

	std::map<std::string, FONT> m_mapFont;

public:
	void WriteText(std::string str, std::string key, float xDest, float yDest, D3DCOLOR color = C_WHITE);
	void AddFont(LPCWSTR fontName, std::string key, int fontSize);
	bool FindFont(std::string key, FONT* font);
};

