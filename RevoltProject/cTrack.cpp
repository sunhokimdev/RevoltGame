#include "stdafx.h"
#include "cTrack.h"
#include "cLight.h"
#include "cCheckBox.h"
#include "cStuff.h"
#include "cFollowPoint.h"
#include "cPickUp.h"



cTrack::cTrack()
	:m_nLightIdx(11)
{
//	pVeh = NULL;

	//임시 등록 데이터
	cTrack::SetData();

//	*camPos = D3DXVECTOR3(0 - 5, 0 + 5, 0);
//	*camLookTarget = D3DXVECTOR3(0, 0, 0);
//
//	g_pCamManager->SetCamPos(camPos);
//	g_pCamManager->SetLookAt(camLookTarget);
}


cTrack::~cTrack()
{
}

void cTrack::Update()
{
	for each(Object* pObj in m_vecObject)
	{
		pObj->Update();
	}
	//if (pVeh)
	//{
	//	NxVec3 pos = pVeh->getGlobalPose().t;
	//	*camPos = D3DXVECTOR3(pos.x - 5, pos.y + 5, pos.z);
	//	*camLookTarget = D3DXVECTOR3(pos.x, pos.y + 3, pos.z);
	//	g_pCamManager->SetLookAt(camLookTarget);

	//	static float angle = 0;
	//	if (g_pKeyManager->isOnceKeyDown('A'))
	//	{
	//		angle += 0.1;
	//	}
	//	if (g_pKeyManager->isOnceKeyDown('D'))
	//	{
	//		angle -= 0.1;
	//	}
	//	NxWheel* wheel = pVeh->getWheel(0);
	//	wheel->setAngle(angle);

	//	wheel = pVeh->getWheel(1);
	//	wheel->setAngle(angle);

	//	pVeh->getActor()->addForce(NxVec3(0, 1, 0));

	//	if (g_pKeyManager->isOnceKeyDown('S'))
	//	{
	//		NxWheel* wheel = pVeh->getWheel(0);
	//		wheel->tick(false, (NxReal)-1000, (NxReal)0, (NxReal)1.f / 60.f);
	//		wheel->setAngle(angle);

	//		wheel = pVeh->getWheel(1);
	//		wheel->tick(false, (NxReal)-1000, (NxReal)0, (NxReal)1.f / 60.f);
	//		wheel->setAngle(angle);

	//		wheel = pVeh->getWheel(2);
	//		wheel->tick(false, (NxReal)-1000, (NxReal)0, (NxReal)1.f / 60.f);

	//		wheel = pVeh->getWheel(3);
	//		wheel->tick(false, (NxReal)-1000, (NxReal)0, (NxReal)1.f / 60.f);
	//	}

	//	if (g_pKeyManager->isOnceKeyDown(VK_SPACE))
	//	{
	//		NxWheel* wheel = pVeh->getWheel(0);
	//		wheel->tick(false, (NxReal)0, (NxReal)1000, (NxReal)1.f / 60.f);

	//		wheel = pVeh->getWheel(1);
	//		wheel->tick(false, (NxReal)0, (NxReal)1000, (NxReal)1.f / 60.f);

	//		wheel = pVeh->getWheel(2);
	//		wheel->tick(false, (NxReal)0, (NxReal)1000, (NxReal)1.f / 60.f);

	//		wheel = pVeh->getWheel(3);
	//		wheel->tick(false, (NxReal)0, (NxReal)1000, (NxReal)1.f / 60.f);
	//	}

	//	if (g_pKeyManager->isOnceKeyDown('W'))
	//	{
	//		NxWheel* wheel = pVeh->getWheel(0);
	//		wheel->tick(false, (NxReal)1000, (NxReal)0, (NxReal)1.f / 60.f);

	//		wheel = pVeh->getWheel(1);
	//		wheel->tick(false, (NxReal)1000, (NxReal)0, (NxReal)1.f / 60.f);

	//		wheel = pVeh->getWheel(2);
	//		wheel->tick(false, (NxReal)1000, (NxReal)0, (NxReal)1.f / 60.f);

	//		wheel = pVeh->getWheel(3);
	//		wheel->tick(false, (NxReal)1000, (NxReal)0, (NxReal)1.f / 60.f);
	//	}

	//}
//	else
//	{
//		if (g_pKeyManager->isOnceKeyDown('W'))
//		{
//			camPos->x += 0.5;
//		}
//	}



	//
//	static float angle_ = D3DX_PI;
//	pCar1->RotationUp(D3DXToRadian(angle_));
}

void cTrack::LastUpdate()
{
	if (!GetPhysXData()) return;

}

void cTrack::Render()
{
	Object::Render();
	for each(Object* pObj in m_vecObject)
	{
		pObj->Render();
	}
}

