#include "stdafx.h"
#include "cPhysXManager.h"
#include "DEBUG_RENDERER.h"
#include "cCar.h"

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
	newPhysXUserData->Reset();
	SetPhysXData(newPhysXUserData);

	E_PHYSX_MATERIAL_NONE; {/*default*/}
	E_PHYSX_MATERIAL_MAP; {
		NxMaterialDesc material;
		material.setToDefault();
		material.restitution = 0.3;
		material.staticFriction = 0.5f;
		material.dynamicFriction = 0.2f;
		m_pNxScene->createMaterial(material);

	}
	E_PHYSX_MATERIAL_CAR; {
		NxMaterialDesc material;
		material.setToDefault();
		material.restitution = 0.3f;
		material.staticFriction = 5.f;
		material.dynamicFriction = 3.f;
		m_pNxScene->createMaterial(material);
	}
	E_PHYSX_MATERIAL_03; {
		NxMaterialDesc material;
		material.setToDefault();
		material.restitution = 0.6f;
		material.staticFriction = 10.f;
		material.dynamicFriction = 8.f;
		m_pNxScene->createMaterial(material);
	}
	E_PHYSX_MATERIAL_04; {
		NxMaterialDesc material;
		material.setToDefault();
		material.restitution = 0.6f;
		material.staticFriction = 10.f;
		material.dynamicFriction = 8.f;
		m_pNxScene->createMaterial(material);
	}
	E_PHYSX_MATERIAL_05; {
		NxMaterialDesc material;
		material.setToDefault();
		material.restitution = 0.6f;
		material.staticFriction = 10.f;
		material.dynamicFriction = 8.f;
		m_pNxScene->createMaterial(material);
	}
	E_PHYSX_MATERIAL_06; {
		NxMaterialDesc material;
		material.setToDefault();
		material.restitution = 0.6f;
		material.staticFriction = 10.f;
		material.dynamicFriction = 8.f;
		m_pNxScene->createMaterial(material);
	}






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
	if (pDebugRenderer) pDebugRenderer->RenderData(MgrPhysXScene->getDebugRenderable());
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
	}
	return true;
}

void ContactCallBack::onContactNotify(NxContactPair & pair, NxU32 _event)
{
	USERDATA* pUserData0 = (USERDATA*)pair.actors[0]->userData;
	USERDATA* pUserData1 = (USERDATA*)pair.actors[1]->userData;
	if (pUserData0 == NULL || pUserData1 == NULL) return;

	switch (_event)
	{
	case NX_NOTIFY_ON_START_TOUCH:
	{
		pUserData0->ContactPairFlag = NX_NOTIFY_ON_START_TOUCH;
		pUserData1->ContactPairFlag = NX_NOTIFY_ON_START_TOUCH;


	}break;
	case NX_NOTIFY_ON_TOUCH:
	{
		pUserData0->ContactPairFlag = NX_NOTIFY_ON_TOUCH;
		pUserData1->ContactPairFlag = NX_NOTIFY_ON_TOUCH;


	}break;
	case NX_NOTIFY_ON_END_TOUCH:
	{
		pUserData0->ContactPairFlag = NX_NOTIFY_ON_END_TOUCH;
		pUserData1->ContactPairFlag = NX_NOTIFY_ON_END_TOUCH;


	}break;
	default:
		pUserData0->ContactPairFlag = 0;
		pUserData1->ContactPairFlag = 0;
		break;
	}
}

void TriggerCallback::onTrigger(NxShape & triggerShape, NxShape & otherShape, NxTriggerFlag status)
{
	USERDATA* pUserData0 = (USERDATA*)triggerShape.getActor().userData;;
	USERDATA* pUserData1 = (USERDATA*)otherShape.getActor().userData;;
	if (pUserData0 == NULL || pUserData1 == NULL) return;

	if (status & NX_TRIGGER_ON_ENTER)
	{
		pUserData0->TriggerPairFlag = NX_TRIGGER_ON_ENTER;
		pUserData1->TriggerPairFlag = NX_TRIGGER_ON_ENTER;

		pUserData0->TargetPointValue.push_back(pUserData1->UserPointValue);
		pUserData1->TargetPointValue.push_back(pUserData0->UserPointValue);


		if (pUserData0->CheckBoxID == pUserData1->CheckBoxID)
		{
			pUserData1->CheckBoxID += 1;
		}
	}
	else if (status & NX_TRIGGER_ON_STAY)
	{
		pUserData0->TriggerPairFlag = NX_TRIGGER_ON_STAY;
		pUserData1->TriggerPairFlag = NX_TRIGGER_ON_STAY;

	}
	else if (status & NX_TRIGGER_ON_LEAVE)
	{

		//	std::cout << "NX_TRIGGER_ON_ENTER";
		// 2가 중력자탄
		if (pUserData0->USER_TAG == E_PHYSX_TAG_GRIVATEBALL)
		{
			triggerShape.getActor().addForce(NxVec3(0, 300000, 0));
			triggerShape.getActor().addTorque(NxVec3(1.5f, 0, 0));
		}
		else if (pUserData1->USER_TAG == E_PHYSX_TAG_GRIVATEBALL)
		{
			otherShape.getActor().addForce(NxVec3(0, 300000, 0));
			otherShape.getActor().addLocalTorque(NxVec3(1.5f, 0, 0));
		}

		else
		{
			pUserData0->TriggerPairFlag = 0;
			pUserData1->TriggerPairFlag = 0;
		}


		for (int i = 0; i < pUserData0->TargetPointValue.size(); i++)
		{
			if (pUserData0->TargetPointValue[i] == pUserData1->UserPointValue)
			{
				pUserData0->TargetPointValue.erase(pUserData0->TargetPointValue.begin() + i);
				i--;
			}
		}
		for (int i = 0; i < pUserData1->TargetPointValue.size(); i++)
		{
			if (pUserData1->TargetPointValue[i] == pUserData0->UserPointValue)
			{
				pUserData1->TargetPointValue.erase(pUserData1->TargetPointValue.begin() + i);
				i--;
			}
		}
	}

}

