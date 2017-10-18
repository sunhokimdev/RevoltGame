#pragma once

#include "MtlTex.h"
class Group
{
public:
	Group();
	~Group();

	void Render();

private:
	SYNTHESIZE_PASS_BY_REF(std::vector<ST_PNT_VERTEX>,
		m_vecVertex, Vertex);
	SYNTHESIZE_ADD_REF(MtlTex*, m_pMtlTex, MtlTex);
};

