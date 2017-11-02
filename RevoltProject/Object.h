#pragma once
#include "cMesh.h"
#include "cPhysX.h"
#include "cTransform.h"


enum eOBJECT_TAG
{
	E_OBJECT_CHECKBOX,
	E_OBJECT_FOLLOWPOINT,
	E_OBJECT_CAR,
	E_OBJECT_MAP,
	E_OBJECT_LIGHT,
	E_OBJECT_STUFF,
	E_OBJECT_CAMERA,
	E_OBJECT_PICKUP,
	E_OBJECT_END,
	E_OBJECT_NONE,
};

enum eOBJECT_STATE
{
	E_OBJECT_STATE_NONE,
	E_OBJECT_STATE_SELECT,
	E_OBJECT_STATE_CANSLE,
	E_OBJECT_STATE_DELETE,
};

enum eOBJECT_ID
{
	E_OBJ_ID_CEHCKBOX,
	E_OBJ_ID_FOLLOWPOINT,
	E_OBJ_ID_STUFF_CHEESE,
	E_OBJ_ID_STUFF_CHICKEN,
	E_OBJ_ID_STUFF_FABRIC,
	E_OBJ_ID_STUFF_KIDRIDE,
	E_OBJ_ID_PICKUP,
	E_OBJ_ID_STAR,
};


class Object : public cTransform
{
protected:

	Object();
	~Object();

	cMesh* m_pMeshData;
	cPhysX* m_PhysXData;

	SYNTHESIZE(eOBJECT_TAG, m_objTag, Tag);
	SYNTHESIZE(eOBJECT_ID, m_eID, ID);
	SYNTHESIZE(std::string, m_objName, ObjName);
	SYNTHESIZE(bool, m_isEnable, m_isEnable);
public:
	cMesh* GetMeshData() { return m_pMeshData; }
	void SetMeshData(cMesh* pMesh) {
		if (pMesh)
		{
			if (m_pMeshData)
			{
				m_pMeshData->Destory();
			}
			m_pMeshData = pMesh;
		}
	}
	cPhysX*	GetPhysXData() { return m_PhysXData; }
	void SetPhysXData(cPhysX* pPhysX)
	{
		if (pPhysX)
		{
			if (m_PhysXData)
			{
				m_PhysXData->Destory();
			}
			else
			{
				m_PhysXData = new cPhysX;
			}
			m_PhysXData->m_pActor = pPhysX->m_pActor;
			m_PhysXData->m_pUserData = pPhysX->m_pUserData;
		}
	}

	virtual void Setup();
	virtual void Destroy();
	virtual void Update();
	virtual void LastUpdate();
	virtual void Render();
};

