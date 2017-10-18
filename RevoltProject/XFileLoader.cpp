#include "stdafx.h"
#include "XFileLoader.h"


XFileLoader::XFileLoader()
{
}


XFileLoader::~XFileLoader()
{
}

void XFileLoader::Load(char * szFile)
{
	ID3DXBuffer* adjBuffer = 0;
	ID3DXBuffer* mtrlBuffer = 0;
	DWORD numMtrls = 0;

	if (FAILED(D3DXLoadMeshFromXA(
		szFile,
		D3DXMESH_MANAGED,
		g_pD3DDevice,
		&adjBuffer,
		&mtrlBuffer,
		0,
		&numMtrls,
		&m_pMesh)))
	{
		MessageBox(g_hWnd, _T("파일을 못 읽었습니다."), _T("앙 기모띠"), MB_OK);
		return;
	}

	if (mtrlBuffer != 0 && numMtrls != 0)
	{
		D3DXMATERIAL* mtrls = (D3DXMATERIAL*)mtrlBuffer->GetBufferPointer();

		for (int i = 0;i < numMtrls;++i)
		{
			mtrls[i].MatD3D.Ambient = mtrls[i].MatD3D.Diffuse;
			m_vMaterial.push_back(mtrls[i].MatD3D);

			if (mtrls[i].pTextureFilename != 0)
			{
				IDirect3DTexture9* nTexture = 0;
				D3DXCreateTextureFromFileA(g_pD3DDevice, mtrls[i].pTextureFilename, &nTexture);
				m_vTexture.push_back(nTexture);
			}
			else
			{
				m_vTexture.push_back(0);
			}
		}

		mtrlBuffer->Release();
	}
}

void XFileLoader::Render()
{
	static float rotY = 0.0f;
	D3DXMATRIXA16 matR;
	D3DXMatrixRotationY(&matR, rotY);

	if (rotY >= 6.28)
		rotY = 0.0f;

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matR);

	for (int i = 0;i < m_vMaterial.size();i++)
	{
		g_pD3DDevice->SetMaterial(&m_vMaterial[i]);
		g_pD3DDevice->SetTexture(0, m_vTexture[i]);
		m_pMesh->DrawSubset(i);
	}
}
