#include "stdafx.h"
#include "cPhysXManager.h"
#include "DEBUG_RENDERER.h"


#include "NxCooking.h"


cPhysXManager::cPhysXManager()
{
}


cPhysXManager::~cPhysXManager()
{
}

BOOL cPhysXManager::InitNxPhysX()
{
	NxSceneDesc sceneDesc;


	m_pNxPhysicsSDK = NxCreatePhysicsSDK(NX_PHYSICS_SDK_VERSION);
	if ((m_pNxPhysicsSDK) == NULL)
	{
		return S_FALSE;
	}

	m_pNxPhysicsSDK->setParameter(NX_SKIN_WIDTH, 0.0f);
	if (pDebugRenderer == NULL)
	{
		m_pNxPhysicsSDK->setParameter(NX_VISUALIZATION_SCALE, 3);
		m_pNxPhysicsSDK->setParameter(NX_VISUALIZE_COLLISION_SHAPES, 1);
		m_pNxPhysicsSDK->setParameter(NX_VISUALIZE_ACTOR_AXES, 1);
		m_pNxPhysicsSDK->setParameter(NX_VISUALIZE_JOINT_LIMITS, 1);

		(pDebugRenderer) = new DEBUG_RENDERER;
	}

	sceneDesc.gravity = NxVec3(0.0f, -9.81f, 0.0f);

	NxHWVersion HWVersion = m_pNxPhysicsSDK->getHWVersion();
	if (HWVersion != NX_HW_VERSION_NONE)
		sceneDesc.simType = NX_SIMULATION_HW;

	m_pNxScene = m_pNxPhysicsSDK->createScene(sceneDesc);
	if (m_pNxScene == NULL)
	{
		return S_FALSE;
	}

	m_physXUserData = NULL;
	PHYSXDATA*  newPhysXUserData = new PHYSXDATA;
	newPhysXUserData->Init();
	SetPhysXData(newPhysXUserData);




	//NxMaterialDesc defaultMaterial;
	//defaultMaterial.setToDefault();
	//defaultMaterial.restitution = 1.0f;
	//defaultMaterial.staticFriction = 10.f;
	//defaultMaterial.dynamicFriction = 8.f;
	//m_pNxScene->createMaterial(defaultMaterial);

//	m_pNxPhysicsSDK->setParameter(NX_VISUALIZATION_SCALE, 2);





	return S_OK;
}

void cPhysXManager::Destory()
{
	if (m_pNxPhysicsSDK != NULL)
	{
		if (m_pNxScene != NULL)
		{
			NxU32 actorCount = m_pNxScene->getNbActors();
			for (NxU32 i = 0; i < actorCount; i++)
			{
				NxActor* p = m_pNxScene->getActors()[i];
				m_pNxScene->releaseActor(*p);
			}
			m_pNxPhysicsSDK->releaseScene(*m_pNxScene);
			m_pNxScene = NULL;
		}
		NxReleasePhysicsSDK(m_pNxPhysicsSDK);
		m_pNxPhysicsSDK = NULL;
	}
}

void cPhysXManager::Render()
{
	if(pDebugRenderer) pDebugRenderer->RenderData(MgrPhysXScene->getDebugRenderable());
}

NxTriangleMeshShapeDesc cPhysXManager::CreateTringleMesh(ID3DXMesh* pMesh, D3DXMATRIXA16* matS)
{
	NxTriangleMeshShapeDesc meshShapeDesc;
	meshShapeDesc.setToDefault();

	NxTriangleMesh* pTriangleMesh;
	NxTriangleMeshDesc meshDesc;
	NxU32 flg = 0;

	if (pMesh)
	{
		//메쉬 정보 복사
		ID3DXMesh* pTempMesh;
		pMesh->CloneMeshFVF(pMesh->GetOptions(), D3DFVF_XYZ, MgrD3DDevice, &pTempMesh);

		//인덱스의 사이즈를 얻기
		LPDIRECT3DINDEXBUFFER9 pIndexBuffer;
		pTempMesh->GetIndexBuffer(&pIndexBuffer);
		D3DINDEXBUFFER_DESC indexDesc;
		pIndexBuffer->GetDesc(&indexDesc);
		switch (indexDesc.Format)
		{
		case D3DFMT_INDEX16:
			flg |= NX_CF_16_BIT_INDICES;
		}
		SAFE_RELEASE(pIndexBuffer);

		meshDesc.flags = flg;

		meshDesc.numVertices = pTempMesh->GetNumVertices();
		meshDesc.pointStrideBytes = pTempMesh->GetNumBytesPerVertex();
		meshDesc.numTriangles = pTempMesh->GetNumFaces();

		if (flg & NX_CF_16_BIT_INDICES)
			meshDesc.triangleStrideBytes = 3 * sizeof(WORD);
		else
			meshDesc.triangleStrideBytes = 3 * sizeof(DWORD);

		D3DXVECTOR3* pVec = new D3DXVECTOR3[meshDesc.numVertices];

		LPBYTE pIndex = NULL;
		LPBYTE pBits = NULL;

		pTempMesh->LockVertexBuffer(D3DLOCK_READONLY, (PVOID*)&pBits);
		CopyMemory(pVec, pBits, meshDesc.pointStrideBytes * meshDesc.numVertices);
		if (matS)
		{
			for (int i = 0; i < meshDesc.numVertices; i++)
			{
				D3DXVec3TransformCoord(&(pVec[i]), &(pVec[i]), matS);
			}
		}
		meshDesc.points = pVec;
		pTempMesh->UnlockVertexBuffer();

		pIndex = new BYTE[meshDesc.triangleStrideBytes * meshDesc.numTriangles];

		pTempMesh->LockIndexBuffer(D3DLOCK_READONLY, (PVOID*)&pBits);
		CopyMemory(pIndex, pBits, meshDesc.triangleStrideBytes * meshDesc.numTriangles);
		meshDesc.triangles = pIndex;
		pTempMesh->UnlockIndexBuffer();

		//Cooking 초기화
		NxInitCooking();
		MemoryWriteBuffer buf;
		if (NxCookTriangleMesh(meshDesc, buf))
		{
			pTriangleMesh = MgrPhysXSDK->createTriangleMesh(MemoryReadBuffer(buf.data));
			if (pTriangleMesh)
			{
				meshShapeDesc.meshData = pTriangleMesh;
			}
		}
		NxCloseCooking();

		SAFE_RELEASE(pTempMesh);
		SAFE_DELETE_ARRAY(pVec);
		SAFE_DELETE_ARRAY(pIndex);
	}
	return meshShapeDesc;
}

