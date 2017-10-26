#pragma once
#include "cMesh.h"
#include "cPhysX.h"

class Object
{
public:

	Object();
	~Object();

	SYNTHESIZE_VIRTUAL(cMesh*, m_pMeshData, MeshData);
	SYNTHESIZE_VIRTUAL(cPhysX*, m_PhysXData, PhysXData);

public:
	virtual void Setup();
	virtual void Destory();
	virtual void Update();
	virtual void LastUpdate();
	virtual void Render();

};

