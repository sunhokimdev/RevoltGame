#pragma once
class DEBUG_RENDER
{
private:
	typedef struct _DEBUG_RENDER_VERTEX
	{
		D3DXVECTOR3  p;
		D3DCOLOR	c;
		enum { FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE };
	};
	_DEBUG_RENDER_VERTEX* m_DebugRenderVertex;
	void RenderBuffer(const _DEBUG_RENDER_VERTEX* pVertex, const D3DPRIMITIVETYPE Type, const int VertexCount);
public:
	DEBUG_RENDER();
	~DEBUG_RENDER();
	void RenderData(const NxDebugRenderable* data);
};

