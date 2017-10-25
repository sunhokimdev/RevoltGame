#pragma once

class MtlTex;
class Car;

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
	D3DXMATRIXA16			m_matWorld;			// 오브젝트의 월드 행렬
	D3DXMATRIXA16			m_matRX, m_matRY, m_matT, m_matR;			// 오브젝트의 X회전, Y회전, 움직임 회전, 최종 Rotation회전
	LPD3DXMESH				m_pObjMesh;		// 오브젝트를 그릴 메쉬 변수
	std::vector<MtlTex*>		m_vecObjMtlTex;	// 오브젝트의 매터리얼를 저장하는 변수
	std::vector<Thing*>		 m_vecChild;					// 자식 노드들

	float m_xAngle;		// 버튼 눌렀을 때 x축으로 회전 시키기 위한 회전 각도
	float m_yAngle;		// 오브젝트를 돌리기 위한 y축 회전 각도
	float m_prevYAngle;	// 이전 y각도값
	float m_prevXAngle;			// 이전 x각도값

	D3DXVECTOR3 m_vPosition;		// 오브젝트 위치
	D3DXVECTOR3 m_vTarget;			// 오브젝트의 다음 위치
	D3DXVECTOR3 m_vPrevPosition;	// 최초의 오브젝트 위치
public:
	/*   초기화 정적 매개변수   */
	static LOBBY* g_LobbyState;	// 로비의 상태

	/*    초기화 메서드    */
	Thing();
	virtual ~Thing();
	virtual void SetPosition(float x, float y, float z);
	virtual void SetRotationX(float angle);
	virtual void SetRotationY(float angle);
	virtual void SetTarget(float x, float y, float z);
	virtual void SetMesh(char* szFolder, char* szFile);
	SYNTHESIZE(D3DXMATRIXA16*, m_pParentWorldTM, ParentWorldTM);
	virtual void AddChild(Thing* pChild);

	/*    갱신, 렌더링 메서드    */
	virtual void Update();
	virtual void Render();
	virtual void Destroy();
};

