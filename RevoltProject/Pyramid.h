#pragma once
class Pyramid
{
public:
	Pyramid();
	~Pyramid();

	void Setup(D3DXCOLOR c, D3DXMATRIXA16& mat);
	void Render();
private:
	int						m_nNumTri;
	LPDIRECT3DVERTEXBUFFER9	m_pVB;

	D3DXMATRIXA16				m_matR;
	D3DMATERIAL9				m_stMtl;
};

