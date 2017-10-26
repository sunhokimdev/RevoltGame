#include "stdafx.h"
#include "cTransform.h"


cTransform::cTransform()
	: m_position(0, 0, 0)
	, m_size(1, 1, 1)
	, m_direction(0, 0, 1)
	//, m_top(0, 1, 0)
{
	D3DXQuaternionIdentity(&m_Quaternion);
	DebugTr = true;

	front = D3DXVECTOR3(0, 0, 1);
	right = D3DXVECTOR3(1, 0, 0);
	up = D3DXVECTOR3(0, 1, 0);

	SetQuaternion(front);
	//	ArrowVectorSetting();
}

cTransform::~cTransform()
{
}

void cTransform::Update()
{
	ArrowVectorSetting();
}

void cTransform::Render()
{
	if (DebugTr)
	{
		ST_PC_VERTEX v;

		std::vector<ST_PC_VERTEX>	vecVertex;

		v.c = D3DCOLOR_XRGB(0, 0, 255);
		v.p = m_position; vecVertex.push_back(v);
		v.p = m_position + GetFrontVec() * 5; vecVertex.push_back(v);

		v.c = D3DCOLOR_XRGB(0, 255, 0);
		v.p = m_position; vecVertex.push_back(v);
		v.p = m_position + GetUpVec() * 5; vecVertex.push_back(v);

		v.c = D3DCOLOR_XRGB(255, 0, 0);
		v.p = m_position; vecVertex.push_back(v);
		v.p = m_position + GetRightVec() * 5; vecVertex.push_back(v);


		LPDIRECT3DVERTEXBUFFER9 m_pVB;

		int m_nNumLine = vecVertex.size() / 2;
		g_pD3DDevice->CreateVertexBuffer(vecVertex.size() * sizeof(ST_PC_VERTEX),
			0, ST_PC_VERTEX::FVF, D3DPOOL_MANAGED,
			&m_pVB, NULL);
		ST_PC_VERTEX *pV = NULL;
		m_pVB->Lock(0, 0, (LPVOID*)&pV, 0);
		memcpy(pV, &vecVertex[0], vecVertex.size() * sizeof(ST_PC_VERTEX));
		m_pVB->Unlock();

		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &GetMatrix());
		g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
		g_pD3DDevice->SetStreamSource(0, m_pVB, 0, sizeof(ST_PC_VERTEX));
		g_pD3DDevice->DrawPrimitive(D3DPT_LINELIST, 0, m_nNumLine);

		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
		SAFE_RELEASE(m_pVB);
	}
}


D3DXVECTOR3 cTransform::GetFrontVec()
{
	return front;
}

D3DXVECTOR3 cTransform::GetRightVec()
{
	return right;
}

D3DXVECTOR3 cTransform::GetUpVec()
{
	return up;
}

void cTransform::SetNxF32(NxF32 * mtl)
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);

	matWorld._11 = mtl[0];
	matWorld._12 = mtl[1];
	matWorld._13 = mtl[2];
	matWorld._21 = mtl[3];
	matWorld._22 = mtl[4];
	matWorld._23 = mtl[5];
	matWorld._31 = mtl[6];
	matWorld._32 = mtl[7];
	matWorld._33 = mtl[8];

	cTransform::SetQuaternion(matWorld);
}

void cTransform::SetNxVec3(NxVec3 NxPos)
{
	m_position.x = NxPos.x; m_position.y = NxPos.y; m_position.z = NxPos.z;
}



NxVec3 cTransform::DxVec3ToNxVec3(D3DXVECTOR3 dxVec3)
{
	return NxVec3(dxVec3.x, dxVec3.y, dxVec3.z);
}

NxF32 * cTransform::DxMatToNxF32(D3DXMATRIX dxMat)
{
	NxF32 mtl[] = { 1,0,0,0,1,0,0,0,1 };

	mtl[0] = dxMat._11;
	mtl[1] = dxMat._12;
	mtl[2] = dxMat._13;
	mtl[3] = dxMat._21;
	mtl[4] = dxMat._22;
	mtl[5] = dxMat._23;
	mtl[6] = dxMat._31;
	mtl[7] = dxMat._32;
	mtl[8] = dxMat._33;

	return mtl;
}

D3DXVECTOR3 cTransform::NxVec3ToDxVec3(NxVec3 nxVec3)
{
	return D3DXVECTOR3(nxVec3.x, nxVec3.y, nxVec3.z);
}

D3DXMATRIX cTransform::NxF32ToDxMat(NxF32* nxF32)
{
	D3DXMATRIX mat;
	D3DXMatrixIdentity(&mat);

	mat._11 = nxF32[0];
	mat._12 = nxF32[1];
	mat._13 = nxF32[2];
	mat._21 = nxF32[3];
	mat._22 = nxF32[4];
	mat._23 = nxF32[5];
	mat._31 = nxF32[6];
	mat._32 = nxF32[7];
	mat._33 = nxF32[8];

	return mat;
}



void cTransform::ArrowVectorSetting()
{
	D3DXMATRIXA16 matR;
	D3DXMatrixRotationQuaternion(&matR, &m_Quaternion);
	D3DXVec3TransformNormal(&front, &D3DXVECTOR3(0, 0, 1), &matR);
	D3DXVec3TransformNormal(&right, &D3DXVECTOR3(1, 0, 0), &matR);
	D3DXVec3TransformNormal(&up, &D3DXVECTOR3(0, 1, 0), &matR);

	D3DXVec3Normalize(&front, &front);
	D3DXVec3Normalize(&right, &right);
	D3DXVec3Normalize(&up, &up);

	D3DXVECTOR3 dir = GetDirection();
	float dirL = D3DXVec3Length(&dir);
	D3DXVec3TransformNormal(&dir, &D3DXVECTOR3(0, 0, dirL), &matR);
	SetDirection(dir);
}

