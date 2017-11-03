#pragma once
class cImpact
{
protected:
	D3DXVECTOR3 m_itemPos;						// 아이템 위치
public:
	cImpact();
	virtual ~cImpact();

	virtual void Setup();
	virtual void Update();
	virtual void Render();
	void SetPosition(D3DXVECTOR3 pos) { 
		m_itemPos = pos;
	};
	DWORD FtoDw(float f)
	{
		return *((DWORD*)&f);
	}
	SYNTHESIZE(bool, m_isUse, IsUse);
	SYNTHESIZE(int, nAlpha, Alpha);
	SYNTHESIZE(int, nDelta, Delta);
};