void cTrack::SetData()
{
	//그저 메쉬일 뿐...
	//pCar1 = new cCar;
	//pCar1->LoadMesh("tc1");
	//m_vecObject.push_back(pCar1);


	////자동차 추가
	//pVeh = MgrPhysX->createCarWithDesc(NxVec3(0, 2, 0), true, true, false, false, false, MgrPhysXSDK);




}

void cTrack::LoadTrack(std::string FileName)
{
	//<<<<<<< HEAD
	//	//카메라 등록
	//	pCamera = pCam;

	Destroy();// 기존에 가지고 있던 정보 버리기
	std::string fullpath = "Maps/" + FileName + ".scn";
	std::fstream Load;
	Load.open(fullpath);

	char szTemp[1024];

	if (Load.is_open())
	{
		while (1)
		{
			if (Load.eof()) break;

			Load.getline(szTemp, 1024);
			if (szTemp[0] == ' ' || szTemp[0] == '\t') continue;
			else if (szTemp[0] == '/') continue;
			else if (szTemp[0] == 'M') // Map Load
			{
				char szMapFile[1024];
				sscanf_s(szTemp, "%*s %s", szMapFile, 1024);
				std::string Folder = "Maps/" + FileName;
				std::string Name = FileName + ".obj";
				SetMeshData(new cMesh);
				GetMeshData()->LoadMesh(Folder, Name);
				CreateTrackPhysX();

				return;
			}
			else if (szTemp[0] == 'O') //Object Load
			{
				Object* Obj = NULL;

				int tag;
				Load.getline(szTemp, 1024);
				sscanf_s(szTemp, "%*s %d", &tag);

				switch (tag)
				{
				case E_OBJECT_CHECKBOX:      Obj = new cCheckBox; break;
				case E_OBJECT_FOLLOWPOINT:   Obj = new cFollowPoint; break;
				case E_OBJECT_CAR: break;
				case E_OBJECT_MAP: break;
				case E_OBJECT_LIGHT:      Obj = new cLight; break;
				case E_OBJECT_STUFF:      Obj = new cStuff; break;
				case E_OBJECT_CAMERA: break;
				case E_OBJECT_PICKUP:      Obj = new cPickUp; break;
				case E_OBJECT_END: break;
				case E_OBJECT_NONE:   break;
				default: break;
				}

				Obj->SetTag((eOBJECT_TAG)tag);

				cPhysX* physx = new cPhysX;
				NxShapeType type((NxShapeType)0);
				NxVec3 position(0, 0, 0);
				NxVec3 sizeValue(0, 0, 0);
				NxF32 matR[9] = { 1,0,0,0,1,0,0,0,1 };
				USERDATA* pUserData = new USERDATA;
				bool isTrigger = false;
				bool isStatic_ = false;
				bool isGravity = true;

				NxVec3 worldPosition(0, 0, 0);
				NxVec3 localPosition(0, 0, 0);

				//Obj->SetPhysXData(physx);

				std::string strName;
				Load >> strName;
				Load >> strName;
				Obj->SetObjName(strName);

				while (1)
				{
					Load.getline(szTemp, 1024);
					if (szTemp[0] == 'I') // Attribute
					{
						int nID = 0;
						sscanf_s(szTemp, "%*s %d", &nID);
						Obj->SetID((eOBJECT_ID)nID);
						cMesh* mesh;
						if (Obj->GetTag() == E_OBJECT_CHECKBOX || nID == E_OBJECT_FOLLOWPOINT)
						{
							mesh = NULL;
						}
						else
						{
							mesh = new cMesh;
							std::string folder = "Objects/" + Obj->GetObjName();
							std::string fileName = Obj->GetObjName() + ".obj";
							if (mesh) mesh->LoadMesh(folder, fileName);
						}
						Obj->SetMeshData(mesh);
					}
					else if (szTemp[0] == 'P') //Position
					{
						float x, y, z;
						sscanf_s(szTemp, "%*s %f %f %f", &x, &y, &z);
						Obj->SetPosition(D3DXVECTOR3(x, y, z));
						worldPosition.x = x;
						worldPosition.y = y;
						worldPosition.z = z;
					}
					else if (szTemp[0] == 'S') //Scale
					{
						float x, y, z;
						sscanf_s(szTemp, "%*s %f %f %f", &x, &y, &z);
						Obj->SetSize(D3DXVECTOR3(x, y, z));
					}
					else if (szTemp[0] == 'R') //Rotation
					{
						float x, y, z;
						sscanf_s(szTemp, "%*s %f %f %f", &x, &y, &z);
						Obj->SetQuaternion(D3DXVECTOR3(x, y, z));
					}
					else if (szTemp[0] == 'X') //Physics
					{
						//물리정보입력
						if (szTemp[2] == 'A')
						{
							int isActor = 0;
							sscanf_s(szTemp, "%*s %d", &isActor);
							//	Obj->SetIsActor(isActor);
						}
						else if (szTemp[2] == 'T')
						{
							int nType = 0;
							sscanf_s(szTemp, "%*s %d", &nType);
							type = (NxShapeType)nType;
						}
						else if (szTemp[2] == 'O')
						{
							int t, s, g;
							sscanf_s(szTemp, "%*s %d %d %d", &t, &s, &g);
							isTrigger = t;
							isStatic_ = s;
							isGravity = g;
						}
						else if (szTemp[2] == 'P')
						{
							float x, y, z;
							sscanf_s(szTemp, "%*s %f %f %f", &x, &y, &z);
							position.x = x;
							position.y = y;
							position.z = z;

							localPosition.x = x;
							localPosition.y = y;
							localPosition.z = z;

						}
						else if (szTemp[2] == 'S')
						{
							float x, y, z;
							sscanf_s(szTemp, "%*s %f %f %f", &x, &y, &z);
							sizeValue.x = x;
							sizeValue.y = y;
							sizeValue.z = z;
						}
						else if (szTemp[2] == 'F')
						{
							float F[9];
							sscanf_s(szTemp, "%*s %f %f %f %f %f %f %f %f %f",
								&F[0], &F[1], &F[2], &F[3], &F[4], &F[5], &F[6], &F[7], &F[8]);
							for (int i = 0; i < 9; i++)
							{
								matR[i] = F[i];
							}
						}
					}
					else if (szTemp[0] == '#') //Push
					{
						if (Obj->GetTag() == E_OBJECT_LIGHT)
						{
							// Light Manager에 등록
							cLight* light = (cLight*)Obj;
							light->SetupPoint(m_nLightIdx++, C_WHITE, light->GetPosition(), 20);
							g_pLightManager->AddLight(light->GetLightIndex(), light);
						}
						else if (Obj->GetTag() == E_OBJECT_PICKUP)
						{
							NxActor* pActor = MgrPhysX->CreateActor(
								type,
								position + worldPosition + localPosition,
								matR,
								sizeValue,
								pUserData,
								isTrigger,
								isStatic_,
								isGravity);
							if (pActor)
							{
								physx->m_pActor = pActor;
								Obj->SetPhysXData(physx);
							}

							m_vecObject.push_back(Obj);

							//픽업오브젝트의 경우 조명이 필요하기때문에 생성해준다.
							cLight* light = new cLight;
							light->SetupPoint(m_nLightIdx++, C_YELLOW, light->GetPosition(), 5);
							g_pLightManager->AddLight(light->GetLightIndex(), light);
						}
						else
						{
							NxActor* pActor = MgrPhysX->CreateActor(
								type,
								position + worldPosition + localPosition,
								matR,
								sizeValue,
								pUserData,
								isTrigger,
								isStatic_,
								isGravity);
							if (pActor)
							{
								physx->m_pActor = pActor;
								Obj->SetPhysXData(physx);
							}

							m_vecObject.push_back(Obj);
						}
						break;
						
					}
				} // << : while Object
			}
		} // << : while 파일
	}
	else //파일 열기 실패
	{
		std::string pritfOut(FileName + ": 파일을 찾을 수 없습니다");
		MessageBoxA(g_hWnd, pritfOut.c_str(), "오류", MB_OK);
	}

	Load.close();



	NxActorDesc aDesc;
	NxPlaneShapeDesc sDesc;

	aDesc.setToDefault();
	sDesc.setToDefault();

	aDesc.shapes.pushBack(&sDesc);
	aDesc.globalPose.t = NxVec3(0, 0, 0);

	MgrPhysXScene->createActor(aDesc);

}

