#pragma once

#include "UIObject.h"

#define CURSORRENDER 10

//======================================E
// - written by 김선호
// - 텍스트를 읽어와 이미지파일(png파일)를 출력하는 UI 클래스
//======================================

class UITextImageView : public UIObject
{
private:
	LPDIRECT3DTEXTURE9	m_pTexture;						// 텍스쳐
	POINT				m_textPos;						// 텍스트 이미지 파일의 위치를 계산하는 변수
	FONTFILE			m_fontFileType;					// 폰트 파일의 타입
	std::vector<std::string>	m_vecText;				// 버튼 누를 때 바뀌는 텍스트를 저장하기 위한 벡터 변수
	std::string m_chatText;								// 채팅 텍스트를 저장하기 위한 string변수

	int			m_cursorTime;							// 커서를 Update하는 변수
	bool		m_isCursorRender;						// 커서를 보이게 하는 변수

public:
	UITextImageView();
	virtual ~UITextImageView();

	static int*			m_Select;						// 현재 텍스트의 선택된 위치
	static int*			m_LeftAndRightSelect;			// 현재 오른쪽 왼쪽 선택된 위치

	SYNTHESIZE(std::string, m_sText, Text);				// 텍스트의 내용을 저장하는 변수
	SYNTHESIZE(int, m_index, Index);					// 현재 위치에서 텍스트의 위치
	SYNTHESIZE(D3DXCOLOR, m_color, Color);				// 텍스트 색상 변경
	SYNTHESIZE(float, m_xSize, XSize);					// X폰트 사이즈 설정
	SYNTHESIZE(float, m_ySize, YSize);					// Y폰트 사이즈 설정
	SYNTHESIZE(bool, m_isVectorText, IsVectorText);		// 벡터 텍스트로 사용 할 것인지 확인하는 작업
	SYNTHESIZE(bool, m_isVectorText2, IsVectorText2);	// 벡터 텍스트(위, 아래)로 사용 할 것인지 확인하는 작업
	SYNTHESIZE(bool, m_isChatingText, IsChatingText);	// 키 입력을 받을 것인지 확인하는 작업
	SYNTHESIZE(bool, m_isRealTime, IsRealTime);			// 실시간으로 그려줄 텍스트인지 확인
	SYNTHESIZE(int, m_carIndex, CarIndex);				// 자동차의 어떤 위치의 특성을 보여줄 변수 -> m_isRealTime이 true여야 한다. 


	/*   텍스트를 벡터로 사용할 때 쓰는 메서드   */
	void SetAddText(std::string text) { m_vecText.push_back(text); }

	void KeyEvent();

	/*   UI오브젝트에서 상속받은 클래스   */
	virtual void Update();
	virtual void Render(LPD3DXSPRITE pSprite) override;
	virtual void SetTexture(char* szFullPath);	// 텍스쳐 설정
	virtual void Destroy();

	std::string GetChatName() { return m_chatText; };
	void SetChatText(std::string) { m_chatText = ""; };
	std::string GetCarName();
};

