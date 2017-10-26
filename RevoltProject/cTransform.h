#pragma once

class NxVec3;
#include "Nx.h"

class cTransform
{
protected:

	SYNTHESIZE(D3DXVECTOR3, m_position, Position);
	SYNTHESIZE(D3DXVECTOR3, m_size, Size);
	SYNTHESIZE(D3DXVECTOR3, m_direction, Direction);
	D3DXQUATERNION m_Quaternion;

private:
	//ArrowVector
	D3DXVECTOR3 front;
	D3DXVECTOR3 right;
	D3DXVECTOR3 up;

	bool DebugTr;
public:

	cTransform();
	~cTransform();


	void Update();
	void Render();


	// 현재 Transform의 포인터를 가져옵니다.
	cTransform* GetTransform() { return this; }

	// 다른 Transform의 포인터를 받아 값을 초기화합니다.
	void SetTransform(cTransform* Tr)
	{
		SetPosition(Tr->GetPosition());
		SetSize(Tr->GetSize());
		m_Quaternion = Tr->m_Quaternion;
		front = Tr->front;
		right = Tr->right;
		up = Tr->up;
		//	m_matWorld = Tr->m_matWorld;
		DebugTr = Tr->DebugTr;
	}



	//현재 백터의 정면을 향하는 백터
	//현재 백터의 우측을 향하는 백터
	//현재 백터의 위를 향하는 백터
	D3DXVECTOR3 GetFrontVec();
	D3DXVECTOR3 GetRightVec();
	D3DXVECTOR3 GetUpVec();

	//쿼터니언 값을 반환
	D3DXQUATERNION GetQuaternion() { return m_Quaternion; }
	//쿼터니언 값을 세팅
	void SetQuaternion(D3DXQUATERNION quaternion)
	{
		m_Quaternion = quaternion;
		ArrowVectorSetting();
	}
	void SetQuaternion(float x, float y, float z, float w)
	{
		m_Quaternion = D3DXQUATERNION(x, y, z, w);
		ArrowVectorSetting();
	}
	void SetQuaternion(float Yam, float Pitch, float Roll)
	{
		D3DXQuaternionRotationYawPitchRoll(&m_Quaternion, Yam, Pitch, Roll);
		ArrowVectorSetting();
	}
	void SetQuaternion(D3DXMATRIX matR)
	{
		D3DXQuaternionRotationMatrix(&m_Quaternion, &matR);
		ArrowVectorSetting();
	}
	void SetQuaternion(D3DXVECTOR3 vecDir)
	{
		//자세한 과정은 VectorToQuaternion 함수 참고
		// !! Roll 값은 0으로 초기화된다 !!
		m_direction = vecDir;
		VectorToQuaternion(vecDir, true, true);
		ArrowVectorSetting();
	}

	void SetPosition(D3DXMATRIX matT)
	{
		m_position.x = matT._41; m_position.y = matT._42; m_position.z = matT._43;
	}
	void SetPosition(float x, float y, float z)
	{
		m_position.x = x;
		m_position.y = y;
		m_position.z = z;
	}


	//PhsyX 관련 변환 (불안정)
	NxVec3 DxVec3ToNxVec3(D3DXVECTOR3 dxVec3);
	NxF32* DxMatToNxF32(D3DXMATRIX dxMat);
	D3DXVECTOR3 NxVec3ToDxVec3(NxVec3 nxVec3);
	D3DXMATRIX NxF32ToDxMat(NxF32* nxF32);

	void SetNxVec3(NxVec3 NxPos);
	void SetNxF32(NxF32* mtl);
	//	void GetScreenPos();

	void ArrowVectorSetting();

