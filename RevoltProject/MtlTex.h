#pragma once

#include "Object.h"

class MtlTex : public Object
{
public:
	MtlTex();
	~MtlTex();

private:
	SYNTHESIZE_PASS_BY_REF(D3DMATERIAL9,
		m_stMtl, Material);
	SYNTHESIZE(LPDIRECT3DTEXTURE9,
		m_pTexture, Texture);
	SYNTHESIZE(int, m_nAttrID, AttrID); 
};

