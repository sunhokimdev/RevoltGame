#pragma once

#include "cImpact.h"

#define UPDATE_TIME 3

class cPlasmaImpact : public cImpact
{
private:
	LPD3DXSPRITE	m_pSprite;			// 스프라이트 출력
	LPDIRECT3DTEXTURE9		m_pTexture;		// 텍스쳐 이미지
	ST_SIZE							m_stSize;		// 텍스쳐 사이즈
	int m_fTime;		// 시간
	int m_index;		// 현재 위치;
	int m_currentX;		// 이미지 현재 X위치
	int m_currentY;		// 이미지 현재 y위치
public:
	cPlasmaImpact();
	virtual ~cPlasmaImpact();

	virtual void Setup();
	virtual void Update();
	virtual void Render();
	virtual void UpdateSetPosition(D3DXVECTOR3 v) { m_itemPos = v; };
};

