#include "stdafx.h"
#include "cItem.h"

cItem::cItem()
	: m_fTime(0.0f)
	, m_id(0)
{
}

cItem::~cItem()
{
}

void cItem::Setup()
{
}

void cItem::Update()
{
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
