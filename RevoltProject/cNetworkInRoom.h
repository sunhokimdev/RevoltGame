#pragma once

#include "iLobby.h"

class UIImageView;
class UITextImageView;
class UITextView;

class cNetworkInRoom : public iLobby
{
private:
	UITextImageView*	m_pChating;		// 채팅 구현
	UITextImageView*	m_pText;		// 화면에 보여줄 채팅 내용

	std::vector<UITextImageView*>	m_vecText;		// 화면에 보여줄 채팅 내용
	std::vector<UITextImageView*>	m_vecUser;		// 화면에 보여줄 유저들
	int m_index;
	int m_sizeY;
public:
	cNetworkInRoom();
	virtual ~cNetworkInRoom();

	virtual void Setup();
	virtual void Update();
	virtual void Render(LPD3DXSPRITE pSprite);
	virtual void Destroy();

	std::string GetMsg();
	void SetResetCharText();
	void SetText(std::string str);
	void SetUserText(std::string str, int index, D3DXCOLOR color);
};