void cTrack::CreateTrackPhysX()
{
	if (GetMeshData()->m_pMesh)	//맵은 특별한 인자값을 주고 받지 않는다. (굳이 있다면 재질값 정도)
	{
		cPhysX* physx = new cPhysX;
		physx->m_pUserData = new USERDATA;
		NxActorDesc actorDesc;	actorDesc.setToDefault();
		NxBodyDesc  bodyDesc;	bodyDesc.setToDefault();

		//bodyDesc.flags |= NX_BF_KINEMATIC;

		NxTriangleMeshShapeDesc shapeDesc = MgrPhysX->CreateTringleMesh(GetMeshData()->m_pMesh);
		shapeDesc.materialIndex = 1; // 재질 : 0 (default)값
		shapeDesc.localPose.t = NxVec3(0, 0, 0);

		actorDesc.shapes.pushBack(&shapeDesc);
		//actorDesc.body = &bodyDesc;

		actorDesc.globalPose.t = NxVec3(0, 0, 0);
		actorDesc.userData = (physx->m_pUserData);

		physx->m_pActor = MgrPhysXScene->createActor(actorDesc);

		Object::SetPhysXData(physx);
		//맵의 물리 정보를 주고 받지 않기 때문에  SetActor(NULL) 이다.
	}
}
