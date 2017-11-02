#pragma once
class cImpact
{
private:
	IDirect3DVertexBuffer9* VB;
	D3DXMATRIXA16	m_matWorld;
	D3DXVECTOR3 m_itemPos;
	std::vector<ST_PC_VERTEX>m_vecParticleVertex;
public:
	cImpact();
	~cImpact();

	void Setup();
	void Update();
	void Render();
	void SetPosition(D3DXVECTOR3 pos) { m_itemPos = pos; };
	DWORD FtoDw(float f)
	{
		return *((DWORD*)&f);
	}
	SYNTHESIZE(bool, m_isUse, IsUse);
	SYNTHESIZE(int, nAlpha, Alpha);
	SYNTHESIZE(int, nDelta, Delta);
};

