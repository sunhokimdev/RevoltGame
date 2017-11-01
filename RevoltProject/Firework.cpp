#include "stdafx.h"
#include "Firework.h"
#include "ObjectLoader.h"

Firework::Firework()
{
}


Firework::~Firework()
{

}

void Firework::Setup()
{
	ObjectLoader load;
	m_pObjMesh = load.LoadMesh(m_vecObjMtlTex, "Objects/firework", "firework.obj");
}

void Firework::Update()
{
	cItem::Update();
}

void Firework::Render()
{
	cItem::Render();

}
