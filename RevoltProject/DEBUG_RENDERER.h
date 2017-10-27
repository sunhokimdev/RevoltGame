#pragma once
#include <NxDebugRenderable.h>

class DEBUG_RENDERER
{
public:
	DEBUG_RENDERER();
	~DEBUG_RENDERER();
private:
	//디버깅을 위한 버택스정보
	typedef struct _DEBUG_RENDER_VERTEX
	{
		D3DXVECTOR3  p;
		D3DCOLOR	c;
		enum { FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE };
	};

	_DEBUG_RENDER_VERTEX* m_DebugRenderVertex;
public:
	void RenderData(const NxDebugRenderable* data);
private:
	void RenderBuffer(const _DEBUG_RENDER_VERTEX* pVertex, const D3DPRIMITIVETYPE Type, const int VertexCount);
};

