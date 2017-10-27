#pragma once
#include "UIObject.h"

#define MAX_ID 11

class UIImageView : public UIObject
{
protected:
	/*   맵 노이즈 선택   */
	float LeftNoiseX;
	float RightNoiseX;
	float UpNoiseY;
	float DownNoiseY;

	/*   아이템 창 뜨게 하기 위한 작업   */
	int m_itemPrevID;	// 아이템의 이전 아이디
	int m_itemID;		// 아이템의 현재 아이디
	int m_alpha;			// 알파 값 적용시켜주기
	int m_fTime;			// 알파 값 갱신 해주기 위한 시간 값
	int m_updateTIme;

	LPDIRECT3DTEXTURE9		m_pTexture;			// 이미지 그리기 작업
public:
	UIImageView();
	virtual ~UIImageView();
	virtual void SetTexture(char* szFullPath);
	virtual void Update();
	virtual void Render(LPD3DXSPRITE pSprite) override;

	SYNTHESIZE(bool, m_isMove, IsMove);
	SYNTHESIZE(bool, m_isBoard, IsBoard);		
	SYNTHESIZE(bool, m_isNoise, IsNoise);
	SYNTHESIZE(bool, m_isItem, IsItem);
	SYNTHESIZE(float, m_xSize, XSize);
	SYNTHESIZE(float, m_ySize, YSize);
	SYNTHESIZE(D3DXCOLOR, m_color, Color);

};

