#pragma once
class SkidMarks
{
private:
	LPDIRECT3DTEXTURE9		m_pTexture;
	D3DMATERIAL9		   m_stMtlPlane;
	std::vector<ST_PN_VERTEX> m_vecPlaneVertex;

public:
	SkidMarks();
	~SkidMarks();

	void Setup();
	void Update();
	void Render();
};

