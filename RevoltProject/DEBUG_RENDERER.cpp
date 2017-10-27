#include "stdafx.h"
#include "DEBUG_RENDERER.h"


DEBUG_RENDERER::DEBUG_RENDERER()
{
	m_DebugRenderVertex = NULL;
}


DEBUG_RENDERER::~DEBUG_RENDERER()
{
}

void DEBUG_RENDERER::RenderData(const NxDebugRenderable * data)
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	MgrD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	SAFE_DELETE(m_DebugRenderVertex);

	if (data == NULL || MgrD3DDevice == NULL)
	{
		return;
	}
	DWORD dwCount;

	////점 그리기
	unsigned int NbPoints = data->getNbPoints();
	if (NbPoints)
	{
		m_DebugRenderVertex = new _DEBUG_RENDER_VERTEX[NbPoints];
		if (m_DebugRenderVertex == NULL)
		{
			return;
		}
		const NxDebugPoint*	Points = data->getPoints();
	
		dwCount = 0;
	
		while (NbPoints--)
		{
			m_DebugRenderVertex[dwCount].p = D3DXVECTOR3(Points->p.x, Points->p.y, Points->p.z);
			m_DebugRenderVertex[dwCount].c = (DWORD)Points->color;
			dwCount++;
	
			Points++;
		}
		RenderBuffer(m_DebugRenderVertex, D3DPT_POINTLIST, data->getNbPoints());
		SAFE_DELETE(m_DebugRenderVertex);
	}

	//선 그리기
	unsigned int NbLines = data->getNbLines();
	if (NbLines)
	{
		m_DebugRenderVertex = new _DEBUG_RENDER_VERTEX[NbLines * 2];
		if (m_DebugRenderVertex == NULL)
		{
			return;
		}
		const NxDebugLine*	Lines = data->getLines();

		dwCount = 0;

		while (NbLines--)
		{
			m_DebugRenderVertex[dwCount].p = D3DXVECTOR3(Lines->p0.x, Lines->p0.y, Lines->p0.z);
			m_DebugRenderVertex[dwCount].c = (DWORD)Lines->color;
			dwCount++;

			m_DebugRenderVertex[dwCount].p = D3DXVECTOR3(Lines->p1.x, Lines->p1.y, Lines->p1.z);
			m_DebugRenderVertex[dwCount].c = (DWORD)Lines->color;
			dwCount++;

			Lines++;
		}
		RenderBuffer(m_DebugRenderVertex, D3DPT_LINELIST, data->getNbLines());
		SAFE_DELETE(m_DebugRenderVertex);
	}

	//면 그리기
	unsigned int NBTriangles= data->getNbTriangles();
	if (NBTriangles)
	{
		m_DebugRenderVertex = new _DEBUG_RENDER_VERTEX[NBTriangles * 3];
		if (m_DebugRenderVertex == NULL)
		{
			return;
		}
		const NxDebugTriangle* Triangles = data->getTriangles();
	
		dwCount = 0;
	
		while (NBTriangles--)
		{
			m_DebugRenderVertex[dwCount].p = D3DXVECTOR3(Triangles->p0.x, Triangles->p0.y, Triangles->p0.z);
			m_DebugRenderVertex[dwCount].c = (DWORD)Triangles->color;
			dwCount++;
	
			m_DebugRenderVertex[dwCount].p = D3DXVECTOR3(Triangles->p1.x, Triangles->p1.y, Triangles->p1.z);
			m_DebugRenderVertex[dwCount].c = (DWORD)Triangles->color;
			dwCount++;
	
			m_DebugRenderVertex[dwCount].p = D3DXVECTOR3(Triangles->p2.x, Triangles->p2.y, Triangles->p2.z);
			m_DebugRenderVertex[dwCount].c = (DWORD)Triangles->color;
			dwCount++;
	
			Triangles++;
		}
		RenderBuffer(m_DebugRenderVertex, D3DPT_TRIANGLELIST, data->getNbTriangles());
		SAFE_DELETE(m_DebugRenderVertex);
	}
}

void DEBUG_RENDERER::RenderBuffer(const _DEBUG_RENDER_VERTEX * pVertex, const D3DPRIMITIVETYPE Type, const int VertexCount)
{
	//디바이스의 현재상태 저장 및 초기화
	DWORD RStateKightingBK;
	MgrD3DDevice->GetRenderState(D3DRS_LIGHTING, &RStateKightingBK);
	MgrD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	DWORD RStateCullModeBK;
	MgrD3DDevice->GetRenderState(D3DRS_CULLMODE, &RStateCullModeBK);
	MgrD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	IDirect3DBaseTexture9* ppTexture = NULL;
	MgrD3DDevice->GetTexture(0, &ppTexture);
	MgrD3DDevice->SetTexture(0, NULL);

	DWORD FVFBK;
	MgrD3DDevice->GetFVF(&FVFBK);
	MgrD3DDevice->SetFVF(_DEBUG_RENDER_VERTEX::FVF);


	//설정값으로 렌더링
	MgrD3DDevice->DrawPrimitiveUP(Type, VertexCount, pVertex, sizeof(_DEBUG_RENDER_VERTEX));


	//디바이스 원상복귀.
	MgrD3DDevice->SetRenderState(D3DRS_LIGHTING, RStateKightingBK);
	MgrD3DDevice->SetRenderState(D3DRS_CULLMODE, RStateCullModeBK);
	MgrD3DDevice->SetTexture(0, ppTexture);
	MgrD3DDevice->SetFVF(FVFBK);
}
