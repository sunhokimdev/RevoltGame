#pragma once

class MtlTex;

class Thing
{
protected:
	LPD3DXMESH				m_pObjMesh;		// 오브젝트를 그리기 위한 Mesh 변수
	std::vector<MtlTex*>	m_vecObjMtlTex;	// 오브젝트의 매터리얼를 저장하는 변수

	std::vector<Thing*> m_vecChild;
	D3DXMATRIXA16		m_matWorld;
	SYNTHESIZE(D3DXVECTOR3, m_vPosition, Position);		// 오브젝트 위치
	SYNTHESIZE(Thing*, m_pParent, Parent);
	SYNTHESIZE(int, m_nTag, Tag);
public:
	Thing();
	virtual ~Thing();

	void Load(char* szFolder, char* szFile);

	virtual void SetPosition(float x, float y, float z);
	virtual void AddChild(Thing* pChild);
	virtual void Update();
	virtual void Render();
	virtual void Destroy();
	virtual Thing* FindChildByTag(int nTag);
};

