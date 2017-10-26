#pragma once

#include <fstream>
#include <iostream>
#include "cStringUtil.h"
#include "cPhysXManager.h"

class cPhysX
{
public:
	NxActor*  m_pActor;		//save/load (X)		->월드좌표 + 로컬좌표 저장
	USERDATA* m_pUserData;	//save/load (X)

	NxMat34 m_worldPose;	//save/load (X)		->월드좌표 저장
	NxMat34 m_localPose;	//save/load (X)		->로컬좌표 저장


	cPhysX();
	~cPhysX();

	std::string actorName;						//save/load
	NxVec3 m_position;							//save/load
	NxVec3 m_sizeValue;							//save/load
	NxVec3 m_dirValue;							//save/load
	NxF32 m_matR[9] = { 1,0,0,0,1,0,0,0,1 };	//save/load


	bool m_isTrigger = false;	//save/load
	bool m_isStatic_ = false;	//save/load
	bool m_isGravity = true;	//save/load

	NxShapeType m_type;			//save/load

	void SetPosition(NxVec3 pos)
	{
		m_pActor->getGlobalPose().t = pos;
	}
	void SetPosition(D3DXVECTOR3 vec3)
	{
		SetPosition(NxVec3(vec3.x, vec3.y, vec3.z));
	}
	void SetLocalPosition(NxVec3 pos)
	{
		m_localPose.t = pos;
	}
	void SetLocalPosition(D3DXVECTOR3 vec3)
	{
		SetLocalPosition(NxVec3(vec3.x, vec3.y, vec3.z));
	}

	void SetRotation(D3DXMATRIX mat16)
	{
		NxF32 nxf[9] = { 1,0,0,0,1,0,0,0,1 };

		nxf[0] = mat16._11;
		nxf[1] = mat16._12;
		nxf[2] = mat16._13;
		nxf[3] = mat16._21;
		nxf[4] = mat16._22;
		nxf[5] = mat16._23;
		nxf[6] = mat16._31;
		nxf[7] = mat16._32;
		nxf[8] = mat16._33;

		SetRotation(nxf);


	//	m_pActor->desc
	}
	void SetRotation(NxF32* nxf32)
	{
		NxMat33 mat33;
		mat33.setColumnMajor(nxf32);
		SetRotation(mat33);
	}
	void SetRotation(NxMat33 mat33)
	{
		m_pActor->getGlobalPose().M = mat33;
	}

	void SetLocalRotation(D3DXMATRIX mat16)
	{
		NxF32 nxf[9] = { 1,0,0,0,1,0,0,0,1 };

		nxf[0] = mat16._11;
		nxf[1] = mat16._12;
		nxf[2] = mat16._13;
		nxf[3] = mat16._21;
		nxf[4] = mat16._22;
		nxf[5] = mat16._23;
		nxf[6] = mat16._31;
		nxf[7] = mat16._32;
		nxf[8] = mat16._33;

		SetLocalRotation(nxf);
	}
	void SetLocalRotation(NxF32* nxf32)
	{
		NxMat33 mat33;
		mat33.setColumnMajor(nxf32);
		SetLocalRotation(mat33);
	}
	void SetLocalRotation(NxMat33 mat33)
	{
		m_localPose.M = mat33;
	}

	NxVec3 GetPositionToNxVec3()
	{
		return m_pActor->getGlobalPose().t;
	}
	D3DXVECTOR3 GetPositionToD3DXVec3()
	{
		NxVec3 pos = m_pActor->getGlobalPose().t;
		return D3DXVECTOR3(pos.x, pos.y, pos.z);
	}
	NxMat33 GetRotationToNxMat33()
	{
		return m_pActor->getGlobalPose().M;
	}
	D3DXMATRIXA16 GetRotationToD3DXMat16()
	{
		D3DXMATRIXA16 mat16;
		D3DXMatrixIdentity(&mat16);

		NxF32 mat[9] = { 1,0,0,0,1,0,0,0,1 };
		m_pActor->getGlobalPose().M.getColumnMajor(mat);

		mat16._11 = mat[0];
		mat16._12 = mat[1];
		mat16._13 = mat[2];
		mat16._21 = mat[3];
		mat16._22 = mat[4];
		mat16._23 = mat[5];
		mat16._31 = mat[6];
		mat16._32 = mat[7];
		mat16._33 = mat[8];

		return mat16;
	}

