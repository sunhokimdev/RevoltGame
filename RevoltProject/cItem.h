#pragma once

#include "Object.h"

class cItem : public Object
{
private:
	int m_id;

public:
	cItem();
	virtual ~cItem();

	virtual void Setup();
	virtual void Update();
	virtual void Render();

protected:
	LPD3DXMESH				m_pObjMesh;		// 오브젝트를 그릴 메쉬 변수
	std::vector<MtlTex*>		m_vecObjMtlTex;	// 오브젝트의 매터리얼를 저장하는 변수
	std::vector<Thing*>		 m_vecChild;					// 자식 노드들

};

