#include "stdafx.h"
#include "PhysXManager.h"
#include "DEBUG_RENDER.h"

PhysXManager::PhysXManager()
{
	NxSceneDesc sceneDesc;

	m_pNxPhysicsSDK = NxCreatePhysicsSDK(NX_PHYSICS_SDK_VERSION);
	if ((m_pNxPhysicsSDK) == NULL)
	{
		return;
	}

	m_pNxPhysicsSDK->setParameter(NX_SKIN_WIDTH, 0.0f);
	if (*m_ppDebugRender == NULL)
	{
		m_pNxPhysicsSDK->setParameter(NX_VISUALIZATION_SCALE, 3);
		m_pNxPhysicsSDK->setParameter(NX_VISUALIZE_COLLISION_SHAPES, 1);
		m_pNxPhysicsSDK->setParameter(NX_VISUALIZE_ACTOR_AXES, 1);
		(*m_ppDebugRender) = new DEBUG_RENDER;
	}

	sceneDesc.gravity = NxVec3(0.0f, -9.81f, 0.0f);

	NxHWVersion HWVersion = m_pNxPhysicsSDK->getHWVersion();
	if (HWVersion != NX_HW_VERSION_NONE)
		sceneDesc.simType = NX_SIMULATION_HW;

	m_pNxScene = m_pNxPhysicsSDK->createScene(sceneDesc);
	if (m_pNxScene == NULL)
	{
		return;
	}
}


PhysXManager::~PhysXManager()
{
}


void PhysXManager::Destory()
{
	if (m_pNxPhysicsSDK != NULL)
	{
		if (m_pNxScene != NULL)
		{
			m_pNxPhysicsSDK->releaseScene(*m_pNxScene);
			m_pNxScene = NULL;
		}
		NxReleasePhysicsSDK(m_pNxPhysicsSDK);
		m_pNxPhysicsSDK = NULL;
	}
}

NxTriangleMeshShapeDesc PhysXManager::CreateTringleMesh(ID3DXMesh * pMesh, D3DXMATRIXA16 * matS)
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
		pMesh->CloneMeshFVF(pMesh->GetOptions(), D3DFVF_XYZ, g_pD3DDevice, &pTempMesh);

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
//		NxInitCooking();
//		MemoryWriteBuffer buf;
//		if (NxCookTriangleMesh(meshDesc, buf))
//		{
//			pTriangleMesh = g_pPhysXManagerSDK->createTriangleMesh(MemoryReadBuffer(buf.data));
//			if (pTriangleMesh)
//			{
//				meshShapeDesc.meshData = pTriangleMesh;
//			}
//		}
//		NxCloseCooking();
//
//		SAFE_RELEASE(pTempMesh);
//		SAFE_DELETE_ARRAY(pVec);
//		SAFE_DELETE_ARRAY(pIndex);
	}
	return meshShapeDesc;
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

		std::cout << "NX_NOTIFY_ON_START_TOUCH" << std::endl;

	}break;
	case NX_NOTIFY_ON_END_TOUCH:
	{
		pUserData0 = (USERDATA*)pair.actors[0]->userData;
		pUserData1 = (USERDATA*)pair.actors[1]->userData;

		pUserData0->ContactPairFlag = 0;
		pUserData1->ContactPairFlag = 0;

		std::cout << "NX_NOTIFY_ON_END_TOUCH" << std::endl;

	}break;
	}
}
