#pragma once
#include <NxPhysics.h>
#include <NxCooking.h>
#include "UserStream.h"
#include "DEBUG_RENDERER.h"

#include "PhysX/NxVehicle.h"
#include "PhysX/NxAllVehicles.h"
#include "PhysX/NxLinearInterpolate3Values.h"
#include "PhysX/NxLinearInterpolationValues.h"
#include "PhysX/NxVehicleDesc.h"
#include "PhysX/NxVehicleGearDesc.h"
#include "PhysX/NxVehicleGears.h"
#include "PhysX/NxVehicleMotor.h"
#include "PhysX/NxVehicleMotorDesc.h"
#include "PhysX/NxWheel.h"
#include "PhysX/NxWheelDesc.h"
#include "PhysX/cooking.h"

//#include <NxConvexMeshDesc.h>




#define MgrPhysX		cPhysXManager::GetInstance()
#define MgrPhysXScene	cPhysXManager::GetInstance()->GetPhysXScene()
#define MgrPhysXSDK		cPhysXManager::GetInstance()->GetPhysXSDK()
#define MgrPhysXData	cPhysXManager::GetInstance()->GetPhysXData()

#define  g_pPhysX		  MgrPhysX		
#define  g_pPhysXScene	  MgrPhysXScene	
#define  g_pPhysXSDK	  MgrPhysXSDK		
#define  g_pPhysXData	  MgrPhysXData	
enum ePhysXTag
{
	E_PHYSX_TAG_NONE = 0		//충돌 이벤트에서 딱히 해줄게 없는 것들...
	, E_PHYSX_TAG_CHECKBOX		//체크 박스
	, E_PHYSX_TAG_CAR			//
	, E_PHYSX_TAG_FIREWORK
	, E_PHYSX_TAG_WHATEBOMB
	, E_PHYSX_TAG_METALBALL
	, E_PHYSX_TAG_GRIVATEBALL
	, E_PHYSX_TAG_END
};

enum eMaterialTag
{
	E_PHYSX_MATERIAL_NONE = 0 // 존재하지 않은 제질
	, E_PHYSX_MATERIAL_MAP
	, E_PHYSX_MATERIAL_CAR
	, E_PHYSX_MATERIAL_03
	, E_PHYSX_MATERIAL_04
	, E_PHYSX_MATERIAL_05
	, E_PHYSX_MATERIAL_06
};

struct PHYSXDATA
{
	int RaycastAllShapeHitCount;
	NxVec3	RaycastClosestShapePosition;
	PHYSXDATA() { Init(); }
	void Init()
	{
		RaycastAllShapeHitCount = 0;
		RaycastClosestShapePosition = NxVec3(0, 0, 0);
	}
};

struct USERDATA
{
	ePhysXTag USER_TAG;
	NxU32 ContactPairFlag;
	NxU32 TriggerPairFlag;

	NX_BOOL RaycastClosestShape;
	NX_BOOL RaycastAllShape;
	NxVec3	RayHitPos;
	USERDATA()
	{
		USER_TAG = E_PHYSX_TAG_NONE;
		ContactPairFlag = 0;
		TriggerPairFlag = 0;
		RaycastClosestShape = NX_FALSE;
		RaycastAllShape = NX_FALSE;
		RayHitPos = NxVec3(0, 0, 0);
	}
	void Init()
	{
		RaycastClosestShape = NX_FALSE;
		RaycastAllShape = NX_FALSE;
	}
};

struct KinematicActor {
	NxActor* actor;
	NxVec3 vel;
};
//NxArray<KinematicActor>	gKinematicActors;

class ContactCallBack : public NxUserContactReport
{
	//충돌확인
	void onContactNotify(NxContactPair& pair, NxU32 _event);
};
class TriggerCallback : public NxUserTriggerReport
{
	//충돌확인
	void onTrigger(NxShape& triggerShape, NxShape& otherShape, NxTriggerFlag status);
};

class RaycastCallBack : public NxUserRaycastReport
{
	//Ray 확인
	virtual bool onHit(const NxRaycastHit& hit);
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
enum eShapeTag
{
	E_SHAPE_NONE,
	E_SHAPE_BOX,
	E_SHAPE_SPHERE,
	E_SHAPE_PLANE,
	E_SHAPE_TRIANGLE,
};


class cPhysXManager
{
public:
	SINGLETONE(cPhysXManager);

	SYNTHESIZE(PHYSXDATA*, m_physXUserData, PhysXData);
private:
	DEBUG_RENDERER* pDebugRenderer = NULL;

	NxPhysicsSDK*	m_pNxPhysicsSDK;
	NxScene*		m_pNxScene;

	std::map<E_MATERIAL, NxMaterial*> m_mapMaterial;
public:
	NxPhysicsSDK* GetPhysXSDK() { return m_pNxPhysicsSDK; }
	NxScene* GetPhysXScene() { return m_pNxScene; }
	BOOL InitNxPhysX();

	void Update();
	void Destory();

	void Render();

	NxTriangleMeshShapeDesc CreateTringleMesh(ID3DXMesh* pMesh, D3DXMATRIXA16* matS = NULL);
	NxBoxShapeDesc CreateBoxShape(int materialIndex, NxVec3 boxSize);

