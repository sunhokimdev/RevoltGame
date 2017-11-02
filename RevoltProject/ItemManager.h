#pragma once

class cItem;
class cContactUser;
class cImpact;

#define g_pItemManager ItemManager::GetInstance()

struct ST_PHYSX
{
	cPhysX* pPhysX;
	cPhysX* pTrigger;
	cMesh* pMesh;
	NxVec3 pos;
};

struct ST_USERDATA
{
	int id;
	int events;
};

enum ITEM_LIST{ WBOMEB=3001, FIREWORK, GRAVITY, ITEMLAST};

//===================================================================
// - written by 김선호
// - ###아이템 물리적용 시켜주는 아이템 매니저###
// - 모든 아이템들은 여기서 적용시켜준다
//===================================================================

class ItemManager
{
private:
	std::vector<cItem*> m_vecItem;				// 아이템들을 관리하는 클래스
	std::map<ITEM_LIST, std::vector<cItem*>>	m_mapItem;
	int m_max;
	int m_index;

	NxActor* box1;
	NxActor* box2;
	NxActor* box3;
	NxActor* box4;

public:
	SINGLETONE(ItemManager);

	void Init();
	void Update();
	void Render();

	void SetFire(D3DXVECTOR3 angle, D3DXVECTOR3 pos);
	void SetActorGroup(NxActor* actor, NxCollisionGroup group);
	void InitCollisionGroup();
};

