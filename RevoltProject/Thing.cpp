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
		if (*g_LobbyState == CREATE_PROFILE_LOBBY ||
		*g_LobbyState == CREATE_PROFILE_LOBBY2)

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
		g_pD3DDevice->SetMaterial(&m_vecObjMtlTex[i]->GetMaterial());

		if (m_vecObjMtlTex[i]->GetTexture() != NULL)
		{
			g_pD3DDevice->SetTexture(0, m_vecObjMtlTex[i]->GetTexture());
		}
		m_pObjMesh->DrawSubset(i);
	}

}

void Thing::Destroy()
{

}


void Thing::MirrorRender()
{
	g_pD3DDevice->SetRenderState(D3DRS_STENCILENABLE, true);
	g_pD3DDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
	g_pD3DDevice->SetRenderState(D3DRS_STENCILREF, 0x1);
	g_pD3DDevice->SetRenderState(D3DRS_STENCILMASK, 0xffffffff);
	g_pD3DDevice->SetRenderState(D3DRS_STENCILWRITEMASK, 0xffffffff);
	g_pD3DDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
	g_pD3DDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
	g_pD3DDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);

	g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);

	g_pD3DDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
	g_pD3DDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);

	// 반사 위치
	D3DXMATRIX W, R;
	D3DXPLANE plane(0.0f, 1.0f, 0.0f, 0.0f);
	D3DXMatrixReflect(&R, &plane);
	W = m_matWorld * R;

	g_pD3DDevice->Clear(0, 0, D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &W);
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_DESTCOLOR);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_SRCCOLOR);
	
	for (size_t i = 0; i < m_vecObjMtlTex.size(); ++i)
	{
		g_pD3DDevice->SetMaterial(&m_vecObjMtlTex[i]->GetMaterial());
		if (m_vecObjMtlTex[i]->GetTexture() != NULL)
		{
			g_pD3DDevice->SetTexture(0, m_vecObjMtlTex[i]->GetTexture());
		}
		m_pObjMesh->DrawSubset(i);
	}

	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_STENCILENABLE, false);
}

