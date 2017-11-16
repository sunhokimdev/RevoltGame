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


	vecStartPos.push_back(D3DXVECTOR3(-0.0f, 0,  1.5));
	vecStartPos.push_back(D3DXVECTOR3(-1.5f, 0, -1.5));
	vecStartPos.push_back(D3DXVECTOR3(-3.0f, 0,  1.5));
	vecStartPos.push_back(D3DXVECTOR3(-4.5f, 0, -1.5));
	vecStartPos.push_back(D3DXVECTOR3(-6.0f, 0,  1.5));
	vecStartPos.push_back(D3DXVECTOR3(-7.5f, 0, -1.5));
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

}

void cTrack::LastUpdate()
{
	for each(Object* pObj in m_vecObject)
	{
		pObj->LastUpdate();
	}
}

void cTrack::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	Object::Render();
	for each(Object* pObj in m_vecObject)
	{
		pObj->Render();
	}
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

void cTrack::Destroy()
{
	for each(auto p in m_vecCheckBox)
	{
		p->Destroy();
		SAFE_DELETE(p);
	}
	for each(auto p in m_vecObject)
	{
		p->Destroy();
		SAFE_DELETE(p);
	}
	Object::Destroy();
}

void cTrack::SetData()
{

}

void cTrack::LoadTrack(std::string FileName)
{
	Destroy();// 기존에 가지고 있던 정보 버리기

	std::map<std::string, Object*> mapCheckBox;

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
			}
			else if (szTemp[0] == 'O') //Object Load
			{
				Object* Obj = NULL;

				int tag;
				Load.getline(szTemp, 1024);
				sscanf_s(szTemp, "%*s %d", &tag);

				ePhysXTag physxTag = E_PHYSX_TAG_NONE;
				switch (tag)
				{
				case E_OBJECT_CHECKBOX:
				{
					Obj = new cCheckBox;
					physxTag = ePhysXTag::E_PHYSX_TAG_CHECKBOX;	break;
				}
				case E_OBJECT_FOLLOWPOINT:   Obj = new cFollowPoint;	physxTag = ePhysXTag::E_PHYSX_TAG_NONE;	break;
				case E_OBJECT_CAR: break;
				case E_OBJECT_MAP: break;
				case E_OBJECT_LIGHT:		Obj = new cLight;			physxTag = ePhysXTag::E_PHYSX_TAG_NONE;	break;
				case E_OBJECT_STUFF:		Obj = new cStuff;			physxTag = ePhysXTag::E_PHYSX_TAG_NONE;	break;
				case E_OBJECT_CAMERA: break;
				case E_OBJECT_PICKUP:		Obj = new cPickUp;			physxTag = ePhysXTag::E_PHYSX_TAG_PICKUP;	break;
				case E_OBJECT_END: break;
				case E_OBJECT_NONE:   break;
				default: break;
				}

				Obj->SetTag((eOBJECT_TAG)tag);
				USERDATA* pUserData = new USERDATA;
				pUserData->USER_TAG = physxTag;
				pUserData->IsPickUp = NX_TRUE;
				cPhysX* physx = new cPhysX;
				NxShapeType type((NxShapeType)0);
				NxVec3 position(0, 0, 0);
				NxVec3 sizeValue(0, 0, 0);
				NxF32 matR[9] = { 1,0,0,0,1,0,0,0,1 };

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
								position + worldPosition,
								matR,
								sizeValue,
								E_PHYSX_MATERIAL_NONE,
								pUserData,
								isTrigger,
								isStatic_,
								isGravity);
							if (pActor)
							{
								g_pPhysX->SetActorGroup(pActor, E_PHYSX_TAG_PICKUP);
								
								physx->m_pActor = pActor;
								physx->m_pUserData = pUserData;
								physx->m_localPos = localPosition;
								Obj->SetPhysXData(physx);
							}

							m_vecObject.push_back(Obj);

							//픽업오브젝트의 경우 조명이 필요하기때문에 생성해준다.
							cLight* light = new cLight;
							light->SetupPoint(m_nLightIdx++, C_YELLOW, light->GetPosition(), 5);
							g_pLightManager->AddLight(light->GetLightIndex(), light);
						}
						else if (Obj->GetTag() == E_OBJECT_CHECKBOX)
						{
							//맵에 배치되어있는 장애물들...
							NxActor* pActor = MgrPhysX->CreateActor(
								type,
								position + worldPosition + localPosition,
								matR,
								sizeValue,
								E_PHYSX_MATERIAL_NONE,
								pUserData,
								isTrigger,
								isStatic_,
								isGravity);
							if (pActor)
							{
								g_pPhysX->SetActorGroup(pActor, E_PHYSX_TAG_CHECKBOX);
								
								physx->m_pActor = pActor;
								physx->m_pUserData = pUserData;
								physx->m_localPos = localPosition;
								Obj->SetPhysXData(physx);
							}
							mapCheckBox[Obj->GetObjName()] = Obj;
						}
						else
						{
							//맵에 배치되어있는 장애물들...
							NxActor* pActor = MgrPhysX->CreateActor(
								type,
								worldPosition - localPosition,
								matR,
								sizeValue,
								E_PHYSX_MATERIAL_ETC,
								pUserData,
								isTrigger,
								isStatic_,
								isGravity);
							if (pActor)
							{
								g_pPhysX->SetActorGroup(pActor, E_PHYSX_TAG_NONE);
								physx->m_pActor = pActor;
								physx->m_pUserData = pUserData;
								physx->m_localPos = localPosition;
								Obj->SetPhysXData(physx);
							}

							m_vecObject.push_back(Obj);
						}
						break;
					}
				} // << : while Object
			}
		} // << : while 파일
		Load.close();
	}
	else //파일 열기 실패
	{
		std::string pritfOut(FileName + ": 파일을 찾을 수 없습니다");
		MessageBoxA(g_hWnd, pritfOut.c_str(), "오류", MB_OK);
	}



	//체크박스 정리 (map->vector)
	//int id = 0;
	for (std::map<std::string, Object*>::iterator it = mapCheckBox.begin(); it != mapCheckBox.end(); it++)
	{
		m_vecCheckBox.push_back(it->second);
	}
	//Next 값 설정
	for (int i = 0; i < m_vecCheckBox.size(); i++)
	{
		cCheckBox* p = (cCheckBox*)m_vecCheckBox[i];

		p->GetPhysXData()->m_pUserData->CheckBoxID = i;

		if (i + 1 == m_vecCheckBox.size())
			p->SetNextCheckBox((cCheckBox*)m_vecCheckBox[0]);
		else
			p->SetNextCheckBox((cCheckBox*)m_vecCheckBox[i + 1]);
	}
}

