#include "stdafx.h"
#include "WheelTire.h"

float WheelTire::g_xRotAngle;

WheelTire::WheelTire()
{
}


WheelTire::~WheelTire()
{
}

void WheelTire::Setup()
{
}

void WheelTire::Update()
{
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_matR);
	D3DXMatrixIdentity(&m_matRX);
	D3DXMatrixIdentity(&m_matRY);
	D3DXMatrixIdentity(&m_matR);
	D3DXMatrixIdentity(&m_matT);

	if (*g_LobbyState == CREATE_PROFILE_LOBBY)
	{
			D3DXMatrixRotationZ(&m_matRX, g_xRotAngle);
	}

	Thing::Update();
}

void WheelTire::Render()
{
	Thing::Render();
}