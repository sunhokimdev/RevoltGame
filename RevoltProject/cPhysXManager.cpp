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
		material.restitution = 0.5;
		material.staticFriction = 0.2f;
		material.dynamicFriction = 0.1f;
		m_pNxScene->createMaterial(material);
	}
	E_PHYSX_MATERIAL_CAR; {
		NxMaterialDesc material;
		material.setToDefault();
		material.restitution = 0.5;
		material.staticFriction = 0.2f;
		material.dynamicFriction = 0.1f;
		m_pNxScene->createMaterial(material);
	}
	E_PHYSX_MATERIAL_GRIVATEBALL; {
		NxMaterialDesc material;
		material.setToDefault();
		material.restitution = 1.0f;
		material.staticFriction = 0.f;
		material.dynamicFriction = 0.f;
		m_pNxScene->createMaterial(material);
	}
	E_PHYSX_MATERIAL_WHATEBOMB; {
		NxMaterialDesc material;
		material.setToDefault();
		material.restitution = 0.5f;
		material.staticFriction = 5.f;
		material.dynamicFriction = 3.f;
		m_pNxScene->createMaterial(material);
	}
	E_PHYSX_MATERIAL_ETC; {
		NxMaterialDesc material;
		material.setToDefault();
		material.restitution = 0.3f;
		material.staticFriction = 10.f;
		material.dynamicFriction = 10.f;
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


	//	해당 {} 내부의 순서 변경 금지
	{
		PhysXReportSeting();
		g_pPhysXScene->setUserTriggerReport(new TriggerCallback());
		g_pPhysXScene->setUserContactReport(new ContactCallBack());
	}


	//	
	m_IS_DEBUG_RENDER = true;
	return S_OK;
}

void cPhysXManager::Destroy()
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
	if (m_IS_DEBUG_RENDER && pDebugRenderer) pDebugRenderer->RenderData(MgrPhysXScene->getDebugRenderable());
}

