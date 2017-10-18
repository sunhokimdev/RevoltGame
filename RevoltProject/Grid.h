#pragma once

class Pyramid;

class Grid
{
public:
	Grid();
	~Grid();

	void Setup(int nNumHalfTile = 15, float fInterval = 1.0f);
	void Render();
private:
	std::vector<Pyramid*>		m_vecPyramid;

	int						m_nNumLine;
	LPDIRECT3DVERTEXBUFFER9	m_pVB;
};