NxBoxShapeDesc cPhysXManager::CreateBoxShape(int materialIndex, NxVec3 boxSize)
{
	NxBoxShapeDesc boxDesc;	boxDesc.setToDefault();
	boxDesc.materialIndex = materialIndex;
	boxDesc.dimensions = boxSize * 0.5f;



	return boxDesc;
}

void cPhysXManager::Update()
{

}

void cPhysXManager::RaycastClosestShape(D3DXVECTOR3 start, D3DXVECTOR3 dir)
{
	NxRay worldRay;

	worldRay.orig = MgrPhysX->D3DVecToNxVec(start);
	worldRay.dir = MgrPhysX->D3DVecToNxVec(dir);

	NxRaycastHit raycastHit;
	MgrPhysXScene->raycastClosestShape(worldRay, NX_ALL_SHAPES, raycastHit);// , 0xffffffff, NX_MAX_F32, 0xffffffff, NULL, NULL);

	if (raycastHit.shape)
	{
		USERDATA* userData = (USERDATA*)raycastHit.shape->getActor().userData;
		if (!userData) return;
		userData->RaycastClosestShape = NX_TRUE;
		userData->RayHitPos = raycastHit.worldImpact;
		MgrPhysXData->RaycastClosestShapePosition = raycastHit.worldImpact;
	}

}

void cPhysXManager::RaycastAllShapes(D3DXVECTOR3 start, D3DXVECTOR3 dir)
{
	NxRay worldRay;

	worldRay.orig = MgrPhysX->D3DVecToNxVec(start);
	worldRay.dir = MgrPhysX->D3DVecToNxVec(dir);

	RaycastCallBack raycastHit;
	MgrPhysXScene->raycastAllShapes(worldRay, raycastHit, NX_ALL_SHAPES);

}

bool RaycastCallBack::onHit(const NxRaycastHit & hit)
{
	NxActor& actor = hit.shape->getActor();
	if (actor.userData)
	{
		USERDATA* userData = (USERDATA*)actor.userData;
		userData->RaycastAllShape = NX_TRUE;
		userData->RayHitPos = hit.worldImpact;
		MgrPhysXData->RaycastAllShapeHitCount++;
	//	std::cout << MgrPhysXData->RaycastAllShapeHitCount << std::endl;
	}
	return true;
}

void ContactCallBack::onContactNotify(NxContactPair & pair, NxU32 _event)
{
	USERDATA* pUserData0 = NULL;
	USERDATA* pUserData1 = NULL;
	switch (_event)
	{
	case NX_NOTIFY_ON_START_TOUCH:
	{
		pUserData0 = (USERDATA*)pair.actors[0]->userData;
		pUserData1 = (USERDATA*)pair.actors[1]->userData;

		pUserData0->ContactPairFlag = NX_NOTIFY_ON_START_TOUCH;
		pUserData1->ContactPairFlag = NX_NOTIFY_ON_START_TOUCH;

	//	std::cout << "NX_NOTIFY_ON_START_TOUCH" << std::endl;

	}break;
	case NX_NOTIFY_ON_END_TOUCH:
	{
		pUserData0 = (USERDATA*)pair.actors[0]->userData;
		pUserData1 = (USERDATA*)pair.actors[1]->userData;

		pUserData0->ContactPairFlag = 0;
		pUserData1->ContactPairFlag = 0;

	//	std::cout << "NX_NOTIFY_ON_END_TOUCH" << std::endl;

	}break;
	}
}

void TriggerCallback::onTrigger(NxShape & triggerShape, NxShape & otherShape, NxTriggerFlag status)
{

	USERDATA* pUserData0 = NULL;
	USERDATA* pUserData1 = NULL;


	pUserData0 = (USERDATA*)triggerShape.getActor().userData;
	pUserData1 = (USERDATA*)otherShape.getActor().userData;

	// other actor is a trigger too?
	if ((NxI32)(otherShape.getActor().userData) < 0)
		return;

	NxActor& triggerActor = triggerShape.getActor();
	NxI32 triggerNumber = -(NxI32)triggerActor.userData;
	NxI32 triggerIndex = triggerNumber - 1;

	//std::cout << "onTrigger ";
	if (status & NX_TRIGGER_ON_LEAVE)
	{
	//	std::cout << "NX_TRIGGER_ON_LEAVE";
	}
	if (status & NX_TRIGGER_ON_ENTER)
	{
	//	std::cout << "NX_TRIGGER_ON_ENTER";
	}
	if (status & NX_TRIGGER_ON_STAY)
	{
	//	std::cout << "NX_TRIGGER_ON_STAY";
	}
	std::cout << std::endl;
}