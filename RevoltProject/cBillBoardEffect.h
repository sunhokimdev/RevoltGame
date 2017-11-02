#pragma once

class UIImageView;

//===================================================================
// - written by DongHun
// - Effect ±¸Çö
//===================================================================

/*          EFFECT TYPE          */
enum EFFECT_TYPE
{
	WATER = 1,
};

class cBillBoardEffect
{
private:
	LPDIRECT3DTEXTURE9		m_pTexture;					// EffectImageTexture
	ST_SIZE					m_stSize;					// Set EffectImageSize
	EFFECT_TYPE				m_effectType;				// Effect Type

public:
	cBillBoardEffect();
	~cBillBoardEffect();

	void SetTexture(char* szFullPath);
	void SetFrameTexture(char* szFullPath, int MaxFrameX = 1, int MaxFrameY = 1);	// Set Frame EffectImageTexture
	void SetEffectType(int TypeNum);												// 1 = WATER
	void FrameUpdate();																// FrameUpdate

	void BillboardRender(LPD3DXSPRITE Sprite,										// Billboard Render
		float posX = 0.0f, float posY = 0.0f, float posZ = 0.0f,
		float sizeX = 1.0f, float sizeY = 1.0f, float sizeZ = 1.0f);

	//void BillboardFrameRender(LPD3DXSPRITE Sprite,									// Billboard FrameRender
	//	float posX = 0.0f, float posY = 0.0f, float posZ = 0.0f,
	//	float sizeX = 1.0f, float sizeY = 1.0f, float sizeZ = 1.0f);
	void Destroy();

	SYNTHESIZE(int, m_MaxFrameX, MaxFrameX);
	SYNTHESIZE(int, m_MaxFrameY, MaxFrameY);
	SYNTHESIZE(int, m_CurrentFrameX, CurrentFrameX);
	SYNTHESIZE(int, m_CurrentFrameY, CurrentFrameY);
	SYNTHESIZE(int, m_FrameTime, FrameTime);
	SYNTHESIZE(bool, m_isFrameRender, FrameRender);
	SYNTHESIZE(bool, m_isActive, Active);
};

