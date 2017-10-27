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



	void LoadMesh(std::string folder, std::string name);
	void LoadSphere();
	void LoadBox();
};

