#include "stdafx.h"
#include "MtlTex.h"


MtlTex::MtlTex()
{
}


MtlTex::~MtlTex()
{
	SAFE_RELEASE(m_pTexture);
}
