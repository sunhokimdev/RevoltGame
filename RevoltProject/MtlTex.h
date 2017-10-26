#pragma once

#include "Object.h"

class MtlTex
{
public:
	MtlTex();
	~MtlTex();

	void Release() { SAFE_RELEASE(m_pTexture); }
private:
	SYNTHESIZE_PASS_BY_REF(D3DMATERIAL9, m_stMtl, Material);
	SYNTHESIZE(LPDIRECT3DTEXTURE9, m_pTexture, Texture);
	SYNTHESIZE(int, m_nAttrID, AttrID);
};

