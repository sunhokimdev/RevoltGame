#pragma once

#include "Object.h"

class MtlTex;

class Thing : public Object
{
protected:
	std::vector<Thing*>	m_vecChild;			//	오브젝트내 자식(조각)들을 저장할 벡터
	D3DXMATRIXA16		m_matWorld;
	LPD3DXMESH			m_pObjMesh;		// 오브젝트를 그릴 메쉬 변수
	std::vector<MtlTex*>		m_vecObjMtlTex;	// 오브젝트의 매터리얼를 저장하는 변수

	float m_xAngle;		// 버튼 눌렀을 때 x축으로 회전 시키기 위한 회전 각도
	float m_yAngle;		// 오브젝트를 돌리기 위한 y축 회전 각도
	bool m_isMove;	// 움직이는 오브젝트인지 체크
	bool m_isRot;		// x축 회전 가능 
	D3DXVECTOR3 m_vPosition;

public:
	/*   초기화 메서드   */
	Thing();
	virtual ~Thing();
	virtual void SetPosition(float x, float y, float z);
	virtual void SetRotationX(float angle);
	virtual void SetRotationY(float angle);
	void SetMesh(char* szFolder, char* szFile);
	void SetIsMove(bool isMove);
	void SetIsRot(bool isRot);

	virtual void Update();
	virtual void Render();
	virtual void Destroy();
};

