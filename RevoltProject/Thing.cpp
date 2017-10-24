#include "stdafx.h"
#include "Thing.h"
#include "MtlTex.h"
#include "ObjectLoader.h"

#include "CarTextLoader.h"
#include "MtlTex.h"
#include "Car.h"

LOBBY* Thing::g_LobbyState;

Thing::Thing()
	: m_vPosition(0,0,0)
	, m_vTarget(0,0,0)
	, m_yAngle(0.0f)
	, m_xAngle(0.0f)
	, m_pParentWorldTM(NULL)
{
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_matR);
	D3DXMatrixIdentity(&m_matRX);
	D3DXMatrixIdentity(&m_matRY);
	D3DXMatrixIdentity(&m_matR);
	D3DXMatrixIdentity(&m_matT);
}

Thing::~Thing()
{
	SAFE_RELEASE(m_pObjMesh);

	for each(auto c in m_vecObjMtlTex)
		SAFE_RELEASE(c);

	SAFE_DELETE(g_LobbyState);
	SAFE_DELETE(m_pParentWorldTM);
}

void Thing::SetPosition(float x, float y, float z)
{
	m_vPosition.x = x;
	m_vPosition.y = y;
	m_vPosition.z = z;

	m_vPrevPosition = m_vPosition;
}

void Thing::SetRotationX(float angle)
{
	m_xAngle = angle;
	m_prevXAngle = m_xAngle;
}

void Thing::SetRotationY(float angle)
{
	m_yAngle = angle;
	m_prevYAngle = angle;
}

void Thing::SetTarget(float x, float y, float z)
{
	m_vTarget.x = x;
	m_vTarget.y = y;
	m_vTarget.z = z;
}

void Thing::SetMesh(char * szFolder, char * szFile)
{
	ObjectLoader loader;
	m_pObjMesh = loader.LoadMesh(
		m_vecObjMtlTex,
		szFolder, szFile);
}

void Thing::AddChild(Thing * pChild)
{
	if (pChild == NULL) return;

	pChild->m_pParentWorldTM = &m_matWorld;
	m_vecChild.push_back(pChild);
}


void Thing::Update()
{
	D3DXMatrixRotationY(&m_matRY, m_yAngle);

	m_matR = m_matRX * m_matRY;

	m_matT._41 = m_vPosition.x;
	m_matT._42 = m_vPosition.y;
	m_matT._43 = m_vPosition.z;

	m_matWorld = m_matR * m_matT;

	if (m_pParentWorldTM)
	{
		m_matWorld *= *m_pParentWorldTM;
	}

	for each(auto p in m_vecChild)
	{
		p->Update();
	}
}

void Thing::Render()
{
	g_pD3DDevice->SetTexture(0, NULL);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

	g_pD3DDevice->SetTransform(D3DTS_WORLD,
		&m_matWorld);
		
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
}

void Thing::Destroy()
{
}

