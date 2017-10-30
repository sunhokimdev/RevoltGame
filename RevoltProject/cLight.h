#pragma once
#include "Object.h"

class cCar;

class cLight :public Object
{
private:
	D3DLIGHT9 m_stLight; //조명 정보를 저장할 구조체
	int m_nIndex;
	cCar* m_pCar;

public:
	cLight();
	virtual ~cLight();

	virtual void Setup(int nIndex, _D3DLIGHTTYPE type, D3DXCOLOR color, D3DXVECTOR3 position);
	void SetupDirectional(int nIndex, D3DXCOLOR color, D3DXCOLOR direc);
	void SetupPoint(int nIndex, D3DXCOLOR color, D3DXVECTOR3 position, float range);
	void SetupSpot(int nIndex, D3DXCOLOR color, D3DXVECTOR3 position, D3DXCOLOR direc, float range, float Phi = (D3DX_PI / 2), float Theta = (D3DX_PI / 2));
	virtual void Update();
	virtual void Destroy();
	virtual void Switch(bool on);

	int GetLightIndex() { return m_nIndex; }
	D3DLIGHT9* GetLight() { return &m_stLight; }
	void LinkCar(cCar* car) { m_pCar = car; }
};

