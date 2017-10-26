#include "stdafx.h"
#include "Thing.h"
#include "MtlTex.h"
#include "ObjectLoader.h"

#include "ObjectLoader.h"
#include "MtlTex.h"

LOBBY* Thing::g_LobbyState;
float Thing::g_xRotAngle = 0.0f;
int* Thing::g_select;

Thing::Thing()
	: m_vPosition(0,0,0)
	, m_vTarget(0,0,0)
	, m_yAngle(0.0f)
	, m_xAngle(0.0f)
	, m_isMove(false)
	, m_isRot(false)
	, m_lobby(LOBBY_NONE)
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

	m_vPrevPosition = m_vPosition;
}

void Thing::SetRotationX(float angle)
{
	g_xRotAngle = angle;
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

void Thing::SetIsMove(bool isMove)
{
	m_isMove = isMove;
}

void Thing::SetIsRot(bool isRot)
{
	m_isRot = isRot;
}

void Thing::SetLobby(LOBBY lobby)
{
	m_lobby = lobby;
}

void Thing::SetIndex(int index)
{
	m_index = index;
}

void Thing::SetNameObject(std::string name)
{
	m_name = name;

	/*   자동차 박스라면   */
	if (m_name.find("CarBox") != -1)
	{

	}
}

void Thing::Update()
{
	D3DXMATRIXA16 matRX, matRY, matR, matT;

	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixIdentity(&matRX);
	D3DXMatrixIdentity(&matRY);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixIdentity(&matT);

	/*   자동차 선택 분기점일 때   */
	if (m_lobby == SELECT_CAR_LOBBY && *g_LobbyState == SELECT_CAR_LOBBY)
	{
		if (m_index == *g_select)
		{
			if (m_vPosition.y < m_vTarget.y)
			{
				D3DXVECTOR3 tempV = (m_vTarget - m_vPrevPosition) / 30.0f;
				m_vPosition += tempV;
			}

			else if (m_vTarget.y >= m_vPosition.y)
			{
				m_vPosition = m_vTarget;
			}

			D3DXMatrixRotationX(&matRX, D3DX_PI/4.0f);
			m_yAngle = D3DX_PI / 3.7f;
		}
		else
		{
			if (m_vPosition != m_vPrevPosition)
			{
				m_vPosition += (m_vPrevPosition - m_vTarget) / 40.0f;
			}
			m_vPosition = m_vPrevPosition;
			m_yAngle = m_prevYAngle;
			D3DXMatrixRotationX(&matRX, 0.0f);
		}
	}

	else if (*g_LobbyState == CREATE_PROFILE_LOBBY ||
		*g_LobbyState == CREATE_PROFILE_LOBBY2)
	{
		if(m_isRot)
			D3DXMatrixRotationZ(&matRX, g_xRotAngle);
	}

	D3DXMatrixRotationY(&matRY, m_yAngle);

	matR = matRX * matRY;

	matT._41 = m_vPosition.x;
	matT._42 = m_vPosition.y;
	matT._43 = m_vPosition.z;

	m_matWorld = matR * matT;
}

void Thing::Render()
{
	g_pD3DDevice->SetTexture(0, NULL);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);

	for (size_t i = 0; i < m_vecObjMtlTex.size(); ++i)
	{
		g_pD3DDevice->SetMaterial(&m_vecObjMtlTex[i]->GetMaterial());

		if (m_vecObjMtlTex[i]->GetTexture() != NULL)
		{
			g_pD3DDevice->SetTexture(0, m_vecObjMtlTex[i]->GetTexture());
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

void Thing::MirrorRender()
{
	if (*g_LobbyState >= MAIN_LOBBY3)
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
}

