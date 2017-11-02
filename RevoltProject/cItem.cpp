#include "stdafx.h"
#include "cItem.h"

cItem::cItem()
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

void cItem::Create()
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
