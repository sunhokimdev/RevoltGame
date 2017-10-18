#include "stdafx.h"
#include "TextureManager.h"


TextureManager::TextureManager()
{
}


TextureManager::~TextureManager()
{
}

LPDIRECT3DTEXTURE9 TextureManager::GetTexture(char * szFullPath)
{
	if (m_mapTexture.find(szFullPath) == m_mapTexture.end())
	{
		HRESULT hok = D3DXCreateTextureFromFileA(g_pD3DDevice,
			szFullPath,
			&m_mapTexture[szFullPath]
			);

		if (FAILED(hok))
			MessageBoxA(g_hWnd, szFullPath, ("asdasd"), MB_OK);
	}
	return m_mapTexture[szFullPath];
}

LPDIRECT3DTEXTURE9 TextureManager::GetTexture(std::string & sFullPath)
{
	return GetTexture((char*)sFullPath.c_str());
}

LPDIRECT3DTEXTURE9 TextureManager::GetTexture(char * szFullPath, D3DXIMAGE_INFO * pImageInfo)
{
	if (m_mapTexture.find(szFullPath) == m_mapTexture.end() || m_mapImageInfo.find(szFullPath) == m_mapImageInfo.end())
	{
		SAFE_RELEASE(m_mapTexture[szFullPath]);
		D3DXCreateTextureFromFileExA(
			g_pD3DDevice,
			szFullPath,
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT,
			0,
			D3DFMT_UNKNOWN,
			D3DPOOL_MANAGED,
			D3DX_FILTER_NONE,
			D3DX_DEFAULT,
			0,
			&m_mapImageInfo[szFullPath],
			NULL,
			&m_mapTexture[szFullPath]
			);
	}

	*pImageInfo = m_mapImageInfo[szFullPath];

	return m_mapTexture[szFullPath];
}

LPDIRECT3DTEXTURE9 TextureManager::GetTexture(std::string & szFullPath, D3DXIMAGE_INFO * pImageInfo)
{
	return GetTexture((char*)szFullPath.c_str(), pImageInfo);
}

void TextureManager::Destroy()
{
	for each(auto it in m_mapTexture)
	{
		SAFE_RELEASE(it.second);
	}
	m_mapTexture.clear();
}
