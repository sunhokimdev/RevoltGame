#include "stdafx.h"
#include "Thing.h"
#include "ObjectLoader.h"
#include "MtlTex.h"

Thing::Thing()
	: m_vPosition(0,0,0)
	, m_yAngle(0.0f)
	, m_xAngle(0.0f)
	, m_isMove(false)
	, m_isRot(false)
{
}

Thing::~Thing()
{
}

void Thing::SetPosition(float x, float y, float z)
{
	m_vPosition.x = x;
	m_vPosition.y = y;
	m_vPosition.z = z;
}

void Thing::SetRotationX(float angle)
{
	m_xAngle = angle;
}

void Thing::SetRotationY(float angle)
{
	m_yAngle = angle;
}

void Thing::SetMesh(char * szFolder, char * szFile)
{
	ObjectLoader loader;
	m_pObjMesh = loader.LoadMesh(
		m_vecObjMtlTex,
		szFolder, szFile);
}

void Thing::SetIsMove(bool isMove)
{
	m_isMove = isMove;
}

void Thing::SetIsRot(bool isRot)
{
	m_isRot = isRot;
}

void Thing::Update()
{
	D3DXMATRIXA16 matRX, matRY, matR;

	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixRotationY(&matRX, m_yAngle);
	D3DXMatrixRotationX(&matRY, m_yAngle);

	matR = matRX * matRY;

	m_matWorld = matR;

	m_matWorld._41 = m_vPosition.x;
	m_matWorld._42 = m_vPosition.y;
	m_matWorld._43 = m_vPosition.z;
}

void Thing::Render()
{
	g_pD3DDevice->SetTexture(0, NULL);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

	D3DXMATRIXA16	matWorld, matS, matR;

	D3DXMatrixIdentity(&matWorld);

	g_pD3DDevice->SetTransform(D3DTS_WORLD,
		&matWorld);

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