void cTrack::CreateTrackPhysX()
{
	if (GetMeshData()->m_pMesh)	//맵은 특별한 인자값을 주고 받지 않는다. (굳이 있다면 재질값 정도)
	{
		cPhysX* physx = new cPhysX;

		USERDATA* userData = new USERDATA;
		NxActorDesc actorDesc;	actorDesc.setToDefault();
		NxBodyDesc  bodyDesc;	bodyDesc.setToDefault();


		//bodyDesc.flags |= NX_BF_KINEMATIC;

		NxTriangleMeshShapeDesc shapeDesc = MgrPhysX->CreateTringleMesh(GetMeshData()->m_pMesh);

		shapeDesc.materialIndex = 1; // 재질 : 0 (default)값
		shapeDesc.localPose.t = NxVec3(0, 0, 0);
		shapeDesc.group = E_PHYSX_TAG_TRACK;
		actorDesc.shapes.pushBack(&shapeDesc);
		//actorDesc.body = &bodyDesc;

		actorDesc.globalPose.t = NxVec3(0, 0, 0);
		actorDesc.userData = (userData);
		actorDesc.name = "map";
		actorDesc.group = E_PHYSX_TAG_TRACK;

		physx->m_pActor = MgrPhysXScene->createActor(actorDesc);

		Object::SetPhysXData(physx);
		//맵의 물리 정보를 주고 받지 않기 때문에  SetActor(NULL) 이다.
	}
}
