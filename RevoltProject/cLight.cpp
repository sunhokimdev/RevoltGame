#include "stdafx.h"
#include "cLight.h"
#include "cCar.h"

cLight::cLight()
{
	ZeroMemory(&m_stLight, sizeof(D3DLIGHT9));
}

cLight::~cLight(){}

void cLight::Setup(int nIndex, _D3DLIGHTTYPE type, D3DXCOLOR color, D3DXVECTOR3 position)
{
	//Object::Setup();

	m_nIndex = nIndex;

	m_stLight.Type = type;
	m_stLight.Ambient = color;
	m_stLight.Diffuse = color;
	m_stLight.Specular = color;
	m_stLight.Position = position;
	D3DXVECTOR3 dir = { 0,-1,0 };
	D3DXVec3Normalize(&dir, &dir);
	m_stLight.Direction = dir;
	m_stLight.Phi = D3DX_PI / 2;
	m_stLight.Theta = D3DX_PI / 2;
	m_stLight.Falloff = 1.0f;
	m_stLight.Range = 20;
	m_stLight.Attenuation0 = 0.1f;
	m_stLight.Attenuation1 = 0.1f;
	m_stLight.Attenuation2 = 0.1f;

	g_pD3DDevice->SetLight(nIndex, &m_stLight);
}

void cLight::SetupDirectional(int nIndex, D3DXCOLOR color, D3DXCOLOR direc)
{
	//Object::Setup();

	m_nIndex = nIndex;

	m_stLight.Type = D3DLIGHT_DIRECTIONAL;
	m_stLight.Ambient = color;
	m_stLight.Diffuse = color;
	m_stLight.Specular = color;
	D3DXVECTOR3 dir = direc;
	D3DXVec3Normalize(&dir, &dir);
	m_stLight.Direction = dir;
	
	g_pD3DDevice->SetLight(nIndex, &m_stLight);
}

void cLight::SetupPoint(int nIndex, D3DXCOLOR color, D3DXVECTOR3 position, float range)
{
	//Object::Setup();

	m_nIndex = nIndex;

	m_stLight.Type = D3DLIGHT_POINT;
	m_stLight.Ambient = color;
	m_stLight.Diffuse = color;
	m_stLight.Specular = color;
	m_stLight.Position = position;
	m_stLight.Range = range;
	m_stLight.Attenuation0 = 0.1f;
	m_stLight.Attenuation1 = 0.1f;
	m_stLight.Attenuation2 = 0.1f;

	g_pD3DDevice->SetLight(nIndex, &m_stLight);
}

void cLight::SetupSpot(int nIndex, D3DXCOLOR color, D3DXVECTOR3 position, D3DXCOLOR direc, float range, float Phi /*= D3DX_PI / 2*/, float Theta /*= D3DX_PI / 2*/)
{
	//Object::Setup();

	m_nIndex = nIndex;

	m_stLight.Type = D3DLIGHT_SPOT;
	m_stLight.Ambient = color;
	m_stLight.Diffuse = color;
	m_stLight.Specular = color;
	m_stLight.Position = position;
	D3DXVECTOR3 dir = direc;
	D3DXVec3Normalize(&dir, &dir);
	m_stLight.Direction = dir;
	m_stLight.Phi = Phi;
	m_stLight.Theta = Theta;
	m_stLight.Falloff = 1.0f;
	m_stLight.Range = range;
	m_stLight.Attenuation0 = 0.1f;
	m_stLight.Attenuation1 = 0.1f;
	m_stLight.Attenuation2 = 0.1f;

	g_pD3DDevice->SetLight(nIndex, &m_stLight);
}

void cLight::Update()
{
	//Object::Update();
}

void cLight::Destroy()
{
	//Object::Destroy();
	g_pD3DDevice->LightEnable(m_nIndex, false);
	g_pD3DDevice->SetLight(m_nIndex, NULL);
}

void cLight::Switch(bool on)
{
	g_pD3DDevice->LightEnable(m_nIndex, on);
}