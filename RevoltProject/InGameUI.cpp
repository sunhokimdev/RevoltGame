#include "stdafx.h"
#include "InGameUI.h"
#include "UITextImageView.h"
#include "UIImageView.h"
#include "cCar.h"

#define TIMEMAX 60

InGameUI::InGameUI()
	: m_pLobby(NULL)
	, m_WorldDotOneth(0)
	, m_LastDotOneTh(48)
	, m_LastDotTenth(48)
	, m_LastDotMilth(48)
	, m_LastSecOneth(48)
	, m_LastSecTenth(48)
	, m_LastMinOneth(48)
	, m_LastMinTenth(48)
	, m_BestDotOneTh(48)
	, m_BestDotTenth(48)
	, m_BestDotMilth(48)
	, m_BestSecOneth(48)
	, m_BestSecTenth(48)
	, m_BestMinOneth(48)
	, m_BestMinTenth(48)
	, m_ElapseTime(0.0f)
	, m_DotTenth(48)
	, m_DotMilth(48)
	, m_SecOneth(48)
	, m_SecTenth(48)
	, m_MinOneth(47)
	, m_MinTenth(48)
	, m_LabElapseTime(0.0f)
	, m_LabDotTenth(48)
	, m_LabDotMilth(48)
	, m_LabSecOneth(48)
	, m_LabSecTenth(48)
	, m_LabMinOneth(47)
	, m_LabMinTenth(48)
	, m_select(99)
	, m_LabCnt(0)
{
}

InGameUI::~InGameUI()
{
	SAFE_DELETE(m_pRootUI);
	SAFE_DELETE(m_pItemImage);
	//SAFE_DELETE(m_pCar);
}

