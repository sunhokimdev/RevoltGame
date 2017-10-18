#pragma once
#define g_pSkinnedMeshManager SkinnedMeshManager::GetInstance()

class SkinnedMesh;

class SkinnedMeshManager
{
private:
	std::map<std::string, SkinnedMesh*> m_mapSkinnedMesh;
public:
	SINGLETONE(SkinnedMeshManager);

	SkinnedMesh* GetSkinnedMesh(char* szFolder, char* szFilename, bool isMove);

	void Destroy();
};

