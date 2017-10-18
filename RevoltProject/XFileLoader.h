#pragma once
class XFileLoader
{
private:
	ID3DXMesh* m_pMesh;
	std::vector<D3DMATERIAL9> m_vMaterial;
	std::vector<IDirect3DTexture9*> m_vTexture;
public:
	XFileLoader();
	~XFileLoader();

	void Load(char* szFile);
	void Render();
};