	NxVec3 D3DVecToNxVec(D3DXVECTOR3& d3d)
	{
		NxVec3 vec;
		vec.x = d3d.x;
		vec.y = d3d.y;
		vec.z = d3d.z;
		return vec;
	}
	void D3DMatToNxMat(NxF32* nx, D3DMATRIX& dx)
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

	void RaycastClosestShape(D3DXVECTOR3 start, D3DXVECTOR3 dir);
	void RaycastAllShapes(D3DXVECTOR3 start, D3DXVECTOR3 dir);


	//CreateActor Actor 를 만들어 매니저에 등록후 반환한다.
	//1
	//NxShapeType
	//NX_SHAPE_SPHERE		:	NxVec3(지름값, 0, 0);
	//NX_SHAPE_BOX			:	NxVec3(width, height, deep);
	//NX_SHAPE_CAPSULE		:	NxVec3(지름값, 지름값, 0);
	//NX_SHAPE_WHEEL		:	NxVec3(지름값, 0, 0);
	//2
	//position 위치 , 회전
	//3
	//충돌 크기
	//4
	//유저 데이터
	//5 
	//Kinematic -> 다른 객체에게 물리 효과를 받지 않음
	//IsTrigger -> 트리거 충돌을 발생
	//
	//        (T,T)    (T,F)    (F,T)    (F,F)
	// (F,F)   O/O      0/N      O/O      O/N
	// (F,T)    /        /        /        /
	// (T,F)    /        /        0        X
	// (T,T)    /        /        /        O
	//
	//
	// eMaterialTag 
	// E_PHYSX_MATERIAL_NONE 값은 Default 값으로 사용하지는 말 것.
	NxActor* CreateActor(NxShapeType type, NxVec3 position, NxF32* mat, NxVec3 sizeValue, eMaterialTag materialTag = E_PHYSX_MATERIAL_NONE, USERDATA* pUserData = NULL,
		bool IsTrigger = false, bool isStatic = false, bool isGravaty = true)
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
			NxCapsuleShapeDesc desc; desc.setToDefault();
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

		NxBodyDesc triggerBody;
		triggerBody.setToDefault();

		if (!isGravaty) triggerBody.flags |= NX_BF_DISABLE_GRAVITY;

		if (isKinematic&& IsTrigger)
		{
			shapeDesc->shapeFlags |= NX_TRIGGER_ENABLE;
			triggerBody.flags |= NX_BF_KINEMATIC;

			ActorDesc.body = &triggerBody;
			//	ActorDesc.body = NULL;
		}
		if (isKinematic && !IsTrigger)
		{
			triggerBody.flags |= NX_BF_KINEMATIC;

			ActorDesc.body = &triggerBody;
		}
		if (!isKinematic&& IsTrigger)
		{
			shapeDesc->shapeFlags |= NX_TRIGGER_ENABLE;

			//	ActorDesc.body = NULL;
		}
		if (!isKinematic && !IsTrigger)
		{
			ActorDesc.body = &triggerBody;
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
			std::cout << "NULL";
		}
		return actor;

		//TEST

	}

	NxVehicle* createCarWithDesc(NxVec3 pos, bool frontWheelDrive, bool backWheelDrive)
	{
		//monsterTruck = true;
		NxVehicleDesc vehicleDesc;
		NxBoxShapeDesc boxShapes[2];

		boxShapes[0].dimensions.set(0.5, 0.1f, 0.2f);
		boxShapes[0].localPose.t.set(0.f, 0.3f, 0.f);
		boxShapes[0].materialIndex = 1;
		vehicleDesc.carShapes.pushBack(&boxShapes[0]);

		//boxShapes[1].dimensions.set(1.f, 0.3f, 1.1f);
		//boxShapes[1].localPose.t.set(-0.3f, 0.7f, 0.f);
		//boxShapes[1].materialIndex = 1;
		//vehicleDesc.carShapes.pushBack(&boxShapes[1]);

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
			wheelDesc[i].wheelWidth = 0.05f;
			wheelDesc[i].wheelSuspension = 0.00f;
			wheelDesc[i].springRestitution = 7000;
			wheelDesc[i].springDamping = 800;
			wheelDesc[i].springBias = 0.2f;
			wheelDesc[i].maxBrakeForce = 1.f;
			wheelDesc[i].wheelFlags |= NX_WF_USE_WHEELSHAPE;


			//바퀴의 마찰력
			wheelDesc[i].frictionToFront = 10.f;
			wheelDesc[i].frictionToSide = 3.f;

			vehicleDesc.carWheels.pushBack(&wheelDesc[i]);
		}


		wheelDesc[0].position.set(0.3f, 0.2f, -0.15);
		wheelDesc[1].position.set(0.3, 0.2f, 0.15);
		wheelDesc[2].position.set(-0.3, 0.2f, -0.15);
		wheelDesc[3].position.set(-0.3, 0.2f, 0.15);

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

		if (vehicle) return vehicle;
		else
		{
			std::string pritfOut("자동차가의 물리정보가 생성되지 않았습니다.");
			MessageBoxA(g_hWnd, pritfOut.c_str(), "오류", MB_OK);
		}
	}
};
