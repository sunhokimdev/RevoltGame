#pragma once

#include "UIObject.h"

//======================================
// - ## 10.11.17 ##
// - written by 김선호
// - 이미지파일(png파일)로 된 텍스트를 읽어와 출력하는 UI 클래스
//======================================

class UITextImageView : public UIObject
{
private:
	LPDIRECT3DTEXTURE9	m_pTexture;			// 텍스쳐
	POINT				m_textPos;			// 텍스트 이미지 파일의 위치를 계산하는 변수
	FONTFILE			m_fontFileType;		// 폰트 파일의 타입
public:
	UITextImageView();
	virtual ~UITextImageView();

	static int*			m_Select;				// 현재 텍스트의 위치

	SYNTHESIZE(std::string, m_sText, Text);		// 텍스트의 내용을 저장하는 변수
	SYNTHESIZE(D3DXVECTOR3, m_vecPos, VecPos);	// 텍스트의 위치
	SYNTHESIZE(int, m_index, Index);			// 현재 위치에서 텍스트의 위치

	virtual void Render(LPD3DXSPRITE pSprite) override;
	virtual void SetTexture(char* szFullPath);	// 텍스쳐 설정
};

