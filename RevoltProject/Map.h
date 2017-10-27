#pragma once

class MtlTex;
class Thing;

class cTrack;


//===================================================================
// - ## 10.15.20 ##
// - written by 김선호
// - 맵을 관리하는 맵 클래스 추가
//===================================================================


class Map
{
private:
	int m_stage;

	std::vector<std::string> m_vecMapName;		// 맵 이름을 저장하는 벡터 변수

	//Front 전용 맵
	LPD3DXMESH				m_pObjMesh;
	std::vector<MtlTex*>	m_vecObjMtlTex;
	std::vector<Thing*>		m_vecThing;

	cTrack* m_map;				

	//트랙 전용 맵
	std::map<int, cTrack*> m_track;

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

