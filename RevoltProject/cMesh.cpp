#include "stdafx.h"
#include "cMesh.h"
#include "MtlTex.h"
#include "ObjectLoader.h"

//기술면접 책 , 디버깅관련 책
//프로그래밍면접, 이렇게 준비한다.

cMesh::cMesh()
	: m_pMesh(NULL)
{
}


cMesh::~cMesh()
{
}


void cMesh::LoadMesh(std::string folder, std::string name)
{
	ObjectLoader::LoadMesh(this, folder, name);
}

void cMesh::LoadCarMesh(std::string folder, std::string name)
{
	ObjectLoader::LoadMeshRotation(this, folder, name,{ 0,D3DX_PI / 2,0 });
	//자동차 오브젝트 불러오기
}

void cMesh::LoadSphere()
{
	D3DXCreateSphere(g_pD3DDevice, 1, 20, 20, &m_pMesh, NULL);
}

void cMesh::LoadBox()
{
	D3DXCreateBox(MgrD3DDevice, 1, 1, 1, &m_pMesh, NULL);
}

void cMesh::Destroy()
{
	//m_mapMtlTex.clear();
	for each (auto pMtlTex in m_vecMtlTex)
	{
		//pMtlTex->Release();
		SAFE_DELETE(pMtlTex);
	}
	m_vecMtlTex.clear();
	SAFE_RELEASE(m_pMesh);
}

void cMesh::Render()
{
	if (!m_vecMtlTex.empty())
	{
		int index = 0;
		for each (auto pMtlTex in m_vecMtlTex)
		{
			MgrD3DDevice->SetMaterial(&(pMtlTex->GetMaterial()));

			if (pMtlTex->GetTexture())
			{
				MgrD3DDevice->SetTexture(0, pMtlTex->GetTexture());
			}

			g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
			
			m_pMesh->DrawSubset(index++);

			if (pMtlTex->GetTexture())
				MgrD3DDevice->SetTexture(0, NULL);
		}
	}
}