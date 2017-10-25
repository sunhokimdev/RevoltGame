#pragma once
#include "Thing.h"

class MtlTex;

struct ST_WHEEL
{
	LPD3DXMESH				m_pObjMesh;		// 바퀴 오브젝트를 그릴 메쉬 변수
	std::vector<MtlTex*>		m_vecObjMtlTex;	// 오브젝트의 매터리얼를 저장하는 변수
	D3DXVECTOR3				m_vPos;				// 바퀴 오브젝트의 상대적 위치
};

//===================================================================
// - ## 10.15.23 ##
// - written by 김선호
// - 자동차에 대한 전반적인 클래스
//===================================================================

class Car : public Thing
{
private:
	ST_CAR	m_stCar;				// 자동차의 대한 정보를 저장
public:
	Car();
	virtual ~Car();

	/*   기본적인 자동차 구조 메서드   */
	virtual void Setup();
	virtual void Update();
	virtual void Render();

	void SetSTCar(ST_CAR car);
	void SetMeshWheel(char* szFolder, char* szName);
	void WheelRender();
	void KeyEvent();
};

