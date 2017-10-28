#pragma once
#include "MtlTex.h"
//class cMtlTex;

class cMesh
{
public:
	LPD3DXMESH m_pMesh;
	std::vector<MtlTex*> m_vecMtlTex;

public:
	void Destory();
	void Render();

	cMesh();
	~cMesh();


	//name 에 확장자를 포함 시킬 것.
	void LoadMesh(std::string folder, std::string name);
	void LoadSphere();
	void LoadBox();
};

