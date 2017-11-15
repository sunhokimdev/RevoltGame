#include "stdafx.h"
#include "PickUpObject.h"
#include "ObjectLoader.h"

PickUpObject::PickUpObject()
{
}


PickUpObject::~PickUpObject()
{
}

void PickUpObject::Setup()
{
	ObjectLoader load;

	m_pObjMesh = load.LoadMesh(m_vecObjMtlTex, "Objects/pickup", "pickup.obj");
}

void PickUpObject::Update()
{
	m_yAngle += D3DX_PI / 30.0f;

	if (m_yAngle > 2 * D3DX_PI)
		m_yAngle = 0.0f;

	Thing::Update();
}

void PickUpObject::Render()
{
	Thing::Render();
}

void PickUpObject::Destroy()
{
	Thing::Destroy();
}
