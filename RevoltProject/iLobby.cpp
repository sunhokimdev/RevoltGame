#include "stdafx.h"
#include "iLobby.h"
#include "UIObject.h"

LOBBY* iLobby::m_gLobbyState;

iLobby::iLobby()
{
}

iLobby::~iLobby()
{
	SAFE_DELETE(m_pRootUI);
	//SAFE_RELEASE(m_pRootUI);
}

void iLobby::Setup()
{
	m_pRootUI = new UIObject;
}

void iLobby::Update()
{
	if (m_pRootUI)
		m_pRootUI->Update();
}

void iLobby::Render(LPD3DXSPRITE pSprite)
{
	if (m_pRootUI)
		m_pRootUI->Render(pSprite);
}
