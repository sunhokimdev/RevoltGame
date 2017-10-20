#pragma once

class MtlTex;
class Thing;

struct ST_MAP
{
	LPD3DXMESH				m_pObjMesh;		// 맵의 메쉬를 저장하는 멤버 변수
	std::vector<MtlTex*>		m_vecObjMtlTex;	// 오브젝트의 매터리얼를 저장하는 멤버 변수
	std::vector<Thing*>		m_vecThing;			
};

class Map
{
private:
	int m_stage;
	std::map<int, ST_MAP*> m_map;
public:
	Map();
	~Map();

	static LOBBY g_LobbyState;

	/*   기본 셋팅 맵 메서드   */
	void Setup();
	void Update();
	void Render();

	void SetupThing();
};