void InGameUI::Setup()
{
	m_pRootUI = new UIObject;
	UITextImageView::m_Select = &m_select;

	UITextImageView* pImageView1 = new UITextImageView;
	pImageView1->SetTexture("Maps/Front/Image/font2.png");
	pImageView1->SetText("Lab");
	pImageView1->SetXSize(1.0f);
	pImageView1->SetYSize(1.0f);
	pImageView1->SetPosition(30, 20);
	pImageView1->SetColor(D3DCOLOR_ARGB(255, 61, 183, 204));

	// Last Lab Timer
	UITextImageView* pLastLabFont = new UITextImageView;
	pLastLabFont->SetTexture("Maps/Front/Image/font2.png");
	pLastLabFont->SetText("Last Lap");
	pLastLabFont->SetXSize(1.0f);
	pLastLabFont->SetYSize(1.0f);
	pLastLabFont->SetPosition(900, 20);
	pLastLabFont->SetColor(D3DCOLOR_ARGB(255, 61, 183, 204));

	m_pLastDotOneTh = new UITextImageView;
	m_pLastDotOneTh->SetTexture("Maps/Front/Image/font2.png");
	m_pLastDotOneTh->SetPosition(55, 20);

	m_pLastDotTenth = new UITextImageView;
	m_pLastDotTenth->SetTexture("Maps/Front/Image/font2.png");
	m_pLastDotTenth->SetPosition(-10, 0);

	m_pLastDotMilth = new UITextImageView;
	m_pLastDotMilth->SetTexture("Maps/Front/Image/font2.png");
	m_pLastDotMilth->SetPosition(-10, 0);

	UITextImageView* pLastSecColon = new UITextImageView;
	pLastSecColon->SetTexture("Maps/Front/Image/font2.png");
	pLastSecColon->SetPosition(-10, 0);
	pLastSecColon->SetText(":");

	m_pLastSecOneth = new UITextImageView;
	m_pLastSecOneth->SetTexture("Maps/Front/Image/font2.png");
	m_pLastSecOneth->SetPosition(-10, 0);

	m_pLastSecTenth = new UITextImageView;
	m_pLastSecTenth->SetTexture("Maps/Front/Image/font2.png");
	m_pLastSecTenth->SetPosition(-10, 0);

	UITextImageView* pLastMinColon = new UITextImageView;
	pLastMinColon->SetTexture("Maps/Front/Image/font2.png");
	pLastMinColon->SetPosition(-10, 0);
	pLastMinColon->SetText(":");

	m_pLastMinOneth = new UITextImageView;
	m_pLastMinOneth->SetTexture("Maps/Front/Image/font2.png");
	m_pLastMinOneth->SetPosition(-10, 0);

	m_pLastMinTenth = new UITextImageView;
	m_pLastMinTenth->SetTexture("Maps/Front/Image/font2.png");
	m_pLastMinTenth->SetPosition(-10, 0);
	// << :

	// Best Lab Timer
	UITextImageView* pBestLabFont = new UITextImageView;
	pBestLabFont->SetTexture("Maps/Front/Image/font2.png");
	pBestLabFont->SetText("Best Lab");
	pBestLabFont->SetXSize(1.0f);
	pBestLabFont->SetYSize(1.0f);
	pBestLabFont->SetPosition(0, 50);
	pBestLabFont->SetColor(D3DCOLOR_ARGB(255, 61, 183, 204));

	m_pBestDotOneTh = new UITextImageView;
	m_pBestDotOneTh->SetTexture("Maps/Front/Image/font2.png");
	m_pBestDotOneTh->SetPosition(55, 20);

	m_pBestDotTenth = new UITextImageView;
	m_pBestDotTenth->SetTexture("Maps/Front/Image/font2.png");
	m_pBestDotTenth->SetPosition(-10, 0);

	m_pBestDotMilth = new UITextImageView;
	m_pBestDotMilth->SetTexture("Maps/Front/Image/font2.png");
	m_pBestDotMilth->SetPosition(-10, 0);

	UITextImageView* pBestSecColon = new UITextImageView;
	pBestSecColon->SetTexture("Maps/Front/Image/font2.png");
	pBestSecColon->SetPosition(-10, 0);
	pBestSecColon->SetText(":");

	m_pBestSecOneth = new UITextImageView;
	m_pBestSecOneth->SetTexture("Maps/Front/Image/font2.png");
	m_pBestSecOneth->SetPosition(-10, 0);

	m_pBestSecTenth = new UITextImageView;
	m_pBestSecTenth->SetTexture("Maps/Front/Image/font2.png");
	m_pBestSecTenth->SetPosition(-10, 0);

	UITextImageView* pBestMinColon = new UITextImageView;
	pBestMinColon->SetTexture("Maps/Front/Image/font2.png");
	pBestMinColon->SetPosition(-10, 0);
	pBestMinColon->SetText(":");

	m_pBestMinOneth = new UITextImageView;
	m_pBestMinOneth->SetTexture("Maps/Front/Image/font2.png");
	m_pBestMinOneth->SetPosition(-10, 0);

	m_pBestMinTenth = new UITextImageView;
	m_pBestMinTenth->SetTexture("Maps/Front/Image/font2.png");
	m_pBestMinTenth->SetPosition(-10, 0);
	// << :

	// Lab Timer
	UITextImageView* pLabFont = new UITextImageView;
	pLabFont->SetTexture("Maps/Front/Image/font2.png");
	pLabFont->SetText("Lab");
	pLabFont->SetXSize(1.0f);
	pLabFont->SetYSize(1.0f);
	pLabFont->SetPosition(39, 100);
	pLabFont->SetColor(D3DCOLOR_ARGB(255, 61, 183, 204));

	m_pLabElapseTime = new UITextImageView;
	m_pLabElapseTime->SetTexture("Maps/Front/Image/font2.png");
	m_pLabElapseTime->SetPosition(20, 20);

	m_pLabDotTenth = new UITextImageView;
	m_pLabDotTenth->SetTexture("Maps/Front/Image/font2.png");
	m_pLabDotTenth->SetPosition(-10, 0);

	m_pLabDotMilth = new UITextImageView;
	m_pLabDotMilth->SetTexture("Maps/Front/Image/font2.png");
	m_pLabDotMilth->SetPosition(-10, 0);

	UITextImageView* pLabSecColon = new UITextImageView;
	pLabSecColon->SetTexture("Maps/Front/Image/font2.png");
	pLabSecColon->SetPosition(-10, 0);
	pLabSecColon->SetText(":");

	m_pLabSecOneth = new UITextImageView;
	m_pLabSecOneth->SetTexture("Maps/Front/Image/font2.png");
	m_pLabSecOneth->SetPosition(-10, 0);

	m_pLabSecTenth = new UITextImageView;
	m_pLabSecTenth->SetTexture("Maps/Front/Image/font2.png");
	m_pLabSecTenth->SetPosition(-10, 0);

	UITextImageView* pLabMinColon = new UITextImageView;
	pLabMinColon->SetTexture("Maps/Front/Image/font2.png");
	pLabMinColon->SetPosition(-10, 0);
	pLabMinColon->SetText(":");

	m_pLabMinOneth = new UITextImageView;
	m_pLabMinOneth->SetTexture("Maps/Front/Image/font2.png");
	m_pLabMinOneth->SetPosition(-10, 0);

	m_pLabMinTenth = new UITextImageView;
	m_pLabMinTenth->SetTexture("Maps/Front/Image/font2.png");
	m_pLabMinTenth->SetPosition(-10, 0);
	// << :

	// Race Timer
	UITextImageView* pRaceFont = new UITextImageView;
	pRaceFont->SetTexture("Maps/Front/Image/font2.png");
	pRaceFont->SetText("Race");
	pRaceFont->SetXSize(1.0f);
	pRaceFont->SetYSize(1.0f);
	pRaceFont->SetPosition(32, 150);
	pRaceFont->SetColor(D3DCOLOR_ARGB(255, 61, 183, 204));

	m_pElapseTime = new UITextImageView;
	m_pElapseTime->SetTexture("Maps/Front/Image/font2.png");
	m_pElapseTime->SetPosition(25, 20);

	m_pDotTenth = new UITextImageView;
	m_pDotTenth->SetTexture("Maps/Front/Image/font2.png");
	m_pDotTenth->SetPosition(-10, 0);

	m_pDotMilth = new UITextImageView;
	m_pDotMilth->SetTexture("Maps/Front/Image/font2.png");
	m_pDotMilth->SetPosition(-10, 0);

	UITextImageView* pSecColon = new UITextImageView;
	pSecColon->SetTexture("Maps/Front/Image/font2.png");
	pSecColon->SetPosition(-10, 0);
	pSecColon->SetText(":");

	m_pSecOneth = new UITextImageView;
	m_pSecOneth->SetTexture("Maps/Front/Image/font2.png");
	m_pSecOneth->SetPosition(-10, 0);

	m_pSecTenth = new UITextImageView;
	m_pSecTenth->SetTexture("Maps/Front/Image/font2.png");
	m_pSecTenth->SetPosition(-10, 0);

	UITextImageView* pMinColon = new UITextImageView;
	pMinColon->SetTexture("Maps/Front/Image/font2.png");
	pMinColon->SetPosition(-10, 0);
	pMinColon->SetText(":");

	m_pMinOneth = new UITextImageView;
	m_pMinOneth->SetTexture("Maps/Front/Image/font2.png");
	m_pMinOneth->SetPosition(-10, 0);

	m_pMinTenth = new UITextImageView;
	m_pMinTenth->SetTexture("Maps/Front/Image/font2.png");
	m_pMinTenth->SetPosition(-10, 0);
	// << :

	UIImageView* pImageView6 = new UIImageView;
	pImageView6->SetXSize(1.2f);
	pImageView6->SetYSize(1.2f);
	pImageView6->SetPosition(-5, 50);
	pImageView6->SetTexture("Maps/Front/Image/itemframe.png");

	UIImageView* pImageView7 = new UIImageView;
	pImageView7->SetIsBoard(true);
	pImageView7->SetXSize(15.0f);
	pImageView7->SetYSize(2.5f);
	pImageView7->SetPosition(20, 600);
	pImageView7->SetTexture("Maps/Front/Image/ring.png");


	// 방향 화살표
	pIV_arrowDir = new UIImageView;
	pIV_arrowDir->SetXSize(1.2f);
	pIV_arrowDir->SetYSize(1.2f);
	pIV_arrowDir->SetPosition(125, -80);
	pIV_arrowDir->SetTexture("UIImage/arrowDirection.png");

	// 등수
	UITextImageView* pITV_Rank = new UITextImageView;
	pITV_Rank->SetXSize(4.0f);
	pITV_Rank->SetYSize(4.0f);
	pITV_Rank->SetPosition(20, -70);
	pITV_Rank->SetText("8");
	pITV_Rank->SetTexture("Maps/Front/Image/font2.png");

	UITextImageView* pITV_Rank2 = new UITextImageView;
	pITV_Rank2->SetXSize(1.2f);
	pITV_Rank2->SetYSize(1.2f);
	pITV_Rank2->SetPosition(55, -65);
	pITV_Rank2->SetText("th");
	pITV_Rank2->SetTexture("Maps/Front/Image/font2.png");
	pITV_Rank2->SetColor(D3DCOLOR_ARGB(255, 61, 183, 204));

	m_pItemImage = new UIImageView;
	m_pItemImage->SetXSize(1.2f);
	m_pItemImage->SetYSize(1.2f);
	m_pItemImage->SetPosition(22, 22);
	m_pItemImage->SetIsItem(true);
	m_pItemImage->SetTexture("Maps/Front/Image/itemlist.png");

	// 속도계 추가

	UIImageView* pSpeedFrame = new UIImageView;
	pSpeedFrame->SetIsSpeedFrame(true);
	pSpeedFrame->SetXSize(1.2f);
	pSpeedFrame->SetYSize(1.2f);
	pSpeedFrame->SetPosition(750, 650);
	pSpeedFrame->SetTexture("UIImage/speedFrame.png");

	pSpeedometerImage = new UIImageView;
	pSpeedometerImage->SetIsSpeed(true);
	pSpeedometerImage->SetXSize(1.2f);
	pSpeedometerImage->SetYSize(1.2f);
	pSpeedometerImage->SetPosition(0, 0);
	pSpeedometerImage->SetTexture("UIImage/speed.png");

	pSpeed = new UITextImageView;			// 10의 자리
	pSpeed->SetTexture("Maps/Front/Image/font2.png");
	pSpeed->SetText("");
	pSpeed->SetXSize(1.2f);
	pSpeed->SetYSize(1.2f);
	pSpeed->SetPosition(140, 8);

	pSpeed2 = new UITextImageView;			// 1의 자리
	pSpeed2->SetTexture("Maps/Front/Image/font2.png");
	pSpeed2->SetText("0");
	pSpeed2->SetXSize(1.2f);
	pSpeed2->SetYSize(1.2f);
	pSpeed2->SetPosition(10, 0);

	UITextImageView* pSpeed_mph = new UITextImageView;
	pSpeed_mph->SetTexture("Maps/Front/Image/font2.png");
	pSpeed_mph->SetText("mph");
	pSpeed_mph->SetXSize(1.2f);
	pSpeed_mph->SetYSize(1.2f);
	pSpeed_mph->SetPosition(170, 8);
	pSpeed_mph->SetColor(D3DCOLOR_ARGB(255, 61, 183, 204));

	/*          Set Child          */

	// Basic
	m_pRootUI->AddChild(pImageView1);
	m_pRootUI->AddChild(pLastLabFont);
	m_pRootUI->AddChild(pImageView7);
	m_pRootUI->AddChild(pSpeedFrame);
	pImageView1->AddChild(pImageView6);
	pLastLabFont->AddChild(pBestLabFont);
	pLastLabFont->AddChild(pLabFont);
	pLastLabFont->AddChild(pRaceFont);
	pImageView6->AddChild(m_pItemImage);

	pImageView7->AddChild(pIV_arrowDir);
	pImageView7->AddChild(pITV_Rank);
	pImageView7->AddChild(pITV_Rank2);

	pSpeedFrame->AddChild(pSpeedometerImage);
	pSpeedFrame->AddChild(pSpeed);
	pSpeedFrame->AddChild(pSpeed_mph);
	pSpeed->AddChild(pSpeed2);


	// Last Font
	pLastLabFont->AddChild(m_pLastDotOneTh);
	m_pLastDotOneTh->AddChild(m_pLastDotTenth);
	m_pLastDotTenth->AddChild(m_pLastDotMilth);
	m_pLastDotMilth->AddChild(pLastSecColon);
	pLastSecColon->AddChild(m_pLastSecOneth);
	m_pLastSecOneth->AddChild(m_pLastSecTenth);
	m_pLastSecTenth->AddChild(pLastMinColon);
	pLastMinColon->AddChild(m_pLastMinOneth);
	m_pLastMinOneth->AddChild(m_pLastMinTenth);

	// Best Font
	pBestLabFont->AddChild(m_pBestDotOneTh);
	m_pBestDotOneTh->AddChild(m_pBestDotTenth);
	m_pBestDotTenth->AddChild(m_pBestDotMilth);
	m_pBestDotMilth->AddChild(pBestSecColon);
	pBestSecColon->AddChild(m_pBestSecOneth);
	m_pBestSecOneth->AddChild(m_pBestSecTenth);
	m_pBestSecTenth->AddChild(pBestMinColon);
	pBestMinColon->AddChild(m_pBestMinOneth);
	m_pBestMinOneth->AddChild(m_pBestMinTenth);

	// LabFont
	pLabFont->AddChild(m_pLabElapseTime);
	m_pLabElapseTime->AddChild(m_pLabDotTenth);
	m_pLabDotTenth->AddChild(m_pLabDotMilth);
	m_pLabDotMilth->AddChild(pLabSecColon);
	pLabSecColon->AddChild(m_pLabSecOneth);
	m_pLabSecOneth->AddChild(m_pLabSecTenth);
	m_pLabSecTenth->AddChild(pLabMinColon);
	pLabMinColon->AddChild(m_pLabMinOneth);
	m_pLabMinOneth->AddChild(m_pLabMinTenth);

	// RaceFont
	pRaceFont->AddChild(m_pElapseTime);
	m_pElapseTime->AddChild(m_pDotTenth);
	m_pDotTenth->AddChild(m_pDotMilth);
	m_pDotMilth->AddChild(pSecColon);
	pSecColon->AddChild(m_pSecOneth);
	m_pSecOneth->AddChild(m_pSecTenth);
	m_pSecTenth->AddChild(pMinColon);
	pMinColon->AddChild(m_pMinOneth);
	m_pMinOneth->AddChild(m_pMinTenth);

}