	// VectorToQuaternion(----);
	// vec를 이용한 회전량(yam,pitch) 계산
	// x(yam) 와 y(pitch) 축 회전 을 기본으로하며, 
	// z(roll) 값은 null (null 이 아닐경우 임의의 값을 넣어주어 회전시킬 수 있다. 기본은 0)
	// 
	// 주의 !
	// SetQuaternion(D3DXVECTOR3 vecDir) 를 이용하지 않고
	// 이 함수를 직접 이용할 경우에는 함수가 끝나고 
	// ArrowVectorSetting() 를 반드시 호출할 것.
	void VectorToQuaternion(D3DXVECTOR3 vec, bool rotY, bool rotX, float* pRoll = nullptr)
	{
		D3DXQUATERNION quaternion;
		D3DXQuaternionIdentity(&quaternion);


		D3DXVECTOR3 vec_y(0, 0, 0);
		D3DXVECTOR3 vec_p(0, 0, 0);
		D3DXVec3Normalize(&vec_y, &vec);
		D3DXVec3Normalize(&vec_p, &vec);

		float yam = 0;
		float pitch = 0;
		float roll = 0;

		if (rotY)
		{
			if (abs(vec_y.x) > 0.0001 && abs(vec_y.z) > 0.0001)
			{
				yam = atan2(vec_y.x, vec_y.z);
				if (cTransform::up.y < 0)
				{
					yam += D3DXToRadian(180);
				}
			}
			else
			{
			//	std::cout << "!";
				if (abs(vec_y.x) < 0.0001 && abs(vec_y.x) < 0.0001)
				{
					//Pass
					//위 또는 아래.
				}
				else
				{
					if (vec_y.z > 0 && abs(vec_y.x) < 0.0001)
					{
						//정면
						yam = D3DXToRadian(0);
						if (cTransform::up.y < 0)
						{
							yam += D3DXToRadian(180);
						}
					}
					if (vec_y.z < 0 && abs(vec_y.x) < 0.0001)
					{
						//후면
						yam = D3DXToRadian(180);
						if (cTransform::up.y < 0)
						{
							yam += D3DXToRadian(180);
						}
					}
					if (vec_y.x > 0 && abs(vec_y.z) < 0.0001)
					{
						//우
						yam = D3DXToRadian(90);
						if (cTransform::up.y < 0)
						{
							yam += D3DXToRadian(180);
						}
					}
					if (vec_y.x < 0 && abs(vec_y.z) < 0.0001)
					{
						//좌
						yam = D3DXToRadian(-90);
						if (cTransform::up.y < 0)
						{
							yam += D3DXToRadian(180);
						}
					}
				}
			}
		}

		D3DXVec3Normalize(&vec_p, &vec_p);

		if (rotX)
		{
			D3DXVECTOR3 rotYamVec(0, 0, 1);
			D3DXMATRIXA16 rotR;
			D3DXMatrixRotationY(&rotR, yam);
			D3DXVec3TransformNormal(&rotYamVec, &rotYamVec, &rotR);

			float dot = D3DXVec3Dot(&vec_y, &rotYamVec);

			if (dot > 1.f)
			{
				dot = 0.999999f;
			}
			if (dot < -1.f)
			{
				dot = -0.999999f;
			}
			dot = roundf(dot * 100000) / 100000.f;
			pitch = -acos(dot);
			if (vec_p.y < 0.f) pitch *= -1;
		}

		if (pRoll) roll = *pRoll;
		D3DXQuaternionRotationYawPitchRoll(&m_Quaternion, yam, pitch, roll);
	}

	//Front 기준으로 회전 (오른손회전)
	//Up 백터 기준으로 회전
	//Right 기준으로 회전
	void RotationFront(float angle)
	{
		D3DXMATRIXA16 matWorld;
		D3DXMatrixRotationQuaternion(&matWorld, &m_Quaternion);

		D3DXQUATERNION quaR;
		D3DXQuaternionRotationAxis(&quaR, &front, angle);
		D3DXMATRIXA16 matR;
		D3DXMatrixRotationQuaternion(&matR, &quaR);

		D3DXQuaternionRotationMatrix(&m_Quaternion, &(matWorld * matR));
		ArrowVectorSetting();
	}
	void RotationUp(float angle)
	{
		D3DXMATRIXA16 matWorld;
		D3DXMatrixRotationQuaternion(&matWorld, &m_Quaternion);

		D3DXQUATERNION quaR;
		D3DXQuaternionRotationAxis(&quaR, &up, angle);
		D3DXMATRIXA16 matR;
		D3DXMatrixRotationQuaternion(&matR, &quaR);

		D3DXQuaternionRotationMatrix(&m_Quaternion, &(matWorld * matR));
		ArrowVectorSetting();
	}
	void RotationRight(float angle)
	{
		D3DXMATRIXA16 matWorld;
		D3DXMatrixRotationQuaternion(&matWorld, &m_Quaternion);

		D3DXQUATERNION quaR;
		D3DXQuaternionRotationAxis(&quaR, &right, angle);
		D3DXMATRIXA16 matR;
		D3DXMatrixRotationQuaternion(&matR, &quaR);

		D3DXQuaternionRotationMatrix(&m_Quaternion, &(matWorld * matR));
		ArrowVectorSetting();
	}

	// pos, size, quaternion 을 이용하여 만들어지는
	// 매트릭스를 반환한다,
	// bool -> S,R,T 값을 포함/제외 할 지 선택
	// 기본은 true
	D3DXMATRIXA16 GetMatrix(bool S = true, bool R = true, bool T = true)
	{
		D3DXMATRIXA16 matWorld;
		D3DXMatrixIdentity(&matWorld);
		if (S)
		{
			D3DXMATRIXA16 matS;
			D3DXMatrixIdentity(&matS);
			D3DXMatrixScaling(&matS, m_size.x, m_size.y, m_size.z);
			matWorld *= matS;
		}
		if (R)
		{
			D3DXMATRIXA16 matR;
			D3DXMatrixIdentity(&matR);
			D3DXMatrixRotationQuaternion(&matR, &m_Quaternion);
			matWorld *= matR;
		}
		if (T)
		{
			D3DXMATRIXA16 matT;
			D3DXMatrixIdentity(&matT);
			D3DXMatrixTranslation(&matT, m_position.x, m_position.y, m_position.z);
			matWorld *= matT;
		}
		return matWorld;
	}
	D3DXMATRIXA16 GetMatrixScale()
	{
		return GetMatrix(true, false, false);
	}
	D3DXMATRIXA16 GetMatrixRotation()
	{
		return GetMatrix(false, true, false);
	}
	D3DXMATRIXA16 GetMatrixTranslation()
	{
		return GetMatrix(false, false, true);
	}
};

