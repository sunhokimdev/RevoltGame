#pragma once
#include "Thing.h"

class MtlTex;

//===================================================================
// - ## 10.15.23 ##
// - written by 김선호
// - 자동차에 대한 전반적인 클래스
//===================================================================

class Car : public Thing
{
private:
	ST_CAR					m_car;				// 자동차의 정보를 저장
	D3DXMATRIXA16		m_matWorld;			// 오브젝트의 월드 행렬
	LPD3DXMESH			m_pObjMesh;		// 오브젝트를 그릴 메쉬 변수
	std::vector<MtlTex*>		m_vecObjMtlTex;	// 오브젝트의 매터리얼를 저장하는 변수
	D3DXVECTOR3 m_vPosition;		// 자동차의 위치
public:
	Car();
	~Car();

	/*   기본적인 자동차 구조 메서드   */
	void Setup();
	void Update();
	void Render();

	void KeyEvent();
};