void InGameUI::Update()
{
	UpdateSpeed();

	if (g_pKeyManager->isOnceKeyDown('Z'))
	{
		UpdateLastTime();
	}
	if (g_pKeyManager->isOnceKeyDown('X'))
	{
		if (m_LabCnt == 0) m_LabCnt = 1;
		else m_LabCnt = 0;
	}


	UpdateRaceTime();
	UpdateLabTime();

	iLobby::Update();

	//UpdateArrowDir();
}

void InGameUI::Render(LPD3DXSPRITE pSprite)
{
	iLobby::Render(pSprite);


}

void InGameUI::UpdateSpeed()
{
	int fTemp;
	fTemp = m_pCar->GetCurrentSpeed();
	int nTen;
	int nOne;

	nTen = (int)fTemp / 10 + FONT2_NUM0;
	nOne = (int)(fTemp % 10) + FONT2_NUM0;

	std::string strTen;
	std::string strOne;

	strTen = nTen;
	strOne = nOne;


	pSpeed->SetText(strTen);
	pSpeed2->SetText(strOne);
	pSpeedometerImage->SetRpmGauge(m_pCar->GetNxVehicle()->getWheel(1)->getRpm());
}
void InGameUI::CompareBestTime()
{
}

void InGameUI::UpdateLastTime()
{
	// Add String For UITextImage Text
	std::string LastDotOneth;								//		 x.xx0
	std::string LastDotTenth;								//		 x.x0x
	std::string LastDotMilth;								//		 x.0xx

	std::string LastSecOneth;								//		 0.xxx
	std::string LastSecTenth;								//		0x.xxx

	std::string LastMinOneth;								//	  0.xx.xxx
	std::string LastMinTenth;								//	 0x.xx.xxx

	if (m_LabCnt != 0)
	{
		m_LastDotOneTh = m_WorldDotOneth;
		m_LastDotTenth = m_LabDotTenth;
		m_LastDotMilth = m_LabDotMilth;
		m_LastSecOneth = m_LabSecOneth;
		m_LastSecTenth = m_LabSecTenth;
		m_LastMinOneth = m_LabMinOneth;
		m_LastMinTenth = m_LabMinTenth;

		LastDotOneth = m_LastDotOneTh;
		LastDotTenth = m_LastDotTenth;
		LastDotMilth = m_LastDotMilth;
		LastSecOneth = m_LastSecOneth;
		LastSecTenth = m_LastSecTenth;
		LastMinOneth = m_LastMinOneth;
		LastMinTenth = m_LastMinTenth;
	}
	else
	{
		LastDotOneth = FONT2_NUM0;
		LastDotTenth = FONT2_NUM0;
		LastDotMilth = FONT2_NUM0;
		LastSecOneth = FONT2_NUM0;
		LastSecTenth = FONT2_NUM0;
		LastMinOneth = FONT2_NUM0;
		LastMinTenth = FONT2_NUM0;
	}


	m_pLastDotOneTh->SetText(LastDotOneth);
	m_pLastDotTenth->SetText(LastDotTenth);
	m_pLastDotMilth->SetText(LastDotMilth);
	m_pLastSecOneth->SetText(LastSecOneth);
	m_pLastSecTenth->SetText(LastSecTenth);
	m_pLastMinOneth->SetText(LastMinOneth);
	m_pLastMinTenth->SetText(LastMinTenth);
}

