#pragma once
#include "Object.h"

class UIObject : public Object
{
protected:
	std::vector<UIObject*>		m_vecChild;
	D3DXMATRIXA16				m_matWorld;
	SYNTHESIZE(D3DXVECTOR3, m_vPosition, Position);
	SYNTHESIZE(UIObject*, m_pParent, Parent);
	SYNTHESIZE(ST_SIZE, m_stSize, Size);
	SYNTHESIZE(int, m_nTag, Tag);

	bool m_isHidden;
public:
	UIObject();
	virtual ~UIObject();

	virtual void SetPosition(float x, float y, float z = 0);
	virtual void AddChild(UIObject* pChild);
	virtual void Update();
	virtual void Render(LPD3DXSPRITE pSprite);
	virtual void Destroy();
	virtual UIObject* FindChildByTag(int nTag);
};

