#pragma once
//#include "Object.h"
class cCar;

struct stRubber
{
	std::vector<ST_PNT_VERTEX> m_vecVertex;
	D3DXVECTOR3 position;
	D3DXMATRIXA16 matLocal, matR;
	D3DXVECTOR3 direction;
	LPD3DXMESH mesh;

	float timer;
	//D3DMATERIAL9 material
};

class cSkidMark
{
	std::vector<stRubber> m_vecRubbers;
	cCar* m_pCar;

public:
	cSkidMark();
	~cSkidMark();

	void Setup();
	void Update();
	void Render();
	void Destroy();

	void DrawSkidMark();
	inline void LinkCar(cCar* car) { m_pCar = car; }
};