void InGameUI::UpdateRaceTime()
{
	// Add String For UITextImage Text
	std::string ElapseTime;								// Elase(x.xx0)
	std::string DotTenth;								//		 x.x0x
	std::string DotMilth;								//		 x.0xx

	std::string SecOneth;								//		 0.xxx
	std::string SecTenth;								//		0x.xxx

	std::string MinOneth;								//	  0.xx.xxx
	std::string MinTenth;								//	 0x.xx.xxx


	m_ElapseTime += g_pTimeManager->GetElapsedTime();	// Uptate ElapsedTime

	if (m_ElapseTime > TIMEMAX)							// After 60 Second
	{
		m_ElapseTime = 0;								// ElapsedTime = 0
		m_MinOneth += 1;								// Add 1 Minute
	}
	if (m_MinOneth > FONT2_NUM9)						// After 10 Minute
	{
		m_MinOneth = FONT2_NUM0;						// MinuteOneth = 0; 
		m_MinTenth += 1;								// Add MinuteTenth ( 09:59 -> 10:00 )
	}
	if (m_MinTenth > FONT2_NUM9)
	{
		m_MinTenth = FONT2_NUM0;
	}
	m_SecTenth = (m_ElapseTime / 10) + FONT2_NUM0;		// Ex : m_ElapseTime = 59
	m_SecOneth = ((int)m_ElapseTime % 10) + FONT2_NUM0; //      m_ElapseTime / 10 = 5;	
														//      m_ElapseTime % 10 = 9;
														//      Therefore Current Second : 59


																//		EX : m_ElapseTime = 9.876
	float CalcDP = (m_ElapseTime - (int)m_ElapseTime) * 10.0f;	//		CalcDP = (9.876 - 9) * 10 = 8.76
	DotMilth = (int)(CalcDP)+FONT2_NUM0;						//		x.?xx = x.8xx
	CalcDP -= (int)CalcDP;										//		CalcDP = 8.76 - 8 = 0.76
	CalcDP *= 10.0f;											//		CalcDP = 0.76 * 10 = 7.6
	DotTenth = (int)CalcDP + FONT2_NUM0;						//		x.8?x = x.87x
	CalcDP -= (int)CalcDP;										//		CalcDP = 7.6 - 7 = 0.6
	CalcDP *= 10.0f;											//		CalcDP = 0.6 * 10 = 6
	ElapseTime = (int)CalcDP + FONT2_NUM0;						//		x.87? = x.876
	m_WorldDotOneth = (int)CalcDP + FONT2_NUM0;;								//		Therefore Calculation Decimal Point = 0.876

	/*          Add String          */
	SecOneth = m_SecOneth;
	SecTenth = m_SecTenth;

	MinOneth = m_MinOneth;
	MinTenth = m_MinTenth;



	/*          Set Text          */
	m_pElapseTime->SetText(ElapseTime);
	m_pDotTenth->SetText(DotTenth);
	m_pDotMilth->SetText(DotMilth);
	m_pSecOneth->SetText(SecOneth);
	m_pSecTenth->SetText(SecTenth);
	m_pMinOneth->SetText(MinOneth);
	m_pMinTenth->SetText(MinTenth);
}

