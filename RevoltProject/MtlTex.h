#pragma once

#include "Object.h"

class MtlTex
{
public:
	MtlTex();
	~MtlTex();

	void Release() { if (m_pTexture) m_pTexture->Release(); }
private:
	SYNTHESIZE_PASS_BY_REF(D3DMATERIAL9, m_stMtl, Material);
	SYNTHESIZE(LPDIRECT3DTEXTURE9, m_pTexture, Texture);
	SYNTHESIZE(int, m_nAttrID, AttrID);
};

