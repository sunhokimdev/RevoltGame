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

	void LoadMtlLib(char* szFolder, char* szFile);

	void LoadSurface(
		OUT std::vector<D3DXVECTOR3>& vecSurface,
		IN char* szFolder, IN char* szFile,
		IN D3DXMATRIXA16* pmat = NULL);

	LPD3DXMESH LoadMesh(
		OUT std::vector<MtlTex*> & vecMtlTex,
		IN char* szFolder, IN char* szFile);
private:
	std::map<std::string, MtlTex*> m_mapMtlTex;
};

