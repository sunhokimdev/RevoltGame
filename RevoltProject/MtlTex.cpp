#include "stdafx.h"
#include "MtlTex.h"


MtlTex::MtlTex()
{
	m_pTexture = NULL;
}


MtlTex::~MtlTex()
{
	SAFE_RELEASE(m_pTexture);
}
