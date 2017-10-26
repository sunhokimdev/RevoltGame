#pragma once
#include "Object.h"
#include "Thing.h"

class cTrack :
	public Object
{
public:
	cTrack();
	~cTrack();
public:
	LPD3DXMESH				m_pObjMesh;		// 맵의 메쉬를 저장하는 멤버 변수
	std::vector<MtlTex*>	m_vecObjMtlTex;	// 오브젝트의 매터리얼를 저장하는 멤버 변수
	std::vector<Thing*>		m_vecThing;		// 오브젝트를 관리하기 위한 벡터 변수
	std::vector<Object*>	m_vecObject;


	void Update()
	{

		for (int i = 0; i < m_vecThing.size(); i++)
		{
			m_vecThing[i]->Update();
		}

		for each(Object* pObj in m_vecObject)
		{
			pObj->Update();
		}
	}

};

