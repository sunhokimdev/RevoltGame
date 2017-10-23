#include "stdafx.h"
#include "Car.h"
#include "MtlTex.h"
#include "CarTextLoader.h"

Car::Car()
{
}


Car::~Car()
{
}

void Car::Setup()
{
	CarTextLoader loader;

	loader.Load(m_car, "Cars/tc1", "Parameters.txt");
}

void Car::Update()
{

}

void Car::Render()
{
	g_pD3DDevice->SetTexture(0, NULL);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

	g_pD3DDevice->SetTransform(D3DTS_WORLD,
		&m_matWorld);

	for (size_t i = 0; i < m_vecObjMtlTex.size(); ++i)
	{
		g_pD3DDevice->SetMaterial(
			&m_vecObjMtlTex[i]->GetMaterial());

		if (m_vecObjMtlTex[i]->GetTexture() != NULL)
		{
			g_pD3DDevice->SetTexture(
				0,
				m_vecObjMtlTex[i]->GetTexture());
		}
		m_pObjMesh->DrawSubset(i);
	}
}
