#include "stdafx.h"
#include "cAI_CtrlCompete.h"
#include "cAI_Master.h"
#include "cCar.h"
#include "cTrack.h"
#include "cPickUp.h"

cAI_CtrlCompete::cAI_CtrlCompete()
{
	maxDistance = 10.0f;
	HandleValue = 0.0f;
	closePickup = NULL;

	PickupAngle = 0.5f;

	PickupValue = 100.0f;
	CarsValue = 500.0f;
	Competitive = 0.5f;
}


cAI_CtrlCompete::~cAI_CtrlCompete()
{
	closePickup = NULL;
}

void cAI_CtrlCompete::Update()
{
	float minDistance = maxDistance * 100;

	NxRaycastHit hit;

	HandleValue = 0.0f;
	{
		if (AI_Data->pCar->GetHoldItem() == (eITEM_LIST)0)
		{
			D3DXVECTOR3 thisPos = AI_Data->pCar->GetPhysXData()->GetPositionToD3DXVec3();
			D3DXVECTOR3 F__Dir = ((cAI_Ray*)(*familyAI)[AI_TAG_RAY])->Ray_F__.GetDir_Dx();

			D3DXVECTOR3 objPos(0, 0, 0);
			D3DXVECTOR3 objDir(0, 0, 0);

			float angleValue = 0.f;

			closePickup = NULL;
			for each(Object* p in AI_Data->pTrack->GetVecObject())
			{
				if (p->GetTag() == eOBJECT_TAG::E_OBJECT_PICKUP)
				{
					if (!((cPickUp*)p)->IsShow()) continue;

					objPos = p->GetPhysXData()->GetPositionToD3DXVec3();

					objDir = ((cPickUp*)p)->GetPosition() - thisPos;
					objDir.y = 0;
					float distance = D3DXVec3Length(&(objDir));
					D3DXVec3Normalize(&objDir, &objDir);

					angleValue = D3DXVec3Dot(&F__Dir, &objDir);


					//각도
					if (angleValue > PickupAngle)
					{
						D3DXVECTOR3 rayPos = D3DXVECTOR3(thisPos.x, thisPos.y + 0.3f, thisPos.z);
						hit = RAYCAST(rayPos, objDir, 10000);
						//장에물
						if (hit.shape != NULL && hit.distance > distance - 0.01f)
						{
							D3DXVECTOR3 rayPos = D3DXVECTOR3(objPos.x, objPos.y + 0.3f, objPos.z);
							hit = RAYCAST(rayPos, -objDir, minDistance);

							if (hit.shape != NULL && hit.distance > distance - 0.01f)
							{
								//가장 가까운 거리
								if (minDistance > distance)
								{
									closePickup = (cPickUp*)p;
									minDistance = distance;
								}
							}
						}
					}
				}
			}
			//행동
			if (closePickup)
			{
				objDir = closePickup->GetPosition() - thisPos;
				objDir.y = 0.f;
				D3DXVec3Normalize(&objDir, &objDir);
				D3DXVECTOR3 dir(0, 0, 0);

				D3DXVec3Cross(&dir, &objDir, &F__Dir);
				D3DXVec3Normalize(&dir, &dir);

				POS_ITEMPOS = closePickup->GetPosition();

				bool isRight = (dir.y <= 0);
				angleValue = 1 - angleValue;
				angleValue = isRight ? angleValue : -angleValue;

				HandleValue += angleValue * PickupValue * Competitive;
			}
		}
	}

	{
		float thisRpmRate = GetRpmRate();
//		thisRpmRate = 1.0f;
		thisRpmRate = fmax(thisRpmRate, 0.1f);

		NxVec3 thisPos = AI_Data->pCar->GetPhysXData()->GetPositionToNxVec3();
		NxVec3 thisDir = AI_Data->pCar->WheelArrow(); // +AI_Data->pCar->CarArrow();
		thisDir.normalize();
		NxVec3 thisDir_(0, 0, 0); thisDir_.multiply(maxDistance * thisRpmRate, thisDir);
		NxVec3 thisDirPos = thisPos + thisDir_;

		// thisDirPos.y = 0.3f;
		POS_THISPOSDIR = D3DXVECTOR3(thisDirPos.x, thisDirPos.y, thisDirPos.z);

		for each(cCar* p in (*AI_Data->pCars))
		{
			if (AI_Data->pCar == p) continue;

			NxVec3 carPos = p->GetPhysXData()->GetPositionToNxVec3();
			NxVec3 carDir = p->CarArrow() + p->WheelArrow();
			//carDir.y = 0.f;
			carDir.normalize();
			NxVec3 carDir_(0, 0, 0); carDir_.multiply(maxDistance * thisRpmRate, carDir);
			NxVec3 carDirPos = carPos + carDir_;

		//	carDirPos.y = 0.3f;
			POS_CARPOSDIR = D3DXVECTOR3(carDirPos.x, carDirPos.y, carDirPos.z);


			float dist = NxVec3(carPos - thisPos).magnitude();



			if (dist < maxDistance * thisRpmRate)
			{
				float distRate = 1.0f - dist / maxDistance;
				float carRpmRate = p->GetRpmRate();


				NxVec3 thisToCarPos = carPos - thisPos;		thisToCarPos.normalize();
				NxVec3 thisToCarDir = carDirPos - thisPos;	thisToCarDir.normalize();
				NxVec3 CarToThisPos = thisPos - carPos;		CarToThisPos.normalize();
				NxVec3 CarToThisDir = thisDirPos - carPos;	CarToThisDir.normalize();

				bool isCarPosRight = thisToCarPos.cross(thisDir).y <= 0;
				bool isCarDirRight = thisToCarDir.cross(thisDir).y < 0;
				bool isThisPosRight = CarToThisPos.cross(carDir).y <= 0;
				bool isThisDirRight = CarToThisDir.cross(carDir).y < 0;

				NxVec3 rayPos = thisPos; rayPos.y += 0.3f;
				hit = RAYCAST(rayPos, thisToCarPos, minDistance);
				if (hit.shape != NULL && hit.distance > dist - 0.01f)
				{
					NxVec3 rayPos = carPos; rayPos.y += 0.3f;
					hit = RAYCAST(rayPos, thisToCarPos, minDistance);
					if (hit.shape != NULL && hit.distance > dist - 0.01f)
					{

						if (isCarPosRight != isCarDirRight && isThisPosRight != isThisDirRight)
						{
							NxVec3 targetDir(0, 0, 0);
							bool isRight = true;
							if ((carPos - thisDirPos).magnitudeSquared() < (carDirPos - thisDirPos).magnitudeSquared())
							{
								//자동차 뒤로 회피
								targetDir = carPos - thisPos;
								isRight = isCarPosRight;
							}
							else
							{
								//자동차 앞으로 회피
								targetDir = carDirPos - thisPos;
								isRight = isCarDirRight;
							}

							targetDir.normalize();
							float value = thisDir.dot(targetDir);

							value = 1.0f - value;
							value = isRight ? value : -value;

							if (closePickup)
								HandleValue += value * CarsValue * (1.0f - Competitive * 0.5f);
							else
								HandleValue += value * CarsValue * (1.0f - Competitive);
						}
					}
				}
			}
		}
	}
}