	void Destory()
	{
		if (m_pActor) MgrPhysXScene->releaseActor(*m_pActor);
		m_pActor = NULL;

		SAFE_DELETE(m_pUserData);
	}
	void Update()
	{
		//저장을 위한 정보 갱신
		m_position = m_localPose.t;
		NxMat33 mat33 = m_localPose.M;
		mat33.getColumnMajor(m_matR);
	}


#define TAB	'\t'
#define SPACE ' '
#define POPDATA Data[sI++]
/*	void LoadPhysX(std::string fileName)
	{
		std::string fullpath = "Object/Objects/PhysXData/PhysXData.phx";
		std::ifstream LOAD(fullpath);

		if (LOAD.is_open())
		{
			while (!LOAD.eof())
			{
				CHAR Text_[1024] = {};
				LOAD.getline(Text_, 1024);
				std::string Text = Text_;

				std::vector<CHAR> Cut;
				Cut.push_back(' ');		// 데이터 구분 단위
				Cut.push_back(TAB);		// 데이터 구분 단위

				std::vector<std::string> Data;
				cStringUtil::Split(&Data, &Cut, &Text);
				// 데이터 읽을 준비 완료.


				int sI = 0; //startIndex
				while (Data[sI].length() == 1)
				{
					CHAR cut = Data[sI][0];
					bool isCut = false;
					for (int i = 0; i < Cut.size(); i++)
					{
						if (cut == Cut[i]) { isCut = true; ++sI; break; }
						//해당 index 에서 cut 이 발생하면 데이터를 버리고 다음 index검사
					}
					if (!isCut) break;	//cut 이 일어나지 않으면 빠져나온다.
				}
				//유효한 시작 지점 검사 완료


				//데이터 로드 시작.
				std::string dateTitle = POPDATA; //  POPDATA = Data[sI++] (현재 데이터를 빼낸 뒤 다음 데이터를 준비)
				if (dateTitle == "DATA_NAME")
				{
					actorName = POPDATA;

					continue;
				}
				if (dateTitle == "SHAPE_TYPE")
				{
					m_type = (NxShapeType)cStringUtil::ToInt(POPDATA);
					continue;
				}
				if (dateTitle == "IsTrigger")
				{
					m_isTrigger = (bool)cStringUtil::ToInt(POPDATA);
					continue;
				}
				if (dateTitle == "isStatic_")
				{
					m_isStatic_ = (bool)cStringUtil::ToInt(POPDATA);
					continue;
				}
				if (dateTitle == "isGravaty")
				{
					m_isGravity = (bool)cStringUtil::ToInt(POPDATA);
					continue;
				}
				if (dateTitle == "POS_XYZ")
				{
					m_position.x = cStringUtil::ToFloat(POPDATA);
					m_position.y = cStringUtil::ToFloat(POPDATA);
					m_position.z = cStringUtil::ToFloat(POPDATA);
					continue;
				}
				if (dateTitle == "SIZE_XYZ")
				{
					m_sizeValue.x = cStringUtil::ToFloat(POPDATA);
					m_sizeValue.y = cStringUtil::ToFloat(POPDATA);
					m_sizeValue.z = cStringUtil::ToFloat(POPDATA);
					continue;
				}
				if (dateTitle == "FXU32_[9]")
				{
					m_matR[0] = cStringUtil::ToFloat(POPDATA);
					m_matR[1] = cStringUtil::ToFloat(POPDATA);
					m_matR[2] = cStringUtil::ToFloat(POPDATA);
					m_matR[3] = cStringUtil::ToFloat(POPDATA);
					m_matR[4] = cStringUtil::ToFloat(POPDATA);
					m_matR[5] = cStringUtil::ToFloat(POPDATA);
					m_matR[6] = cStringUtil::ToFloat(POPDATA);
					m_matR[7] = cStringUtil::ToFloat(POPDATA);
					m_matR[8] = cStringUtil::ToFloat(POPDATA);
					continue;
				}
			}//while(eof)

			//creatActor

			NxActor* pActor = MgrPhysX->CreateActor(m_type, m_position, m_matR, m_sizeValue, m_pUserData, m_isTrigger, m_isStatic_, m_isGravity);
			if (pActor)
			{
				//새 pActor 생성에 성공하면 
				//기존에 있던 정보내용 초기화하고
				//새 pActor 로 등록 
				MgrPhysXScene->releaseActor(*m_pActor);
				m_pActor = NULL;

				m_pActor = pActor;
			}

		}//LOAD.is_open()
		else
		{
			//	fullpath = "Object/Objects/PhysXData/" + fileName + "/" + fileName + ".phx";
			//	LOAD = fullpath;
			//	if (LOAD.is_open())
			//	{
			//	}
			//	else
			//	{// 파일을 찾지 못한 경우 구 로 생성
			m_position = NxVec3(0, 0, 0);
			m_sizeValue = NxVec3(0.5, 0, 0);
			m_type = NX_SHAPE_SPHERE;
			m_isTrigger = true;
			m_isStatic_ = true;
			m_isGravity = false;
			m_pActor = MgrPhysX->CreateActor(m_type, m_position, NULL, m_sizeValue,
				m_pUserData, m_isTrigger, m_isStatic_, m_isGravity);
			//	}
		}
		LOAD.close();
	}
	void SavePhysX(std::string fileName)
	{
		std::string fullpath = "Object/Objects/" + fileName + "/" + fileName + ".phx";

		std::ofstream SAVE(fullpath);
		if (SAVE.is_open())
		{
			//SAVE << "OBJECT_NAME" << TAB << fileName << std::endl;

			SAVE << "SHAPE_TYPE" << TAB << (int)m_type << std::endl;

			SAVE << "OPTION" << std::endl;
			SAVE << TAB << "IsTrigger" << TAB << m_isTrigger << std::endl;
			SAVE << TAB << "isStatic_" << TAB << m_isStatic_ << std::endl;
			SAVE << TAB << "isGravaty" << TAB << m_isGravity << std::endl;

			SAVE << "POS_XYZ" << TAB
				<< m_position.x << TAB
				<< m_position.y << TAB
				<< m_position.z << std::endl;

			SAVE << "SIZE_XYZ" << TAB
				<< m_sizeValue.x << TAB
				<< m_sizeValue.y << TAB
				<< m_sizeValue.z << std::endl;

			SAVE << "FXU32_[9]" << TAB
				<< m_matR[0] << TAB << m_matR[1] << TAB << m_matR[2] << TAB
				<< m_matR[3] << TAB << m_matR[4] << TAB << m_matR[5] << TAB
				<< m_matR[6] << TAB << m_matR[7] << TAB << m_matR[8] << std::endl;
		}
	}
	*/
};

