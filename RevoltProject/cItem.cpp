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
	//물리적용
	this->GetPhysXData()->m_pActor;

	Object::Update();
}

void cItem::Render()
{
	Object::Render();
}
