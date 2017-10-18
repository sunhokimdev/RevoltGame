#include "stdafx.h"
#include "SkinnedMeshManager.h"
#include "SkinnedMesh.h"

SkinnedMeshManager::SkinnedMeshManager()
{
}


SkinnedMeshManager::~SkinnedMeshManager()
{
}

void SkinnedMeshManager::Destroy()
{
	for each(auto it in m_mapSkinnedMesh)
	{
		it.second->Destroy();
		SAFE_DELETE(it.second);
	}
}

SkinnedMesh* SkinnedMeshManager::GetSkinnedMesh(char* szFolder, char* szFilename, bool isMove)
{
	std::string sFullPath(szFolder);
	sFullPath += std::string(szFilename);

	if (m_mapSkinnedMesh.find(sFullPath) == m_mapSkinnedMesh.end())
	{
		SkinnedMesh* pSkinnedMesh = new SkinnedMesh();
		pSkinnedMesh->Setup(szFolder, szFilename, D3DXVECTOR3(0, 0, 0), isMove);
		m_mapSkinnedMesh[sFullPath] = pSkinnedMesh;
	}
	return m_mapSkinnedMesh[sFullPath];
}