NxVehicle* cPhysXManager::createCarWithDesc(NxVec3 pos, stCARSPEC carspec, USERDATA* pUserData, bool frontWheelDrive, bool backWheelDrive)
{
	//monsterTruck = true;
	NxVehicleDesc vehicleDesc;
	NxBoxShapeDesc boxShapes[2];

	if (carspec.vecBoxDesc.size() == 2)
	{
		vehicleDesc.carShapes.pushBack(&carspec.vecBoxDesc[0]);
		vehicleDesc.carShapes.pushBack(&carspec.vecBoxDesc[1]);
	}
	else
	{
		boxShapes[0].dimensions.set(0.65, 0.1f, 0.3f);
		boxShapes[0].localPose.t.set(0.f, 0.3f, 0.f);
		boxShapes[0].materialIndex = 1;
		vehicleDesc.carShapes.pushBack(&boxShapes[0]);

		boxShapes[1].dimensions.set(0.3, 0.1f, 0.25f);
		boxShapes[1].localPose.t.set(-0.1f, 0.4, 0.f);
		boxShapes[1].materialIndex = 1;
		vehicleDesc.carShapes.pushBack(&boxShapes[1]);
	}

	vehicleDesc.position = pos;
	vehicleDesc.mass = 1000;//monsterTruck ? 12000 : 
	vehicleDesc.digitalSteeringDelta = 0.04f;
	vehicleDesc.steeringMaxAngle = 30.f;
	vehicleDesc.motorForce = 3500.f;//monsterTruck?180.f:
	vehicleDesc.maxVelocity = 30.f;//(monsterTruck)?20.f:

	vehicleDesc.centerOfMass.set(0.f, 0.1f, 0.f);

	NxWheelDesc wheelDesc[4];
	for (NxU32 i = 0; i < 4; i++)
	{
		wheelDesc[i].wheelApproximation = 10;
		wheelDesc[i].wheelRadius = 0.1f;
		wheelDesc[i].wheelWidth = 0.01f;
		wheelDesc[i].wheelSuspension = 0.00f;
		wheelDesc[i].springRestitution = 7000;
		wheelDesc[i].springDamping = 800;
		wheelDesc[i].springBias = 0.2f;
		wheelDesc[i].maxBrakeForce = 1.f;
		wheelDesc[i].wheelFlags |= NX_WF_USE_WHEELSHAPE;


		//바퀴의 마찰력
		wheelDesc[i].frictionToFront = 3.f;
		wheelDesc[i].frictionToSide = 1.f;

		vehicleDesc.carWheels.pushBack(&wheelDesc[i]);
	}

	if (carspec.vecWheelPos.size() == 4)
	{
#define WHEELPOS carspec.vecWheelPos

		wheelDesc[0].position.set(WHEELPOS[0].x, WHEELPOS[0].y, WHEELPOS[0].z);
		wheelDesc[1].position.set(WHEELPOS[1].x, WHEELPOS[1].y, WHEELPOS[1].z);
		wheelDesc[2].position.set(WHEELPOS[2].x, WHEELPOS[2].y, WHEELPOS[2].z);
		wheelDesc[3].position.set(WHEELPOS[3].x, WHEELPOS[3].y, WHEELPOS[3].z);
	}
	else
	{
		wheelDesc[0].position.set(0.35f, 0.2f, -0.29f);
		wheelDesc[1].position.set(0.35, 0.2f, 0.29);
		wheelDesc[2].position.set(-0.45, 0.2f, -0.29);
		wheelDesc[3].position.set(-0.45, 0.2f, 0.29);
	}


	NxU32 flags = NX_WF_BUILD_LOWER_HALF;
	wheelDesc[0].wheelFlags |= (frontWheelDrive ? NX_WF_ACCELERATED : 0) | NX_WF_STEERABLE_INPUT | flags;
	wheelDesc[1].wheelFlags |= (frontWheelDrive ? NX_WF_ACCELERATED : 0) | NX_WF_STEERABLE_INPUT | flags;
	wheelDesc[2].wheelFlags |= (backWheelDrive ? NX_WF_ACCELERATED : 0) | NX_WF_AFFECTED_BY_HANDBRAKE | flags;
	wheelDesc[3].wheelFlags |= (backWheelDrive ? NX_WF_ACCELERATED : 0) | NX_WF_AFFECTED_BY_HANDBRAKE | flags;

	vehicleDesc.steeringSteerPoint.set(1.8f, 0, 0);
	vehicleDesc.steeringTurnPoint.set(-1.5f, 0, 0);



	NxVehicle* vehicle = NxVehicle::createVehicle(MgrPhysXScene, &vehicleDesc);
	NxQuat q;
	q.fromAngleAxis(0.f, NxVec3(0.0f, 1.0f, 0.0f));
	vehicle->getActor()->setGlobalOrientationQuat(q);

	if (pUserData) vehicle->getActor()->userData = pUserData;

	if (vehicle) return vehicle;
	else
	{
		std::string pritfOut("자동차가의 물리정보가 생성되지 않았습니다.");
		MessageBoxA(g_hWnd, pritfOut.c_str(), "심각한 오류", MB_OK);
	}
}
