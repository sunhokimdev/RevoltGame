#pragma once

struct ST_TEXT
{
	D3DXVECTOR3		pos;
	std::string			name;
};

class TextLoader
{
private:
	std::vector<ST_TEXT*> vecText;
public:
	TextLoader();
	~TextLoader();

	void LanguageTextLoad(OUT std::vector<std::string>& vecString,IN char * szFolder, IN char * szFile);
};

