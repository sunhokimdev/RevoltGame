#pragma once
#include "UserStream.h"

class DEBUG_RENDER;

#define g_pPhysXManager PhysXManager::GetInstance()
#define g_pPhysXManagerScene PhysXManager::GetInstance()->GetPhysXScene()
#define g_pPhysXManagerSDK   PhysXManager::GetInstance()->GetPhysXSDK()

struct USERDATA
{
	NxU32 ContactPairFlag;
	USERDATA() { ContactPairFlag = 0; }
};

enum E_MATERIAL
{
	E_MATERIAL_DEFAULT = 0,
	E_MATERIAL_1,
	E_MATERIAL_2,
	E_MATERIAL_3,
	E_MATERIAL_4,
	E_MATERIAL_5,
};

//충돌확인
class ContactCallBack : public NxUserContactReport
{
	void onContactNotify(NxContactPair& pair, NxU32 _event);
};

class PhysXManager
{
private:
	DEBUG_RENDER** m_ppDebugRender;

	NxPhysicsSDK*	m_pNxPhysicsSDK;
	NxScene*		m_pNxScene;

	std::map<E_MATERIAL, NxMaterial*> m_mapMaterial;
public:
	SINGLETONE(PhysXManager);

	NxPhysicsSDK* GetPhysXSDK() { return m_pNxPhysicsSDK; }
	NxScene* GetPhysXScene() { return m_pNxScene; }
	void Destory();

	NxTriangleMeshShapeDesc CreateTringleMesh(ID3DXMesh* pMesh, D3DXMATRIXA16* matS = NULL);

	void D3DVecToNxVec(NxVec3& vec, D3DXVECTOR3& Dvec3)
	{
		vec.x = Dvec3.x;
		vec.y = Dvec3.y;
		vec.z = Dvec3.z;
	}
	void D3DMatToNxMat(NxF32* mtl, D3DMATRIX* Dmat)
	{
		mtl[0] = Dmat->_11;
		mtl[1] = Dmat->_12;
		mtl[2] = Dmat->_13;
		mtl[3] = Dmat->_21;
		mtl[4] = Dmat->_22;
		mtl[5] = Dmat->_23;
		mtl[6] = Dmat->_31;
		mtl[7] = Dmat->_32;
		mtl[8] = Dmat->_33;
	}
};

