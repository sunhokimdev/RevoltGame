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
	//D3DMATERIAL9 material;
	void Setup()
	{
		std::vector<ST_PNT_VERTEX> vecVertex;

		//ST_PNT_VERTEX vertex;
		D3DXVECTOR3 p[4];
		p[0] = { position.x - 0.1f, 0, position.z - 0.2f };
		p[1] = { position.x + 0.1f, 0, position.z - 0.2f };
		p[2] = { position.x + 0.1f, 0, position.z + 0.2f };
		p[3] = { position.x - 0.1f, 0, position.z + 0.2f };


		for (int i = 0; i < 4; i++)
		{
			ST_PNT_VERTEX vertex;
			vertex.p = p[i];
			D3DXVec3TransformCoord(&vertex.p, &vertex.p, &matR);

			vecVertex.push_back(vertex);
		}

		std::vector<DWORD> vecIndex;
		
		vecIndex.push_back(0);
		vecIndex.push_back(1);
		vecIndex.push_back(2);
		vecIndex.push_back(0);
		vecIndex.push_back(2);
		vecIndex.push_back(3);

		m_vecVertex.resize(6);
		
		for (int i = 0; i < vecIndex.size(); i += 3)
		{
			m_vecVertex[i + 0] = vecVertex[vecIndex[i + 0]];
			m_vecVertex[i + 1] = vecVertex[vecIndex[i + 1]];
			m_vecVertex[i + 2] = vecVertex[vecIndex[i + 2]];
		}

		D3DXVECTOR3 u, v, n;
		for (int i = 0; i < vecIndex.size(); i += 3)
		{
			u = m_vecVertex[i + 1].p - m_vecVertex[i].p;
			v = m_vecVertex[i + 2].p - m_vecVertex[i].p;

			D3DXVec3Cross(&n, &u, &v);
			D3DXVec3Normalize(&n, &n);

			m_vecVertex[i + 0].n = n;
			m_vecVertex[i + 1].n = n;
			m_vecVertex[i + 2].n = n;
		}

		D3DXCreateMeshFVF(vecIndex.size() / 3, vecVertex.size(), D3DXMESH_MANAGED, ST_PNT_VERTEX::FVF, g_pD3DDevice, &mesh);
		
		ST_PNT_VERTEX* pV = NULL;
		mesh->LockVertexBuffer(0, (LPVOID*)&pV);
		memcpy(pV, &vecVertex[0], vecVertex.size() * sizeof(ST_PNT_VERTEX));
		mesh->UnlockVertexBuffer();

		DWORD* pI = NULL;
		mesh->LockIndexBuffer(0, (LPVOID*)&pI);
		memcpy(pI, &vecIndex[0], vecIndex.size() * sizeof(DWORD));
		mesh->UnlockIndexBuffer();
	}
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
	void Destory();

	void DrawSkidMark();
	inline void LinkCar(cCar* car) { m_pCar = car; }
};