void cPhysXManager::PhysXReportSeting()
{
	const bool T = true;
	const bool F = false;
	//CollisionEnable(충돌,리보트,그룹1,그룹2);
	CollisionEnable(T, F, E_PHYSX_TAG_NONE, E_PHYSX_TAG_NONE);
	CollisionEnable(F, F, E_PHYSX_TAG_NONE, E_PHYSX_TAG_CHECKBOX);
	CollisionEnable(T, F, E_PHYSX_TAG_NONE, E_PHYSX_TAG_CAR);
	CollisionEnable(T, F, E_PHYSX_TAG_NONE, E_PHYSX_TAG_PICKUP);
	CollisionEnable(T, F, E_PHYSX_TAG_NONE, E_PHYSX_TAG_FIREWORK);
	CollisionEnable(T, F, E_PHYSX_TAG_NONE, E_PHYSX_TAG_WHATEBOMB);
	CollisionEnable(T, F, E_PHYSX_TAG_NONE, E_PHYSX_TAG_METALBALL);
	CollisionEnable(F, F, E_PHYSX_TAG_NONE, E_PHYSX_TAG_GRIVATEBALL);
	CollisionEnable(T, F, E_PHYSX_TAG_NONE, E_PHYSX_TAG_TRACK);

	CollisionEnable(F, F, E_PHYSX_TAG_CHECKBOX, E_PHYSX_TAG_CHECKBOX);
	CollisionEnable(T, T, E_PHYSX_TAG_CHECKBOX, E_PHYSX_TAG_CAR);
	CollisionEnable(F, F, E_PHYSX_TAG_CHECKBOX, E_PHYSX_TAG_PICKUP);
	CollisionEnable(F, F, E_PHYSX_TAG_CHECKBOX, E_PHYSX_TAG_FIREWORK);
	CollisionEnable(F, F, E_PHYSX_TAG_CHECKBOX, E_PHYSX_TAG_WHATEBOMB);
	CollisionEnable(F, F, E_PHYSX_TAG_CHECKBOX, E_PHYSX_TAG_METALBALL);
	CollisionEnable(F, F, E_PHYSX_TAG_CHECKBOX, E_PHYSX_TAG_GRIVATEBALL);
	CollisionEnable(F, F, E_PHYSX_TAG_CHECKBOX, E_PHYSX_TAG_TRACK);

	CollisionEnable(T, T, E_PHYSX_TAG_CAR, E_PHYSX_TAG_CAR);
	CollisionEnable(T, T, E_PHYSX_TAG_CAR, E_PHYSX_TAG_PICKUP);
	CollisionEnable(T, T, E_PHYSX_TAG_CAR, E_PHYSX_TAG_FIREWORK);
	CollisionEnable(T, T, E_PHYSX_TAG_CAR, E_PHYSX_TAG_WHATEBOMB);
	CollisionEnable(T, T, E_PHYSX_TAG_CAR, E_PHYSX_TAG_METALBALL);
	CollisionEnable(T, T, E_PHYSX_TAG_CAR, E_PHYSX_TAG_GRIVATEBALL);
	CollisionEnable(T, T, E_PHYSX_TAG_CAR, E_PHYSX_TAG_FAKEBOMB);
	CollisionEnable(T, T, E_PHYSX_TAG_CAR, E_PHYSX_TAG_TRACK);

	CollisionEnable(T, T, E_PHYSX_TAG_PICKUP, E_PHYSX_TAG_PICKUP);
	CollisionEnable(T, T, E_PHYSX_TAG_PICKUP, E_PHYSX_TAG_FIREWORK);
	CollisionEnable(T, T, E_PHYSX_TAG_PICKUP, E_PHYSX_TAG_WHATEBOMB);
	CollisionEnable(T, T, E_PHYSX_TAG_PICKUP, E_PHYSX_TAG_METALBALL);
	CollisionEnable(F, T, E_PHYSX_TAG_PICKUP, E_PHYSX_TAG_GRIVATEBALL);
	CollisionEnable(T, T, E_PHYSX_TAG_PICKUP, E_PHYSX_TAG_TRACK);

	CollisionEnable(T, T, E_PHYSX_TAG_FIREWORK, E_PHYSX_TAG_FIREWORK);
	CollisionEnable(T, T, E_PHYSX_TAG_FIREWORK, E_PHYSX_TAG_WHATEBOMB);
	CollisionEnable(T, T, E_PHYSX_TAG_FIREWORK, E_PHYSX_TAG_METALBALL);
	CollisionEnable(F, T, E_PHYSX_TAG_FIREWORK, E_PHYSX_TAG_GRIVATEBALL);
	CollisionEnable(T, T, E_PHYSX_TAG_FIREWORK, E_PHYSX_TAG_TRACK);

	CollisionEnable(T, T, E_PHYSX_TAG_WHATEBOMB, E_PHYSX_TAG_WHATEBOMB);
	CollisionEnable(T, T, E_PHYSX_TAG_WHATEBOMB, E_PHYSX_TAG_METALBALL);
	CollisionEnable(F, T, E_PHYSX_TAG_WHATEBOMB, E_PHYSX_TAG_GRIVATEBALL);
	CollisionEnable(T, T, E_PHYSX_TAG_WHATEBOMB, E_PHYSX_TAG_TRACK);

	CollisionEnable(T, T, E_PHYSX_TAG_METALBALL, E_PHYSX_TAG_METALBALL);
	CollisionEnable(F, T, E_PHYSX_TAG_METALBALL, E_PHYSX_TAG_GRIVATEBALL);
	CollisionEnable(T, T, E_PHYSX_TAG_METALBALL, E_PHYSX_TAG_TRACK);

	CollisionEnable(T, T, E_PHYSX_TAG_GRIVATEBALL, E_PHYSX_TAG_GRIVATEBALL);
	CollisionEnable(T, T, E_PHYSX_TAG_GRIVATEBALL, E_PHYSX_TAG_TRACK);

	CollisionEnable(F, F, E_PHYSX_TAG_TRACK, E_PHYSX_TAG_TRACK);

	//Add
	CollisionEnable(T, F, E_PHYSX_TAG_RAYCAST_TO_AI, E_PHYSX_TAG_NONE);
	CollisionEnable(F, F, E_PHYSX_TAG_RAYCAST_TO_AI, E_PHYSX_TAG_CHECKBOX);
	CollisionEnable(F, F, E_PHYSX_TAG_RAYCAST_TO_AI, E_PHYSX_TAG_CAR);
	CollisionEnable(F, F, E_PHYSX_TAG_RAYCAST_TO_AI, E_PHYSX_TAG_PICKUP);
	CollisionEnable(F, F, E_PHYSX_TAG_RAYCAST_TO_AI, E_PHYSX_TAG_FIREWORK);
	CollisionEnable(F, F, E_PHYSX_TAG_RAYCAST_TO_AI, E_PHYSX_TAG_WHATEBOMB);
	CollisionEnable(F, F, E_PHYSX_TAG_RAYCAST_TO_AI, E_PHYSX_TAG_METALBALL);
	CollisionEnable(F, F, E_PHYSX_TAG_RAYCAST_TO_AI, E_PHYSX_TAG_MYBOMB);
	CollisionEnable(F, F, E_PHYSX_TAG_RAYCAST_TO_AI, E_PHYSX_TAG_GRIVATEBALL);
	CollisionEnable(T, F, E_PHYSX_TAG_RAYCAST_TO_AI, E_PHYSX_TAG_TRACK);
	CollisionEnable(F, F, E_PHYSX_TAG_RAYCAST_TO_AI, E_PHYSX_TAG_RAYCAST_TO_AI);


	return;	//END
	CollisionEnable(F, F, E_PHYSX_TAG_END, E_PHYSX_TAG_NONE);
	CollisionEnable(F, F, E_PHYSX_TAG_END, E_PHYSX_TAG_CHECKBOX);
	CollisionEnable(F, F, E_PHYSX_TAG_END, E_PHYSX_TAG_CAR);
	CollisionEnable(F, F, E_PHYSX_TAG_END, E_PHYSX_TAG_PICKUP);
	CollisionEnable(F, F, E_PHYSX_TAG_END, E_PHYSX_TAG_FIREWORK);
	CollisionEnable(F, F, E_PHYSX_TAG_END, E_PHYSX_TAG_WHATEBOMB);
	CollisionEnable(F, F, E_PHYSX_TAG_END, E_PHYSX_TAG_METALBALL);
	CollisionEnable(F, F, E_PHYSX_TAG_END, E_PHYSX_TAG_GRIVATEBALL);
	CollisionEnable(F, F, E_PHYSX_TAG_END, E_PHYSX_TAG_TRACK);
	CollisionEnable(F, F, E_PHYSX_TAG_END, E_PHYSX_TAG_RAYCAST_TO_AI);
	CollisionEnable(F, F, E_PHYSX_TAG_END, E_PHYSX_TAG_END);
}

