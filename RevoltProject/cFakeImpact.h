#pragma once

#include "cImpact.h"

#define UPDATE_TIME 2
#define MAX_XSIZE 20

class cFakeImpact : public cImpact
{
private:
	LPDIRECT3DTEXTURE9		m_pTexture;					// 텍스쳐 이미지
	ST_SIZE							m_stSize;			// 이미지 사이즈
	LPD3DXSPRITE					m_pSprite;			// 스프라이트 이미지
	int m_fTime;		// 시간
	int m_index;		// 현재 위치;
	int m_currentX;		// 이미지 현재 X위치
	int m_currentY;		// 이미지 현재 y위치
public:
	cFakeImpact();
	virtual ~cFakeImpact();

	virtual void Setup();
	virtual void Update();
	virtual void Render();
	virtual void Destroy();
};

