#include "stdafx.h"
#include "Group.h"
#include "MtlTex.h"

Group::Group()
	: m_pMtlTex(NULL)
{
}


Group::~Group()
{
	SAFE_RELEASE(m_pMtlTex);
}

void Group::Render()
{
	if (m_pMtlTex)
	{
		g_pD3DDevice->SetTexture(0, m_pMtlTex->GetTexture());
		g_pD3DDevice->SetMaterial(&m_pMtlTex->GetMaterial());
	}
	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecVertex.size() / 3,
		&m_vecVertex[0],
		sizeof(ST_PNT_VERTEX));
}
