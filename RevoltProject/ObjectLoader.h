#pragma once

class MtlTex;
class Group;

class ObjectLoader
{
public:
	ObjectLoader();
	~ObjectLoader();

	void Load(OUT std::vector<Group*>& vecGroup,
		IN char* szFolder, IN char* szFile);

	void LoadMtlLib(const char* szFolder, char* szFile);

	void LoadSurface(
		OUT std::vector<D3DXVECTOR3>& vecSurface,
		IN char* szFolder, IN char* szFile,
		IN D3DXMATRIXA16* pmat = NULL);

	LPD3DXMESH LoadMesh(
		OUT std::vector<MtlTex*> & vecMtlTex,
		IN const char* szFolder, IN const char* szFile);


	//Object
	static void LoadMesh(OUT cMesh* pMesh, IN std::string szFolder, IN std::string szFile);
	static void LoadMtlLib(std::map<std::string, MtlTex*>* mtlTex, std::string szFolder, std::string szFile);
	static void LoadMeshRotation(OUT cMesh* pMesh, IN std::string szFolder, IN std::string szFile, D3DXVECTOR3 rotateAngle);



private:
	std::map<std::string, MtlTex*> m_mapMtlTex;
};

