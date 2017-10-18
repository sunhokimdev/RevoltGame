#pragma once
class ObjectMap
{
private:
	std::vector<D3DXVECTOR3> m_vecSurface;
public:
	ObjectMap(IN char* szFolder, IN char* szFile,
		IN D3DXMATRIXA16* pmat = NULL);
	~ObjectMap(void);

	void Load(IN char* szFolder, IN char* szFile, IN D3DXMATRIXA16* pmat = NULL);
	bool GetHeight(IN float x, OUT float& y, IN float z);
};

