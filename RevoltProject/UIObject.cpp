#include "stdafx.h"
#include "UIObject.h"


UIObject::UIObject()
	: m_vPosition(0, 0, 0)
	, m_pParent(NULL)
	, m_stSize(0, 0)
	, m_nTag(0)
	, m_isHidden(false)
{
}

UIObject::~UIObject()
{
}

void UIObject::Release()
{
}

void UIObject::SetPosition(float x, float y, float z)
{
	m_vPosition.x = x;
	m_vPosition.y = y;
	m_vPosition.z = z;
}

void UIObject::AddChild(UIObject * pChild)
{
	pChild->SetParent(this);
	m_vecChild.push_back(pChild);
}

void UIObject::Update()
{
	if (m_isHidden) return;

	D3DXMatrixIdentity(&m_matWorld);

	m_matWorld._41 = m_vPosition.x;
	m_matWorld._42 = m_vPosition.y;
	m_matWorld._43 = m_vPosition.z;

	if (m_pParent)
	{
		m_matWorld._41 += m_pParent->m_matWorld._41;
		m_matWorld._42 += m_pParent->m_matWorld._42;
		m_matWorld._43 += m_pParent->m_matWorld._43;
	}

	for each(auto c in m_vecChild)
	{
		c->Update();
	}
}

void UIObject::Render(LPD3DXSPRITE pSprite)
{
	if (m_isHidden) return;
	D3DXMATRIXA16 matS;

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);

	for each(auto c in m_vecChild)
	{
		c->Render(pSprite);
	}
}

void UIObject::Destroy()
{
	m_isHidden = true;

	for each(auto c in m_vecChild)
	{
		c->Destroy();
		SAFE_DELETE(c);
	}
	m_vecChild.clear();
	this->Release();
}

UIObject * UIObject::FindChildByTag(int nTag)
{
	if (m_nTag == nTag)
		return this;

	for each(auto c in m_vecChild)
	{
		UIObject* p = c->FindChildByTag(nTag);
		if (p) return p;
	}

	return nullptr;
}