void cPhysXManager::CollisionEnable(bool collied, bool report, NxCollisionGroup group1, NxCollisionGroup group2)
{
	g_pPhysXScene->setGroupCollisionFlag(group1, group2, collied);
	g_pPhysXScene->setActorGroupPairFlags(group1, group2, report);
	//	g_pPhysXScene->setShapePairFlags(NULL, NULL, NX_SF_DISABLE_RAYCASTING);
		//	g_pPhysXScene->setDominanceGroupPair

	//	g_pPhysXScene->setShapePairFlags()
}


void cPhysXManager::SetActorGroup(NxActor * actor, NxCollisionGroup group)
{
	if (!actor) return;
	actor->setGroup(group);

	NxU32 nbShapes = actor->getNbShapes();
	NxShape** shapes = (NxShape**)actor->getShapes();
	for (int i = 0; i < actor->getNbShapes(); i++)
	{
		shapes[i]->setGroup(group);
		if (!g_pPhysXScene->getGroupCollisionFlag(E_PHYSX_TAG_RAYCAST_TO_AI, group)
			|| !g_pPhysXScene->getGroupCollisionFlag(E_PHYSX_TAG_FIREWORK, group)
			|| !g_pPhysXScene->getGroupCollisionFlag(E_PHYSX_TAG_WHATEBOMB, group)
			|| !g_pPhysXScene->getGroupCollisionFlag(E_PHYSX_TAG_MYBOMB, group)
			|| !g_pPhysXScene->getGroupCollisionFlag(E_PHYSX_TAG_GRIVATEBALL, group)
			|| !g_pPhysXScene->getGroupCollisionFlag(E_PHYSX_TAG_RAYCAST_TO_AI, group)
			)
			shapes[i]->setFlag(NX_SF_DISABLE_RAYCASTING, true);
	}

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

NxVec3 cPhysXManager::D3DVecToNxVec(D3DXVECTOR3 & d3d)
{
	NxVec3 vec;
	vec.x = d3d.x;
	vec.y = d3d.y;
	vec.z = d3d.z;
	return vec;
}
void cPhysXManager::D3DMatToNxMat(NxF32 * nx, D3DMATRIX & dx)
{
	nx[0] = dx._11;
	nx[1] = dx._12;
	nx[2] = dx._13;
	nx[3] = dx._21;
	nx[4] = dx._22;
	nx[5] = dx._23;
	nx[6] = dx._31;
	nx[7] = dx._32;
	nx[8] = dx._33;
}

void cPhysXManager::Update()
{
	//	g_pTimeManager->GetElapsedTime());//
	//	MgrPhysXScene->simulate((1.f/60.f));	//프레임 지정
	//	MgrPhysXScene->checkResults(NX_RIGID_BODY_FINISHED, true);

	MgrPhysXScene->simulate((float)(1.f / 60.f));	//프레임 지정
	MgrPhysXScene->flushStream();
	MgrPhysXScene->fetchResults(NX_RIGID_BODY_FINISHED, true);


	if (g_pKeyManager->isOnceKeyDown(VK_TAB))
	{
		m_IS_DEBUG_RENDER = !m_IS_DEBUG_RENDER;
	}
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

NxRaycastHit cPhysXManager::RaycastClosestShape(D3DXVECTOR3 start, D3DXVECTOR3 dir, NxReal maxDist, NxU32 group)
{
	return RaycastClosestShape(MgrPhysX->D3DVecToNxVec(start), MgrPhysX->D3DVecToNxVec(dir), maxDist, group);
}

NxRaycastHit cPhysXManager::RaycastClosestShape(NxVec3 start, NxVec3 dir, NxReal maxDist, NxU32 group)
{
	NxRay worldRay;

	worldRay.orig = start;
	dir.normalize();
	worldRay.dir = dir;

	NxRaycastHit raycastHit;
	raycastHit.shape = NULL;
	MgrPhysXScene->raycastClosestShape(worldRay, NX_ALL_SHAPES, raycastHit, group, maxDist);// , 0xffffffff, NX_MAX_F32, 0xffffffff, NULL, NULL);

	return raycastHit;
}

void cPhysXManager::RaycastClosestShapePt(NxRaycastHit * raycasthit, NxVec3 start, NxVec3 dir, NxReal maxDist, NxU32 group)
{
	NxRay worldRay;


	worldRay.orig = start;
	dir.normalize();
	worldRay.dir = dir;

	//NxRaycastHit raycastHit;
	//raycastHit.shape = NULL;
	MgrPhysXScene->raycastClosestShape(worldRay, NX_ALL_SHAPES, *raycasthit, group, maxDist);// , 0xffffffff, NX_MAX_F32, 0xffffffff, NULL, NULL);
}

NxActor * cPhysXManager::CreateActor(NxShapeType type, NxVec3 position, NxF32 * mat, NxVec3 sizeValue, eMaterialTag materialTag, USERDATA * pUserData, bool IsTrigger, bool isStatic, bool isGravaty)
{
	sizeValue *= 0.5f;

	bool isKinematic = false;
	// Our trigger is a cube

	NxShapeDesc* shapeDesc = NULL;

	NxActorDesc ActorDesc;
	ActorDesc.setToDefault();


	switch (type)
	{
	case NX_SHAPE_PLANE: {
		break;
	}
	case NX_SHAPE_SPHERE: {
		NxSphereShapeDesc desc; desc.setToDefault();

		desc.setToDefault();
		desc.radius = sizeValue.x;
		shapeDesc = &desc;

		if (isKinematic)
		{
			NxSphereShapeDesc dummyShape;
			dummyShape.setToDefault();
			dummyShape.radius = sizeValue.x;
			ActorDesc.shapes.pushBack(&dummyShape);
		}
		break;
	}
	case NX_SHAPE_BOX: {
		NxBoxShapeDesc desc;
		desc.setToDefault();
		desc.dimensions.set(sizeValue);
		shapeDesc = &desc;

		if (isKinematic)
		{
			NxBoxShapeDesc dummyShape;
			dummyShape.setToDefault();
			dummyShape.dimensions.set(sizeValue);
			ActorDesc.shapes.pushBack(&dummyShape);
		}
		break;
	}
	case NX_SHAPE_CAPSULE: {
		NxCapsuleShapeDesc desc;
		desc.setToDefault();
		desc.radius = sizeValue.x;
		desc.height = sizeValue.y;
		shapeDesc = &desc;

		if (isKinematic)
		{
			NxCapsuleShapeDesc dummyShape;
			dummyShape.setToDefault();
			desc.radius = sizeValue.x;
			desc.height = sizeValue.y;
			ActorDesc.shapes.pushBack(&dummyShape);
		}
		break;
	}
	case NX_SHAPE_WHEEL: {
		NxWheelShapeDesc desc; desc.setToDefault();
		desc.setToDefault();
		desc.radius = sizeValue.y;
		desc.skinWidth = sizeValue.x;
		shapeDesc = &desc;

		if (isKinematic)
		{
			NxWheelShapeDesc dummyShape;
			dummyShape.setToDefault();
			dummyShape.radius = sizeValue.y;
			dummyShape.skinWidth = sizeValue.x;
			ActorDesc.shapes.pushBack(&dummyShape);
		}
		break;
	}
	case NX_SHAPE_CONVEX: {
		break;
	}
	case NX_SHAPE_MESH: {
		break;
	}
	case NX_SHAPE_HEIGHTFIELD: {
		break;
	}
	case NX_SHAPE_RAW_MESH: {
		break;
	}
	case NX_SHAPE_COMPOUND: {
		break;
	}
	case NX_SHAPE_COUNT: {
		break;
	}
	case NX_SHAPE_FORCE_DWORD: {
		break;
	}
	default:break;
	}

	if (shapeDesc == NULL) return NULL;

	shapeDesc->materialIndex = (int)materialTag;

	NxBodyDesc BodyDesc;
	BodyDesc.setToDefault();

	if (!isGravaty) BodyDesc.flags |= NX_BF_DISABLE_GRAVITY;

	if (isKinematic&& IsTrigger)
	{
		shapeDesc->shapeFlags |= NX_TRIGGER_ENABLE;
		BodyDesc.flags |= NX_BF_KINEMATIC;

		ActorDesc.body = &BodyDesc;
		//	ActorDesc.body = NULL;
	}
	if (isKinematic && !IsTrigger)
	{
		BodyDesc.flags |= NX_BF_KINEMATIC;

		ActorDesc.body = &BodyDesc;
	}
	if (!isKinematic&& IsTrigger)
	{
		shapeDesc->shapeFlags |= NX_TRIGGER_ENABLE;

		//	ActorDesc.body = NULL;
	}
	if (!isKinematic && !IsTrigger)
	{
		ActorDesc.body = &BodyDesc;
	}

	if (isStatic) ActorDesc.body = NULL;

	ActorDesc.density = 10.f;
	ActorDesc.shapes.pushBack(shapeDesc);
	ActorDesc.globalPose.t = position;

	if (mat == NULL)
	{
		NxF32 mat_[9] = { 1,0,0,0,1,0,0,0,1 };
		mat = mat_;
	}

	ActorDesc.globalPose.M.setColumnMajor(mat);

	if (pUserData != NULL) ActorDesc.userData = (pUserData);
	NxActor* actor = m_pNxScene->createActor(ActorDesc);
	if (actor == NULL)
	{
		//std::cout << "NULL";
	}
	return actor;

	//TEST

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
		if (pUserData0->USER_TAG == E_PHYSX_TAG_CAR && pUserData1->USER_TAG == E_PHYSX_TAG_CAR)
		{
			if (pUserData0->isMyBomb)
			{
				pUserData0->isMyBomb = false;
				pUserData1->isMyBomb = true;

				//	NxVec3 v = *pUserData0->m_pCarPosion;
					//*pUserData0->m_pCarPosion = *pUserData1->m_pCarPosion;
					//*pUserData1->m_pCarPosion = v;
			}
			else if (pUserData1->isMyBomb)
			{
				pUserData0->isMyBomb = true;
				pUserData1->isMyBomb = false;

				//NxVec3 v = *pUserData0->m_pCarPosion;
				//*pUserData0->m_pCarPosion = *pUserData1->m_pCarPosion;
				//*pUserData1->m_pCarPosion = v;
			}

		//	printf("%d %d\n", pUserData0->isMyBomb, pUserData1->isMyBomb);
		}
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

		if (pUserData0->USER_TAG == E_PHYSX_TAG_CHECKBOX)
		{
			pUserData1->CheckBoxID = pUserData0->CheckBoxID;
		}

		else if (pUserData0->USER_TAG == E_PHYSX_TAG_PICKUP)
		{
			if (pUserData1->IsPickUp == NX_FALSE
				&& pUserData0->IsPickUp == NX_TRUE)
			{
				pUserData0->IsPickUp = NX_FALSE;
				pUserData1->IsPickUp = NX_TRUE;
				//std::cout << "GetItem" << std::endl;
			}
		}

		if (pUserData1->USER_TAG == E_PHYSX_TAG_CAR && pUserData0->USER_TAG == E_PHYSX_TAG_GRIVATEBALL)
		{
			if (!pUserData1->isFireGravity)
			{
				otherShape.getActor().addForce(NxVec3(0, 900000, 0));
				otherShape.getActor().addLocalTorque(NxVec3((1000000 + rand() % 400000), (1000000 + rand() % 400000), (1000000 + rand() % 400000)));
			//	printf("데이터 충돌\n");
			}
		}
		else if (pUserData0->USER_TAG == E_PHYSX_TAG_CAR && pUserData1->USER_TAG == E_PHYSX_TAG_GRIVATEBALL)
		{
			if (!pUserData0->isFireGravity)
			{
				triggerShape.getActor().addForce(NxVec3(0, 900000, 0));
				triggerShape.getActor().addLocalTorque(NxVec3((1000000 + rand() % 400000), (1000000 + rand() % 400000), (1000000 + rand() % 400000)));
			//	printf("데이터 충돌\n");
			}
		}

		if (pUserData0->USER_TAG == E_PHYSX_TAG_FAKEBOMB && pUserData1->USER_TAG == E_PHYSX_TAG_CAR)
		{
			if (pUserData1->isFireFakebomb)
				pUserData1->isFireFakebomb = false;
			else
				pUserData0->isFakebombCollision = true;

		//	printf("충돌\n");
		}
		else if (pUserData1->USER_TAG == E_PHYSX_TAG_FAKEBOMB && pUserData0->USER_TAG == E_PHYSX_TAG_CAR)
		{
			if (pUserData0->isFireFakebomb)
				pUserData0->isFireFakebomb = false;
			else
				pUserData1->isFakebombCollision = true;

		//	printf("충돌\n");
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
		if (pUserData1->USER_TAG == E_PHYSX_TAG_CAR && pUserData0->USER_TAG == E_PHYSX_TAG_GRIVATEBALL)
		{
			if (pUserData1->isFireGravity)
			{
				pUserData1->isFireGravity = false;
			}
		}
		else if (pUserData0->USER_TAG == E_PHYSX_TAG_CAR &&pUserData1->USER_TAG == E_PHYSX_TAG_GRIVATEBALL)
		{
			if (pUserData0->isFireGravity)
			{
				pUserData0->isFireGravity = false;
			}
		}

		else
		{
			pUserData0->TriggerPairFlag = 0;
			pUserData1->TriggerPairFlag = 0;
		}



		//TEST_CODE
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

		pUserData0->TriggerPairFlag = NX_TRIGGER_ON_LEAVE;
		pUserData1->TriggerPairFlag = NX_TRIGGER_ON_LEAVE;
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
		boxShapes[0].materialIndex = E_PHYSX_MATERIAL_CAR;
		vehicleDesc.carShapes.pushBack(&boxShapes[0]);

		boxShapes[1].dimensions.set(0.3, 0.1f, 0.25f);
		boxShapes[1].localPose.t.set(-0.1f, 0.4, 0.f);
		boxShapes[1].materialIndex = E_PHYSX_MATERIAL_CAR;
		vehicleDesc.carShapes.pushBack(&boxShapes[1]);
	}
	;

	vehicleDesc.position = pos;
	vehicleDesc.mass = 1000;//monsterTruck ? 12000 : 
	vehicleDesc.digitalSteeringDelta = 0.04f;
	vehicleDesc.steeringMaxAngle = 30.f;
	vehicleDesc.motorForce = 3500.f;//monsterTruck?180.f:
	vehicleDesc.maxVelocity = 30.f;//(monsterTruck)?20.f:

	vehicleDesc.centerOfMass.set(0.f, 0.108f, 0.f);

	NxWheelDesc wheelDesc[4];
	for (NxU32 i = 0; i < 4; i++)
	{

		wheelDesc[i].wheelApproximation = 10;
		wheelDesc[i].wheelRadius = 0.1f;
		wheelDesc[i].wheelWidth = 0.05f;
		wheelDesc[i].wheelSuspension = 0.05f;
		wheelDesc[i].springRestitution = 800;
		wheelDesc[i].springDamping = 500;
		wheelDesc[i].springBias = 0.05f;

		wheelDesc[i].maxBrakeForce = 1.f;
		wheelDesc[i].wheelFlags |= NX_WF_USE_WHEELSHAPE;


		//바퀴의 마찰력
		wheelDesc[i].frictionToFront = 2.f;
		wheelDesc[i].frictionToSide = 2.f;

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
	g_pPhysX->SetActorGroup(vehicle->getActor(), E_PHYSX_TAG_CAR);

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

NxActor * cPhysXManager::CreateActorToCCD(NxVec3 position, NxF32 * mat, NxVec3 sizeValue, eMaterialTag materialTag, USERDATA * pUserData, bool IsTrigger, bool isStatic, bool isGravaty)
{
	sizeValue *= 0.5f;

	NxU32 triangles[3 * 12] = {
		0,1,3,
		0,3,2,
		3,7,6,
		3,6,2,
		1,5,7,
		1,7,3,
		4,6,7,
		4,7,5,
		1,0,4,
		5,1,4,
		4,0,2,
		4,2,6
	};
	NxVec3 points[8];
	//static mesh
	points[0].set(sizeValue.x, -sizeValue.y, -sizeValue.z);
	points[1].set(sizeValue.x, -sizeValue.y, sizeValue.z);
	points[2].set(sizeValue.x, sizeValue.y, -sizeValue.z);
	points[3].set(sizeValue.x, sizeValue.y, sizeValue.z);
	points[4].set(-sizeValue.x, -sizeValue.y, -sizeValue.z);
	points[5].set(-sizeValue.x, -sizeValue.y, sizeValue.z);
	points[6].set(-sizeValue.x, sizeValue.y, -sizeValue.z);
	points[7].set(-sizeValue.x, sizeValue.y, sizeValue.z);
	NxSimpleTriangleMesh stm;
	stm.numVertices = 8;
	stm.numTriangles = 6 * 2;
	stm.pointStrideBytes = sizeof(NxVec3);
	stm.triangleStrideBytes = sizeof(NxU32) * 3;
	stm.points = points;
	stm.triangles = triangles;
	stm.flags |= NX_MF_FLIPNORMALS;



	//
	sizeValue *= 0.5f;

	bool isKinematic = false;
	// Our trigger is a cube


	NxBoxShapeDesc* ShapeDesc = NULL;
	ShapeDesc->setToDefault();
	ShapeDesc->dimensions.set(sizeValue);
	ShapeDesc->materialIndex = (int)materialTag;

	ShapeDesc->ccdSkeleton = MgrPhysXSDK->createCCDSkeleton(stm);
	ShapeDesc->shapeFlags |= NX_SF_DYNAMIC_DYNAMIC_CCD;


	NxBodyDesc BodyDesc;
	BodyDesc.setToDefault();


	NxActorDesc ActorDesc;
	ActorDesc.setToDefault();


	if (!isGravaty) BodyDesc.flags |= NX_BF_DISABLE_GRAVITY;

	if (IsTrigger)		ShapeDesc->shapeFlags |= NX_TRIGGER_ENABLE;
	if (!IsTrigger)		ActorDesc.body = &BodyDesc;

	if (isStatic) ActorDesc.body = NULL;

	ActorDesc.density = 10.f;
	ActorDesc.shapes.pushBack(ShapeDesc);
	ActorDesc.globalPose.t = position;


	if (mat == NULL)
	{
		NxF32 mat_[9] = { 1,0,0,0,1,0,0,0,1 };
		mat = mat_;
	}

	ActorDesc.globalPose.M.setColumnMajor(mat);

	if (pUserData != NULL) ActorDesc.userData = (pUserData);
	NxActor* actor = m_pNxScene->createActor(ActorDesc);
	if (actor == NULL)
	{
	//	std::cout << "NULL";
	}
	return actor;

	//TEST
}
