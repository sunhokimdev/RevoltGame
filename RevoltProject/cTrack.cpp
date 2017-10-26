#include "stdafx.h"
#include "cTrack.h"


cTrack::cTrack()
{
}


cTrack::~cTrack()
{
}

void cTrack::Update()
{
	for each(Object* pObj in m_vecObject)
	{
		pObj->Update();
	}
}

void cTrack::Render()
{
	g_pD3DDevice->SetTexture(0, NULL);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &cTransform::GetMatrix(true, true, true));

	for each(Object* pObj in m_vecObject)
	{
		pObj->Render();
	}

//	for (size_t i = 0; i < m_vecObject.size(); ++i)
//	{
//		g_pD3DDevice->SetMaterial(&m_vecObject[i]->GetMeshData()->m_vecMtlTex[i]->GetMaterial());
//
//		if (m_vecObject[i]->GetTexture() != NULL)
//		{
//			g_pD3DDevice->SetTexture(0, m_vecObjMtlTex[i]->GetTexture());
//		}
//		m_pObjMesh->DrawSubset(i);
//	}
}
