#pragma once

#include "iLobby.h"

class UIImageView;
class UITextImageView;

class cNetworkCreateRoom : public iLobby
{
private:
	UIImageView*		m_pMapImage;			// 맵 이미지 설정
	UITextImageView*	m_pMapName;				// 맵 이름 설정
	UITextImageView*	m_pMapDifficult;		// 맵 난이도 설정
	UITextImageView*	m_pMapLength;			// 맵 길이 설정
	UITextImageView*	m_pRoomName;			// 방 이름 설정

	std::vector<std::string>	m_vecMap;		// 맵 이름을 저장하는 변수
public:
	cNetworkCreateRoom();
	virtual ~cNetworkCreateRoom();

	virtual void Setup();
	virtual void Update();
	virtual void Render(LPD3DXSPRITE pSprite);

	std::string GetRoomName();
	std::string GetImageName();
};

