#include "stdafx.h"
#include "cItem.h"

cItem::cItem()
	: m_fTime(0.0f)
	, m_id(0)
	, m_isUse(false)
	, m_pUser(NULL)
	, m_pPhysX(NULL)
	, m_isInit(true)
{
}

cItem::~cItem()
{
	SAFE_DELETE(m_pUser);
	SAFE_DELETE(m_pPhysX);
}

void cItem::Setup()
{
	Object::Setup();

	m_pUser = new USERDATA;

	m_pPhysX = new ST_PHYSX;
	m_pPhysX->pPhysX = new cPhysX;
	m_pPhysX->pTrigger = new cPhysX;
}

void cItem::Update()
{
	if(m_isUse)
		m_fTime++;

	Object::Update();
}

void cItem::Render()
{
	Object::Render();
}

void cItem::Create(D3DXVECTOR3 angle, D3DXVECTOR3 pos)
{

}

void cItem::SetActorGroup(NxActor * actor, NxCollisionGroup group)
{
	NxU32 nbShapes = actor->getNbShapes();
	NxShape** shapes = (NxShape**)actor->getShapes();

	while (nbShapes--)
	{
		shapes[nbShapes]->setGroup(group);
	}
}
