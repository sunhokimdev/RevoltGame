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

struct stCARSPEC;
class cCar;

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
	, E_PHYSX_TAG_CAR			//차
	, E_PHYSX_TAG_PICKUP		//아이템
	, E_PHYSX_TAG_FIREWORK
	, E_PHYSX_TAG_WHATEBOMB
	, E_PHYSX_TAG_MYBOMB
	, E_PHYSX_TAG_METALBALL
	, E_PHYSX_TAG_GRIVATEBALL
	, E_PHYSX_TAG_TRACK
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
	PHYSXDATA() { Reset(); }
	void Reset()
	{
		RaycastAllShapeHitCount = 0;
		RaycastClosestShapePosition = NxVec3(0, 0, 0);
	}
};

struct USERDATA
{
	ePhysXTag USER_TAG;
	NxU32 UserPointValue;
	std::vector<NxU32> TargetPointValue;
	NX_BOOL IsPickUp;
	NxU32 CheckBoxID;


	NxU32 ContactPairFlag;
	NxU32 TriggerPairFlag;

	NX_BOOL RaycastClosestShape;
	NX_BOOL RaycastAllShape;
	NxVec3	RayHitPos;

	/*   김선호 작업   */
	bool isMyBomb;
	NxVec3* m_pCarPosion;

	USERDATA(ePhysXTag tag)
	{
		Init();
		USER_TAG = tag;
	}
	USERDATA()
	{
		Init();
	}
	void Init()
	{
		UserPointValue = (NxU32)this;

		USER_TAG = E_PHYSX_TAG_NONE;
		ContactPairFlag = 0;
		TriggerPairFlag = 0;
		RaycastClosestShape = NX_FALSE;
		RaycastAllShape = NX_FALSE;
		RayHitPos = NxVec3(0, 0, 0);
		CheckBoxID = 0;
		IsPickUp = NX_FALSE;

		/*   김선호   */
		isMyBomb = false;
	}
	void Reset()
	{
		TargetPointValue.clear();
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

	NxVec3 D3DVecToNxVec(D3DXVECTOR3& d3d);
	void D3DMatToNxMat(NxF32* nx, D3DMATRIX& dx);

	void RaycastClosestShape(D3DXVECTOR3 start, D3DXVECTOR3 dir);
	void RaycastAllShapes(D3DXVECTOR3 start, D3DXVECTOR3 dir);

	void SetActorGroup(NxActor * actor, NxCollisionGroup group);


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
		bool IsTrigger = false, bool isStatic = false, bool isGravaty = true);

	NxVehicle* createCarWithDesc(NxVec3 pos, stCARSPEC carspec, USERDATA* pUserData, bool frontWheelDrive, bool backWheelDrive);
};
