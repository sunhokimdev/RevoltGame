#include "stdafx.h"
#include "cTrack.h"
#include "cLight.h"
#include "cCheckBox.h"
#include "cStuff.h"
#include "cFollowPoint.h"

cTrack::cTrack()
{
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
	if (!GetPhysXData()) return;

}

void cTrack::Render()
{
	Object::Render();
	for each(Object* pObj in m_vecObject)
	{
		pObj->Render();
	}

	//	for (size_t i = 0; i < m_vecObject.size(); ++i)
	//	{
	//		g_pD3DDevice->SetMaterial(&m_vecObject[i]->GetMeshData()->m_vecMtlTex[i]->GetMaterial());
	//
	//		if (m_vecObject[i]->GetTexture() != NULL)
	//		{
	//			g_pD3DDevice->SetTexture(0, m_vecObjMtlTex[i]->GetTexture());
	//		}
	//		m_pObjMesh->DrawSubset(i);
	//	}
}

void cTrack::LoadTrack(std::string FileName)
{
	Destory();// 기존에 가지고 있던 정보 버리기
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

				switch (tag)
				{
				case E_OBJECT_NONE:			Obj = NULL;				break;
				case E_OBJECT_CAR:			Obj = NULL;				break;
				case E_OBJECT_MAP:			Obj = NULL;				break;
				case E_OBJECT_LIGHT:		Obj = new cLight;		break;
				case E_OBJECT_STUFF:		Obj = new cStuff;		break;
				case E_OBJECT_CAMERA:		Obj = NULL;				break;
				case E_OBJECT_CHECKBOX:		Obj = new cCheckBox;	break;
				case E_OBJECT_FOLLOWPOINT:	Obj = new cFollowPoint; break;
				case E_OBJECT_END:			break;
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





				//Obj->SetPhysXData(physx);





				std::string strName;
				Load >> strName;
				Load >> strName;
				//Obj->SetObjName(strName);

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
							std::string objectName;
							switch (nID)
							{
							case  0: objectName = ""; break;
							case  1: objectName = ""; break;
							case  2: objectName = ""; break;
							case  3: objectName = ""; break;
							case  4: objectName = ""; break;
							case  5: objectName = ""; break;
							case  6: objectName = ""; break;
							case  7: objectName = ""; break;
							case  8: objectName = ""; break;
							case  9: objectName = ""; break;
							case 10: objectName = ""; break;
							}

							mesh = new cMesh;
							std::string folder = "Objects/" + objectName;
							std::string fileName = objectName + ".obj";
							if (mesh) mesh->LoadMesh(folder, fileName);
						}
						Obj->SetMeshData(mesh);
					}
					else if (szTemp[0] == 'P') //Position
					{
						float x, y, z;
						sscanf_s(szTemp, "%*s %f %f %f", &x, &y, &z);
						Obj->SetPosition(D3DXVECTOR3(x, y, z));
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
						NxActor* pActor = MgrPhysX->CreateActor(
							type,
							position,
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
		shapeDesc.materialIndex = 0; // 재질 : 0 (default)값
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
