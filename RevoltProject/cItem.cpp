#include "stdafx.h"
#include "cItem.h"

cItem::cItem()
	: m_pParent(NULL)
{
	D3DXMatrixIdentity(&m_matWorld);
}

cItem::~cItem()
{

}

void cItem::Update()
{
}

void cItem::Render()
{
	g_pD3DDevice->SetTexture(0, NULL);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

	g_pD3DDevice->SetTransform(D3DTS_WORLD,
		&m_matWorld);

	for (size_t i = 0; i < m_vecObjMtlTex.size(); ++i)
	{
		g_pD3DDevice->SetMaterial(&m_vecObjMtlTex[i]->GetMaterial());

		if (m_vecObjMtlTex[i]->GetTexture() != NULL)
		{
			g_pD3DDevice->SetTexture(0, m_vecObjMtlTex[i]->GetTexture());
		}
		m_pObjMesh->DrawSubset(i);
	}
}

void cItem::AddChild(cItem * pChild)
{
	pChild->SetParent(this);
	m_vecChild.push_back(pChild);
}
