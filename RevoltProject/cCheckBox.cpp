#include "stdafx.h"
#include "cCheckBox.h"


cCheckBox::cCheckBox()
{
}


cCheckBox::~cCheckBox()
{
}

D3DXVECTOR3 cCheckBox::ToNextCheckBoxDir()
{
	D3DXVECTOR3 dir;
	D3DXVec3Normalize(&dir, &(GetNextCheckBox()->GetPosition() - GetPosition()));
	return dir;
}
