#pragma once
#include "UIObject.h"

class UIButton;
class iButtonDelegate
{
public:
	virtual void OnClick(UIButton* pSender) = 0;
};

class UIButton : public UIObject
{
public:
	UIButton();
	~UIButton();

	virtual void SetTexture(char* szNor, char* szOvr, char* szSel);
	virtual void Update();
	virtual void Render(LPD3DXSPRITE pSprite);

	void SetTexture(char* szNor, char* szOvr, char* szSel, std::string str);
	void SetText(std::string str);
protected:
	enum eButtonState
	{
		E_NORMAL,
		E_MOUSEOVER,
		E_SELECTED,
		E_STATE_MAX,
		E_STATE_CNT
	};

	eButtonState				m_eButtonState;
	LPDIRECT3DTEXTURE9	m_aTexture[E_STATE_CNT];
	ST_SIZE						m_stSize;

	SYNTHESIZE(iButtonDelegate*, m_pDelegate, Delegate);
};

