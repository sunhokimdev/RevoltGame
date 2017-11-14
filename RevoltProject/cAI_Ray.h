#pragma once
#include "cAI.h"

struct AIRayCastData
{
	NxRaycastHit Hit;
	NxVec3 Pos;
	NxVec3 Dir;
	float Dist;
	AIRayCastData()
	{
		Pos = NxVec3(0, 0, 0);
		Dir = NxVec3(0, 0, 0);
		Dist = 0.f;
	}
	~AIRayCastData()
	{

	}
	void RayShot(NxVec3 pos, NxVec3 dir , float dist)
	{
		Hit = RAYCAST(pos, dir, dist);
		if (Hit.shape)
		{
			Pos = Hit.worldImpact;
			Dir = Pos - pos;
			Dir.normalize();
			Dist = Hit.distance;
		}
		else
		{
			Pos = pos + dir * dist;
			Dir = Pos - pos;
			Dir.normalize();
			Dist = dist;
		}
	}

	bool IsNull() { return (Hit.shape == NULL); }
	NxVec3 GetPosition()
	{
		return Pos;
	}
	D3DXVECTOR3 GetPosition_Dx()
	{
		NxVec3 pos = GetPosition();
		return D3DXVECTOR3(pos.x, pos.y, pos.z);
	}
	NxVec3 GetDir()
	{
		return Dir;
	}
	D3DXVECTOR3 GetDir_Dx()
	{
		NxVec3 pos = GetDir();
		return D3DXVECTOR3(pos.x, pos.y, pos.z);
	}
	float Distance()
	{
		return Dist;
	}
	float DistanceRate(float total)
	{
		if (total == 0.0f) return Dist;
		else return Dist / total;
	}
};

class cAI_Ray :
	public cAI
{
public:
	float RayDist;

	AIRayCastData Ray_F__;
	AIRayCastData Ray_B__;
	AIRayCastData Ray_LF_;
	AIRayCastData Ray_RF_;
	AIRayCastData Ray_L__;
	AIRayCastData Ray_R__;

//	AIRayCastData Ray_Pik;
//	AIRayCastData Ray_Car;
	//	AIRayCastData Ray_8__;
	//	AIRayCastData Ray_9__;

public:
	cAI_Ray();
	~cAI_Ray();
	void Update();
	void Render();

	float RayDirY();
};

