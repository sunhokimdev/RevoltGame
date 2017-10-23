#pragma once

class MtlTex;

#define SELECT_YANGLE 3.7f

#include "Object.h"

//===================================================================
// - ## 10.15.19 ##
// - written by 김선호
// - 오브젝트를 관리하는 오브젝트 클래스 추가
//===================================================================

class MtlTex;

class Thing : public Object
{
protected:
	std::vector<Thing*>	m_vecChild;			//	오브젝트내 자식(조각)들을 저장할 벡터
	D3DXMATRIXA16		m_matWorld;			// 오브젝트의 월드 행렬
	LPD3DXMESH			m_pObjMesh;		// 오브젝트를 그릴 메쉬 변수
	std::vector<MtlTex*>		m_vecObjMtlTex;	// 오브젝트의 매터리얼를 저장하는 변수

	float m_xAngle;		// 버튼 눌렀을 때 x축으로 회전 시키기 위한 회전 각도
	float m_yAngle;		// 오브젝트를 돌리기 위한 y축 회전 각도
	float m_prevYAngle;	// 이전 y각도값
	bool m_isMove;	// 움직이는 오브젝트인지 체크
	bool m_isRot;		// x축 회전 가능한지 체크
	D3DXVECTOR3 m_vPosition;		// 오브젝트 위치
	D3DXVECTOR3 m_vTarget;			// 오브젝트의 다음 위치
	D3DXVECTOR3 m_vPrevPosition;	// 최초의 오브젝트 위치

	LOBBY	m_lobby;	// 어느 로비 상태에서 이벤트를 발생할지 묻는 여부
	int		m_stage;	// 현재 스테이지 : 0 - 프론트, 1이상 맵 스테이지
	int		m_index;	// 현재 선택 위치

public:
	/*   초기화 메서드   */
	static float g_xRotAngle;
	static LOBBY* g_LobbyState;
	static int*	g_select;

	Thing();
	virtual ~Thing();
	virtual void SetPosition(float x, float y, float z);
	virtual void SetRotationX(float angle);
	virtual void SetRotationY(float angle);
	void SetTarget(float x, float y, float z);
	void SetMesh(char* szFolder, char* szFile);
	void SetIsMove(bool isMove);
	void SetIsRot(bool isRot);
	void SetLobby(LOBBY lobby);
	void SetIndex(int index);

	virtual void Update();
	virtual void Render();
	virtual void Destroy();
};

