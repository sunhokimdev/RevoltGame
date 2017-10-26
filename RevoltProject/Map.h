#pragma once

class MtlTex;
class Thing;

//===================================================================
// - ## 10.15.20 ##
// - written by 김선호
// - 맵을 관리하는 맵 클래스 추가
//===================================================================

class Map
{
private:
	int m_stage;
	std::vector<std::string> m_vecMapName;							// 맵 이름을 저장하는 벡터 변수
	std::map<int, ST_MAP*> m_map;		// 맵이랑 오브젝트를 관리하는 STL 변수

public:
	Map();
	~Map();

	static LOBBY* g_LobbyState;

	/*   기본 셋팅 맵 메서드   */
	void Setup();
	void Update();
	void Render();

	void SetupThing();
};

