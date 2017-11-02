#pragma once
class cBillBoardEffect
{
private:
	LPDIRECT3DTEXTURE9	m_pTexture;			// 자동차 박스에 입힐 텍스쳐
	LPD3DXMESH				m_pMesh;			// 메쉬 정보
public:
	cBillBoardEffect();
	~cBillBoardEffect();

	void Setup();
	void Update();
	void Render();

	void SetFileTexture(char* szFile);
};