void cAI_CtrlCompete::Render()
{
	D3DXMATRIXA16 mat16;
	D3DXVECTOR3 pos;
	D3DMATERIAL9 material;

	if (!AI_Mesh)
	{
		D3DXCreateBox(g_pD3DDevice, 0.3f, 0.3f, 0.3f, &AI_Mesh, NULL);
	}


	ZeroMemory(&material, sizeof(D3DMATERIAL9));
	material.Ambient = CX_GREEN;
	material.Diffuse = CX_GREEN;
	material.Specular = CX_GREEN;
	material.Emissive = CX_GREEN;
	g_pD3DDevice->SetMaterial(&material);

	pos = POS_THISPOSDIR;
	D3DXMatrixTranslation(&mat16, pos.x, pos.y, pos.z);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat16);
	(AI_Mesh)->DrawSubset(0);

	pos = POS_CARPOSDIR;
	D3DXMatrixTranslation(&mat16, pos.x, pos.y, pos.z);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat16);
	(AI_Mesh)->DrawSubset(0);

	ZeroMemory(&material, sizeof(D3DMATERIAL9));
	material.Ambient = CX_YELLOW;
	material.Diffuse = CX_YELLOW;
	material.Specular = CX_YELLOW;
	material.Emissive = CX_YELLOW;
	g_pD3DDevice->SetMaterial(&material);

	pos = POS_ITEMPOS;
	D3DXMatrixTranslation(&mat16, pos.x, pos.y, pos.z);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat16);
	(AI_Mesh)->DrawSubset(0);
}
