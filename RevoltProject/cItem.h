#pragma once

#include "Object.h"

class cItem : public Object
{
protected:
	LPD3DXMESH					m_pObjMesh;				// 오브젝트를 그릴 메쉬 변수
	std::vector<MtlTex*>		m_vecObjMtlTex;			// 오브젝트의 매터리얼를 저장하는 변수
	
	std::vector<cItem*>			m_vecChild;				// 자식 노드들
	
	D3DXMATRIXA16				m_matWorld;

public:
	cItem();
	~cItem();

	virtual void Setup() = 0;
	virtual void Update();
	virtual void Render();

	void AddChild(cItem* child);

	SYNTHESIZE(cItem*, m_pParent, Parent);
};

