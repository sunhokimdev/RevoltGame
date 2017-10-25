#pragma once

#include "Thing.h"

class Car;

class CarBox : public Thing
{
private:
	IDirect3DVertexBuffer9* VB;								// 자동차 박스의 표지를 그릴 버텍스 버퍼
	LPDIRECT3DTEXTURE9	m_carboxTexture;			// 자동차 박스에 입힐 텍스쳐
	int m_index;													// 오브젝트의 해당 인덱스
	Car*	m_car;					// 자동차
public:
	CarBox();
	virtual ~CarBox();

	static int*	g_select;										// 로비에서 선택된 인덱스
	static std::vector<ST_CAR>	g_vecCar;				// 자동차의 정보를 담고 있는 벡터 변수

	/*   기본 루프 메서드   */
	virtual void Setup();
	virtual void Update();
	virtual void Render();

	void SetTextFile(char* szFile);
	void SetIndex(int index);
};