void InGameUI::UpdateLabTime()
{
	// Add String For UITextImage Text
	std::string LabElapseTime;										// Elase(x.xx0)
	std::string LabDotTenth;										//		 x.x0x
	std::string LabDotMilth;										//		 x.0xx

	std::string LabSecOneth;										//		 0.xxx
	std::string LabSecTenth;										//		0x.xxx

	std::string LabMinOneth;										//	  0.xx.xxx
	std::string LabMinTenth;										//	 0x.xx.xxx

	//if (m_LabCnt == -1)	m_LabElapseTime = 0;
	//else if (m_LabCnt == 0)	m_LabElapseTime += g_pTimeManager->GetElapsedTime();			// Uptate ElapsedTime
	m_LabElapseTime += g_pTimeManager->GetElapsedTime();

	if (g_pKeyManager->isOnceKeyDown('B'))
	{
		//if (m_LabCnt == -1) m_LabCnt += 1;
		//else m_LabCnt -= 1;

		m_LabElapseTime = 0;
	}

	if (m_LabElapseTime > TIMEMAX)									// After 60 Second
	{
		m_LabElapseTime = 0;										// ElapsedTime = 0
		m_LabMinOneth += 1;											// Add 1 Minute
	}
	if (m_LabMinOneth > FONT2_NUM9)									// After 10 Minute
	{
		m_LabMinOneth = FONT2_NUM0;									// MinuteOneth = 0; 
		m_LabMinTenth += 1;											// Add MinuteTenth ( 09:59 -> 10:00 )
	}
	if (m_LabMinTenth > FONT2_NUM9)
	{
		m_LabMinTenth = FONT2_NUM0;
	}
	m_LabSecTenth = (m_LabElapseTime / 10) + FONT2_NUM0;			// Ex : m_ElapseTime = 59
	m_LabSecOneth = ((int)m_LabElapseTime % 10) + FONT2_NUM0;		//      m_ElapseTime / 10 = 5;	
																	//      m_ElapseTime % 10 = 9;
																	//      Therefore Current Second : 59


																		//		EX : m_ElapseTime = 9.876
	float CalcDP = (m_LabElapseTime - (int)m_LabElapseTime) * 10.0f;	//		CalcDP = (9.876 - 9) * 10 = 8.76
	m_LabDotTenth = (int)(CalcDP)+FONT2_NUM0;								//		x.?xx = x.8xx
	CalcDP -= (int)CalcDP;												//		CalcDP = 8.76 - 8 = 0.76
	CalcDP *= 10.0f;													//		CalcDP = 0.76 * 10 = 7.6
	m_LabDotMilth = (int)CalcDP + FONT2_NUM0;								//		x.8?x = x.87x
	CalcDP -= (int)CalcDP;												//		CalcDP = 7.6 - 7 = 0.6
	CalcDP *= 10.0f;													//		CalcDP = 0.6 * 10 = 6
	LabElapseTime = (int)CalcDP + FONT2_NUM0;							//		x.87? = x.876
																		//		Therefore Calculation Decimal Point = 0.876

	/*          Add String          */
	LabDotTenth = m_LabDotTenth;
	LabDotMilth = m_LabDotMilth;

	LabSecOneth = m_LabSecOneth;
	LabSecTenth = m_LabSecTenth;

	LabMinOneth = m_LabMinOneth;
	LabMinTenth = m_LabMinTenth;



	/*          Set Text          */
	m_pLabElapseTime->SetText(LabElapseTime);
	m_pLabDotTenth->SetText(LabDotTenth);
	m_pLabDotMilth->SetText(LabDotMilth);
	m_pLabSecOneth->SetText(LabSecOneth);
	m_pLabSecTenth->SetText(LabSecTenth);
	m_pLabMinOneth->SetText(LabMinOneth);
	m_pLabMinTenth->SetText(LabMinTenth);
}
void InGameUI::UpdateArrowDir()
{

}
