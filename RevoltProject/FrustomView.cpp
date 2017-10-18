#include "stdafx.h"
#include "FrustomView.h"


FrustomView::FrustomView()
{
}

FrustomView::~FrustomView()
{
}

void FrustomView::Setup()
{
	D3DXMATRIXA16 matView, matProj, mat;
	D3DVIEWPORT9 vp;

	g_pD3DDevice->GetViewport(&vp);

	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProj);
	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);

	float zMinDistance = -matProj._43 / matProj._33;
	float r = (1000.0f) / (1000.0f - zMinDistance);
	float zMaxDistance = (matProj._33 * zMinDistance) / (matProj._33 - 1);

	matProj._33 = r;
	matProj._43 = -r * zMinDistance;

	D3DXMatrixMultiply(&mat, &matView, &matProj);

	mat = matView * matProj;

	m_planes[0].a = mat._14 + mat._13;
	m_planes[0].b = mat._24 + mat._23;
	m_planes[0].c = mat._34 + mat._33;
	m_planes[0].d = mat._44 + mat._43;
	D3DXPlaneNormalize(&m_planes[0], &m_planes[0]);

	m_planes[1].a = mat._14 - mat._13;
	m_planes[1].b = mat._24 - mat._23;
	m_planes[1].c = mat._34 - mat._33;
	m_planes[1].d = mat._44 - mat._43;
	D3DXPlaneNormalize(&m_planes[1], &m_planes[1]);

	m_planes[2].a = mat._14 + mat._11;
	m_planes[2].b = mat._24 + mat._21;
	m_planes[2].c = mat._34 + mat._31;
	m_planes[2].d = mat._44 + mat._41;
	D3DXPlaneNormalize(&m_planes[2], &m_planes[2]);

	m_planes[3].a = mat._14 - mat._11;
	m_planes[3].b = mat._24 - mat._21;
	m_planes[3].c = mat._34 - mat._31;
	m_planes[3].d = mat._44 - mat._41;
	D3DXPlaneNormalize(&m_planes[3], &m_planes[3]);

	m_planes[4].a = mat._14 - mat._12;
	m_planes[4].b = mat._24 - mat._22;
	m_planes[4].c = mat._34 - mat._32;
	m_planes[4].d = mat._44 - mat._42;
	D3DXPlaneNormalize(&m_planes[4], &m_planes[4]);

	m_planes[5].a = mat._14 + mat._12;
	m_planes[5].b = mat._24 + mat._22;
	m_planes[5].c = mat._34 + mat._32;
	m_planes[5].d = mat._44 + mat._42;
	D3DXPlaneNormalize(&m_planes[5], &m_planes[5]);
}

bool FrustomView::CheckPoint(float x, float y, float z)
{
	for (int i = 0;i < 6;i++)
	{
		if (D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR3(x, y, z)) < 0.0f)
		{
			return false;
		}
	}
	return true;
}

bool FrustomView::CheckCube(float xCenter, float yCenter, float zCenter, float radius)
{
	for (int i = 0; i<6; i++)
	{
		if (D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR3((xCenter - radius), (yCenter - radius), (zCenter - radius))) >= 0.0f)
			continue;

		if (D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR3((xCenter + radius), (yCenter - radius), (zCenter - radius))) >= 0.0f)
			continue;

		if (D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR3((xCenter - radius), (yCenter + radius), (zCenter - radius))) >= 0.0f)
			continue;

		if (D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR3((xCenter + radius), (yCenter + radius), (zCenter - radius))) >= 0.0f)
			continue;

		if (D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR3((xCenter - radius), (yCenter - radius), (zCenter + radius))) >= 0.0f)
			continue;

		if (D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR3((xCenter + radius), (yCenter - radius), (zCenter + radius))) >= 0.0f)
			continue;

		if (D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR3((xCenter - radius), (yCenter + radius), (zCenter + radius))) >= 0.0f)
			continue;

		if (D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR3((xCenter + radius), (yCenter + radius), (zCenter + radius))) >= 0.0f)
			continue;

		return false;
	}

	return true;
}

bool FrustomView::CheckSphere(float xCenter, float yCenter, float zCenter, float radius)
{
	for (int i = 0; i<6; i++)
	{
		if (D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR3(xCenter, yCenter, zCenter)) < -radius)
		{
			return false;
		}
	}

	return true;
}

bool FrustomView::CheckRectangle(float xCenter, float yCenter, float zCenter, float xSize, float ySize, float zSize)
{
	for (int i = 0; i<6; i++)
	{
		if (D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR3((xCenter - xSize), (yCenter - ySize), (zCenter - zSize))) >= 0.0f)
			continue;

		if (D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR3((xCenter + xSize), (yCenter - ySize), (zCenter - zSize))) >= 0.0f)
			continue;

		if (D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR3((xCenter - xSize), (yCenter + ySize), (zCenter - zSize))) >= 0.0f)
			continue;

		if (D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR3((xCenter - xSize), (yCenter - ySize), (zCenter + zSize))) >= 0.0f)
			continue;

		if (D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR3((xCenter + xSize), (yCenter + ySize), (zCenter - zSize))) >= 0.0f)
			continue;

		if (D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR3((xCenter + xSize), (yCenter - ySize), (zCenter + zSize))) >= 0.0f)
			continue;

		if (D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR3((xCenter - xSize), (yCenter + ySize), (zCenter + zSize))) >= 0.0f)
			continue;

		if (D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR3((xCenter + xSize), (yCenter + ySize), (zCenter + zSize))) >= 0.0f)
			continue;

		return false;
	}

	return true;
}
