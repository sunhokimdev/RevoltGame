#include "stdafx.h"
#include "Thing.h"
#include "MtlTex.h"
#include "ObjectLoader.h"

Thing::Thing()
{
}

Thing::~Thing()
{
}

void Thing::Load(char * szFolder, char* szFile)
{
	ObjectLoader loader;
	m_pObjMesh = loader.LoadMesh(
		m_vecObjMtlTex,
		szFolder, szFile);
}

void Thing::SetPosition(float x, float y, float z)
{
	m_vPosition.x = x;
	m_vPosition.y = y;
	m_vPosition.z = z;
}

void Thing::AddChild(Thing * pChild)
{
	pChild->SetParent(this);
	m_vecChild.push_back(pChild);
}

void Thing::Update()
{
	D3DXMatrixIdentity(&m_matWorld);

	m_matWorld._41 = m_vPosition.x;
	m_matWorld._42 = m_vPosition.y;
	m_matWorld._43 = m_vPosition.z;

	if (m_pParent)
	{
		m_matWorld._41 += m_pParent->m_matWorld._41;
		m_matWorld._42 += m_pParent->m_matWorld._42;
		m_matWorld._43 += m_pParent->m_matWorld._43;
	}

	for each(auto c in m_vecChild)
	{
		c->Update();
	}
}

void Thing::Render()
{
	g_pD3DDevice->SetTexture(0, NULL);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

	D3DXMATRIXA16	matWorld, matS, matR;

	D3DXMatrixIdentity(&matWorld);

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	for (size_t i = 0; i < m_vecObjMtlTex.size(); ++i)
	{
		g_pD3DDevice->SetMaterial(
			&m_vecObjMtlTex[i]->GetMaterial());

		if (m_vecObjMtlTex[i]->GetTexture() != NULL)
		{
			g_pD3DDevice->SetTexture(
				0,
				m_vecObjMtlTex[i]->GetTexture());
		}
		m_pObjMesh->DrawSubset(i);
	}

	for each(auto c in m_vecChild)
	{
		c->Render();
	}
}

void Thing::Destroy()
{
}

Thing * Thing::FindChildByTag(int nTag)
{
	if (m_nTag == nTag)
		return this;

	for each(auto c in m_vecChild)
	{
		Thing* p = c->FindChildByTag(nTag);
		if (p) return p;
	}

	return nullptr;

	return nullptr;
}
