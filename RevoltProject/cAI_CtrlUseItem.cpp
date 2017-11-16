#include "stdafx.h"
#include "cAI_CtrlUseItem.h"
#include "cAI_Master.h"
#include "cCar.h"

cAI_CtrlUseItem::cAI_CtrlUseItem()
{
	m_isFire = false;
}


cAI_CtrlUseItem::~cAI_CtrlUseItem()
{
}

void cAI_CtrlUseItem::Update()
{
	if (!AI_Data->pCar->m_itemEable) return;

	float lengrh = 0.f;
	m_isFire = false;
	int a = 0;

	switch (AI_Data->pCar->GetHoldItem())
	{
	case ITEM_FIREWORK:
	{
		if (AI_Data->pCar->GetTarget() != NULL)
			m_isFire = true;
		break;
	}
	break;
	case ITEM_WBOMB:	lengrh = 30.f;
	case ITEM_GRAVITY:
	{
		lengrh = 80.f;
		//아이템 발사를 위한 레이
		NxVec3 thisPos = AI_Data->pCar->GetPhysXData()->GetPositionToNxVec3();

		NxVec3 rayposL(0, 0, 0);
		NxVec3 rayposR(0, 0, 0);
		NxVec3 raydir = AI_Data->pCar->CarArrow(0);
		rayposL = thisPos + AI_Data->pCar->CarArrow(-90) * 2;
		rayposR = thisPos + AI_Data->pCar->CarArrow(+90) * 2;

		rayposL += raydir * 1.f;
		rayposR += raydir * 1.f;


		for (int i = 0; i < AI_Data->pCars->size(); i++)
		{
			cCar* p = (*AI_Data->pCars)[i];
			if (AI_Data->pCar == p) continue;

			NxVec3 carPos = p->GetPhysXData()->GetPositionToNxVec3();
			//거리에 들어왔는지
			if (carPos.distance(thisPos) < lengrh)
			{

				NxVec3 toDirL = carPos - rayposL; toDirL.normalize();
				NxVec3 toDirR = carPos - rayposR; toDirR.normalize();

				bool isUpL = (raydir.cross(toDirL).y > 0);
				bool isUpR = (raydir.cross(toDirR).y > 0);
				//두 레이 사이에 있는지
				if (isUpL != isUpR)
				{

					NxVec3 LtoR = rayposR - rayposL; LtoR.normalize();
					//정면 에 있는지
					if ((LtoR.cross(toDirL).y < 0))
					{

						NxVec3 thisToCar = carPos - thisPos; thisToCar.normalize();
						NxRaycastHit hitT;
						NxRaycastHit hitC;
						hitT = RAYCAST(thisPos + NxVec3(0, 0.3, 0), thisToCar, carPos.distance(thisPos));
						hitC = RAYCAST(carPos + NxVec3(0, 0.3, 0), -thisToCar, carPos.distance(thisPos));

						if (hitT.distance > carPos.distance(thisPos) - 0.01f)
						{
							if (hitC.distance > carPos.distance(thisPos) - 0.01f)
							{

								m_isFire = true;
							}
						}
					}
				}
			}
		}
	}break;
	case ITEM_MYBOMB:	m_isFire = true; break;
	case ITEM_FAKEBOMB: m_isFire = true; break;
	case ITEM_NONE:		break;

	default:		break;
	}

	//std::cout << std::endl;
}

void cAI_CtrlUseItem::Render()
{
}
