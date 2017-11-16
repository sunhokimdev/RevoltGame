#include "stdafx.h"
#include "InGameUI.h"
#include "UITextImageView.h"
#include "UIImageView.h"
#include "cCar.h"
#include "cTrack.h"
#include "Object.h"
#include "cCheckBox.h"
#include "c321GO.h"
#include "RacingScene.h"

#define TIMEMAX 60

InGameUI::InGameUI()
	: m_pLobby(NULL)
	, m_WorldDotOneth(0)
	, m_LastDotOneTh(FONT2_NUM0)
	, m_LastDotTenth(FONT2_NUM0)
	, m_LastDotMilth(FONT2_NUM0)
	, m_LastSecOneth(FONT2_NUM0)
	, m_LastSecTenth(FONT2_NUM0)
	, m_LastMinOneth(FONT2_NUM0)
	, m_LastMinTenth(FONT2_NUM0)
	, m_BestDotOneTh(FONT2_NUM0)
	, m_BestDotTenth(FONT2_NUM0)
	, m_BestDotMilth(FONT2_NUM0)
	, m_BestSecOneth(FONT2_NUM0)
	, m_BestSecTenth(FONT2_NUM0)
	, m_BestMinOneth(FONT2_NUM5)
	, m_BestMinTenth(FONT2_NUM0)
	, m_ElapseTime(0.0f)
	, m_DotTenth(FONT2_NUM0)
	, m_DotMilth(FONT2_NUM0)
	, m_SecOneth(FONT2_NUM0)
	, m_SecTenth(FONT2_NUM0)
	, m_MinOneth(FONT2_NUM0)
	, m_MinTenth(FONT2_NUM0)
	, m_LabElapseTime(0.0f)
	, m_LabDotTenth(FONT2_NUM0)
	, m_LabDotMilth(FONT2_NUM0)
	, m_LabSecOneth(FONT2_NUM0)
	, m_LabSecTenth(FONT2_NUM0)
	, m_LabMinOneth(FONT2_NUM0)
	, m_LabMinTenth(FONT2_NUM0)
	, m_select(99)
	, m_LabCnt(-1)
	, m_arrowIndex(0)
{
}

InGameUI::~InGameUI()
{

}

void InGameUI::Setup()
{
	m_pRootUI = new UIObject;
	UITextImageView::m_Select = &m_select;


	//Lab
	UITextImageView* pLabCntFont = new UITextImageView;
	pLabCntFont->SetTexture("UIImage/font2.png");
	pLabCntFont->SetText("Lab");
	pLabCntFont->SetXSize(1.0f);
	pLabCntFont->SetYSize(1.0f);
	pLabCntFont->SetPosition(30, 20);
	pLabCntFont->SetColor(D3DCOLOR_ARGB(255, 61, 183, 204));

	m_pCurrentLab = new UITextImageView;
	m_pCurrentLab->SetTexture("UIImage/font2.png");
	m_pCurrentLab->SetPosition(0, 20);


	m_pMaxLab = new UITextImageView;
	m_pMaxLab->SetTexture("UIImage/font2.png");
	m_pMaxLab->SetPosition(10, 0);
	m_pMaxLab->SetText("/3");

	// Last Lab Timer
	UITextImageView* pLastLabFont = new UITextImageView;
	pLastLabFont->SetTexture("UIImage/font2.png");
	pLastLabFont->SetText("Last Lap");
	pLastLabFont->SetXSize(1.0f);
	pLastLabFont->SetYSize(1.0f);
	pLastLabFont->SetPosition(900, 20);
	pLastLabFont->SetColor(D3DCOLOR_ARGB(255, 61, 183, 204));

	m_pLastDotOneTh = new UITextImageView;
	m_pLastDotOneTh->SetTexture("UIImage/font2.png");
	m_pLastDotOneTh->SetPosition(60, 20);
	m_pLastDotOneTh->SetText("0");

	m_pLastDotTenth = new UITextImageView;
	m_pLastDotTenth->SetTexture("UIImage/font2.png");
	m_pLastDotTenth->SetPosition(-10, 0);
	m_pLastDotTenth->SetText("0");

	m_pLastDotMilth = new UITextImageView;
	m_pLastDotMilth->SetTexture("UIImage/font2.png");
	m_pLastDotMilth->SetPosition(-10, 0);
	m_pLastDotMilth->SetText("0");

	UITextImageView* pLastSecColon = new UITextImageView;
	pLastSecColon->SetTexture("UIImage/font2.png");
	pLastSecColon->SetPosition(-10, 0);
	pLastSecColon->SetText(":");

	m_pLastSecOneth = new UITextImageView;
	m_pLastSecOneth->SetTexture("UIImage/font2.png");
	m_pLastSecOneth->SetPosition(-10, 0);
	m_pLastSecOneth->SetText("0");

	m_pLastSecTenth = new UITextImageView;
	m_pLastSecTenth->SetTexture("UIImage/font2.png");
	m_pLastSecTenth->SetPosition(-10, 0);
	m_pLastSecTenth->SetText("0");

	UITextImageView* pLastMinColon = new UITextImageView;
	pLastMinColon->SetTexture("UIImage/font2.png");
	pLastMinColon->SetPosition(-10, 0);
	pLastMinColon->SetText(":");


	m_pLastMinOneth = new UITextImageView;
	m_pLastMinOneth->SetTexture("UIImage/font2.png");
	m_pLastMinOneth->SetPosition(-10, 0);
	m_pLastMinOneth->SetText("0");

	m_pLastMinTenth = new UITextImageView;
	m_pLastMinTenth->SetTexture("UIImage/font2.png");
	m_pLastMinTenth->SetPosition(-10, 0);
	m_pLastMinTenth->SetText("0");
	// << :

	// Best Lab Timer
	UITextImageView* pBestLabFont = new UITextImageView;
	pBestLabFont->SetTexture("UIImage/font2.png");
	pBestLabFont->SetText("Best Lab");
	pBestLabFont->SetXSize(1.0f);
	pBestLabFont->SetYSize(1.0f);
	pBestLabFont->SetPosition(0, 50);
	pBestLabFont->SetColor(D3DCOLOR_ARGB(255, 61, 183, 204));

	m_pBestDotOneTh = new UITextImageView;
	m_pBestDotOneTh->SetTexture("UIImage/font2.png");
	m_pBestDotOneTh->SetPosition(60, 20);
	m_pBestDotOneTh->SetText("0");

	m_pBestDotTenth = new UITextImageView;
	m_pBestDotTenth->SetTexture("UIImage/font2.png");
	m_pBestDotTenth->SetPosition(-10, 0);
	m_pBestDotTenth->SetText("0");

	m_pBestDotMilth = new UITextImageView;
	m_pBestDotMilth->SetTexture("UIImage/font2.png");
	m_pBestDotMilth->SetPosition(-10, 0);
	m_pBestDotMilth->SetText("0");


	UITextImageView* pBestSecColon = new UITextImageView;
	pBestSecColon->SetTexture("UIImage/font2.png");
	pBestSecColon->SetPosition(-10, 0);
	pBestSecColon->SetText(":");

	m_pBestSecOneth = new UITextImageView;
	m_pBestSecOneth->SetTexture("UIImage/font2.png");
	m_pBestSecOneth->SetPosition(-10, 0);
	m_pBestSecOneth->SetText("0");

	m_pBestSecTenth = new UITextImageView;
	m_pBestSecTenth->SetTexture("UIImage/font2.png");
	m_pBestSecTenth->SetPosition(-10, 0);
	m_pBestSecTenth->SetText("0");

	UITextImageView* pBestMinColon = new UITextImageView;
	pBestMinColon->SetTexture("UIImage/font2.png");
	pBestMinColon->SetPosition(-10, 0);
	pBestMinColon->SetText(":");

	m_pBestMinOneth = new UITextImageView;
	m_pBestMinOneth->SetTexture("UIImage/font2.png");
	m_pBestMinOneth->SetPosition(-10, 0);
	m_pBestMinOneth->SetText("5");

	m_pBestMinTenth = new UITextImageView;
	m_pBestMinTenth->SetTexture("UIImage/font2.png");
	m_pBestMinTenth->SetPosition(-10, 0);
	m_pBestMinTenth->SetText("0");
	// << :

	// Lab Timer
	UITextImageView* pLabFont = new UITextImageView;
	pLabFont->SetTexture("UIImage/font2.png");
	pLabFont->SetText("Lab");
	pLabFont->SetXSize(1.0f);
	pLabFont->SetYSize(1.0f);
	pLabFont->SetPosition(39, 100);
	pLabFont->SetColor(D3DCOLOR_ARGB(255, 61, 183, 204));

	m_pLabElapseTime = new UITextImageView;
	m_pLabElapseTime->SetTexture("UIImage/font2.png");
	m_pLabElapseTime->SetPosition(20, 20);
	m_pLabElapseTime->SetText("0");

	m_pLabDotTenth = new UITextImageView;
	m_pLabDotTenth->SetTexture("UIImage/font2.png");
	m_pLabDotTenth->SetPosition(-10, 0);
	m_pLabDotTenth->SetText("0");

	m_pLabDotMilth = new UITextImageView;
	m_pLabDotMilth->SetTexture("UIImage/font2.png");
	m_pLabDotMilth->SetPosition(-10, 0);
	m_pLabDotMilth->SetText("0");

	UITextImageView* pLabSecColon = new UITextImageView;
	pLabSecColon->SetTexture("UIImage/font2.png");
	pLabSecColon->SetPosition(-10, 0);
	pLabSecColon->SetText(":");

	m_pLabSecOneth = new UITextImageView;
	m_pLabSecOneth->SetTexture("UIImage/font2.png");
	m_pLabSecOneth->SetPosition(-10, 0);
	m_pLabSecOneth->SetText("0");

	m_pLabSecTenth = new UITextImageView;
	m_pLabSecTenth->SetTexture("UIImage/font2.png");
	m_pLabSecTenth->SetPosition(-10, 0);
	m_pLabSecTenth->SetText("0");

	UITextImageView* pLabMinColon = new UITextImageView;
	pLabMinColon->SetTexture("UIImage/font2.png");
	pLabMinColon->SetPosition(-10, 0);
	pLabMinColon->SetText(":");

	m_pLabMinOneth = new UITextImageView;
	m_pLabMinOneth->SetTexture("UIImage/font2.png");
	m_pLabMinOneth->SetPosition(-10, 0);
	m_pLabMinOneth->SetText("0");

	m_pLabMinTenth = new UITextImageView;
	m_pLabMinTenth->SetTexture("UIImage/font2.png");
	m_pLabMinTenth->SetPosition(-10, 0);
	m_pLabMinTenth->SetText("0");
	// << :

	// Race Timer
	UITextImageView* pRaceFont = new UITextImageView;
	pRaceFont->SetTexture("UIImage/font2.png");
	pRaceFont->SetText("Race");
	pRaceFont->SetXSize(1.0f);
	pRaceFont->SetYSize(1.0f);
	pRaceFont->SetPosition(32, 150);
	pRaceFont->SetColor(D3DCOLOR_ARGB(255, 61, 183, 204));

	m_pElapseTime = new UITextImageView;
	m_pElapseTime->SetTexture("UIImage/font2.png");
	m_pElapseTime->SetPosition(25, 20);
	m_pElapseTime->SetText("0");

	m_pDotTenth = new UITextImageView;
	m_pDotTenth->SetTexture("UIImage/font2.png");
	m_pDotTenth->SetPosition(-10, 0);
	m_pDotTenth->SetText("0");

	m_pDotMilth = new UITextImageView;
	m_pDotMilth->SetTexture("UIImage/font2.png");
	m_pDotMilth->SetPosition(-10, 0);
	m_pDotMilth->SetText("0");

	UITextImageView* pSecColon = new UITextImageView;
	pSecColon->SetTexture("UIImage/font2.png");
	pSecColon->SetPosition(-10, 0);
	pSecColon->SetText(":");

	m_pSecOneth = new UITextImageView;
	m_pSecOneth->SetTexture("UIImage/font2.png");
	m_pSecOneth->SetPosition(-10, 0);
	m_pSecOneth->SetText("0");

	m_pSecTenth = new UITextImageView;
	m_pSecTenth->SetTexture("UIImage/font2.png");
	m_pSecTenth->SetPosition(-10, 0);
	m_pSecTenth->SetText("0");

	UITextImageView* pMinColon = new UITextImageView;
	pMinColon->SetTexture("UIImage/font2.png");
	pMinColon->SetPosition(-10, 0);
	pMinColon->SetText(":");

	m_pMinOneth = new UITextImageView;
	m_pMinOneth->SetTexture("UIImage/font2.png");
	m_pMinOneth->SetPosition(-10, 0);
	m_pMinOneth->SetText("0");

	m_pMinTenth = new UITextImageView;
	m_pMinTenth->SetTexture("UIImage/font2.png");
	m_pMinTenth->SetPosition(-10, 0);
	m_pMinTenth->SetText("0");
	// << :

	UIImageView* pImageView6 = new UIImageView;
	pImageView6->SetXSize(1.2f);
	pImageView6->SetYSize(1.2f);
	pImageView6->SetPosition(-5, 50);
	pImageView6->SetTexture("UIImage/itemframe.png");

	UIImageView* pImageView7 = new UIImageView;
	pImageView7->SetIsBoard(true);
	pImageView7->SetXSize(15.0f);
	pImageView7->SetYSize(2.5f);
	pImageView7->SetPosition(20, 600);
	pImageView7->SetTexture("UIImage/ring.png");


	//방향 화살표
	pIV_arrowDir = new UIImageView;
	pIV_arrowDir->SetIsArrowDir(true);
	pIV_arrowDir->SetXSize(1.2f);
	pIV_arrowDir->SetYSize(1.2f);
	pIV_arrowDir->SetPosition(150, 550);
	pIV_arrowDir->SetTexture("UIImage/arrowDirection.png");

	//등수
	pITV_Rank = new UITextImageView;
	pITV_Rank->SetXSize(3.0f);
	pITV_Rank->SetYSize(3.0f);
	pITV_Rank->SetPosition(25, -50);
	pITV_Rank->SetText("8");
	pITV_Rank->SetTexture("UIImage/font2.png");

	pITV_Rank2 = new UITextImageView;
	pITV_Rank2->SetXSize(1.0f);
	pITV_Rank2->SetYSize(1.0f);
	pITV_Rank2->SetPosition(55, -45);
	pITV_Rank2->SetText("th");
	pITV_Rank2->SetTexture("UIImage/font2.png");
	pITV_Rank2->SetColor(D3DCOLOR_ARGB(255, 61, 183, 204));

	m_pItemImage = new UIImageView;
	m_pItemImage->SetXSize(1.2f);
	m_pItemImage->SetYSize(1.2f);
	m_pItemImage->SetPosition(22, 22);
	m_pItemImage->SetIsItem(true);
	m_pItemImage->SetTexture("UIImage/itemlist.png");
	m_pItemImage->LinkCarPt(m_pCar);

	//속도계 추가

	UIImageView* pSpeedFrame = new UIImageView;
	pSpeedFrame->SetIsSpeedFrame(true);
	pSpeedFrame->SetXSize(1.2f);
	pSpeedFrame->SetYSize(1.2f);
	pSpeedFrame->SetPosition(750, 650);
	pSpeedFrame->SetTexture("UIImage/speedFrame.png");

	m_pSpeedometerImage = new UIImageView;
	m_pSpeedometerImage->SetIsSpeed(true);
	m_pSpeedometerImage->SetXSize(1.2f);
	m_pSpeedometerImage->SetYSize(1.2f);
	m_pSpeedometerImage->SetPosition(0, 0);
	m_pSpeedometerImage->SetTexture("UIImage/speed.png");

	m_pSpeedOne = new UITextImageView;			// 1의 자리
	m_pSpeedOne->SetTexture("UIImage/font2.png");
	m_pSpeedOne->SetText("0");
	m_pSpeedOne->SetXSize(1.2f);
	m_pSpeedOne->SetYSize(1.2f);
	m_pSpeedOne->SetPosition(150, 0);

	m_pSpeedTen = new UITextImageView;			// 10의 자리
	m_pSpeedTen->SetTexture("UIImage/font2.png");
	m_pSpeedTen->SetText("");
	m_pSpeedTen->SetXSize(1.2f);
	m_pSpeedTen->SetYSize(1.2f);
	m_pSpeedTen->SetPosition(-10, 0);

	m_pSpeedHun = new UITextImageView;			// 100의 자리
	m_pSpeedHun->SetTexture("UIImage/font2.png");
	m_pSpeedHun->SetText("");
	m_pSpeedHun->SetXSize(1.2f);
	m_pSpeedHun->SetYSize(1.2f);
	m_pSpeedHun->SetPosition(-10, 0);

	UITextImageView* pSpeed_mph = new UITextImageView;
	pSpeed_mph->SetTexture("UIImage/font2.png");
	pSpeed_mph->SetText("mph");
	pSpeed_mph->SetXSize(1.2f);
	pSpeed_mph->SetYSize(1.2f);
	pSpeed_mph->SetPosition(170, 8);
	pSpeed_mph->SetColor(D3DCOLOR_ARGB(255, 61, 183, 204));


	//Result
	m_pResultRing = new UIImageView;
	m_pResultRing->SetIsBoard(true);
	m_pResultRing->SetXSize(15.0f);
	m_pResultRing->SetYSize(12.5f);
	m_pResultRing->SetPosition(400, 200);

	m_pRaceResult = new UITextImageView;
	m_pRaceResult->SetTexture("UIImage/font2.png");
	m_pRaceResult->SetXSize(1.0f);
	m_pRaceResult->SetYSize(1.0f);
	m_pRaceResult->SetPosition(10, 10);
	m_pRaceResult->SetColor(D3DCOLOR_ARGB(255, 61, 183, 204));

	// First
	m_pFirst = new UITextImageView;
	m_pFirst->SetTexture("UIImage/font2.png");
	m_pFirst->SetXSize(1.0f);
	m_pFirst->SetYSize(1.0f);
	m_pFirst->SetPosition(0, 30);
	m_pFirstPlayerName = new UITextImageView;
	m_pFirstPlayerName->SetTexture("UIImage/font2.png");
	m_pFirstPlayerName->SetPosition(30, 0);
	m_pFirstPlayerName->SetColor(D3DCOLOR_ARGB(255, 61, 183, 204));
	m_pFirstResultMinTenth = new UITextImageView;
	m_pFirstResultMinTenth->SetTexture("UIImage/font2.png");
	m_pFirstResultMinTenth->SetPosition(160, 0);
	m_pFirstResultMinOneth = new UITextImageView;
	m_pFirstResultMinOneth->SetTexture("UIImage/font2.png");
	m_pFirstResultMinOneth->SetPosition(10, 0);
	m_pFirstResultMinColon = new UITextImageView;
	m_pFirstResultMinColon->SetTexture("UIImage/font2.png");
	m_pFirstResultMinColon->SetPosition(10, 0);
	m_pFirstResultSecTenth = new UITextImageView;
	m_pFirstResultSecTenth->SetTexture("UIImage/font2.png");
	m_pFirstResultSecTenth->SetPosition(10, 0);
	m_pFirstResultSecOneth = new UITextImageView;
	m_pFirstResultSecOneth->SetTexture("UIImage/font2.png");
	m_pFirstResultSecOneth->SetPosition(10, 0);
	m_pFirstResultSecColon = new UITextImageView;
	m_pFirstResultSecColon->SetTexture("UIImage/font2.png");
	m_pFirstResultSecColon->SetPosition(10, 0);
	m_pFirstResultDotMilth = new UITextImageView;
	m_pFirstResultDotMilth->SetTexture("UIImage/font2.png");
	m_pFirstResultDotMilth->SetPosition(10, 0);
	m_pFirstResultDotTenth = new UITextImageView;
	m_pFirstResultDotTenth->SetTexture("UIImage/font2.png");
	m_pFirstResultDotTenth->SetPosition(10, 0);
	m_pFirstResultDotOneth = new UITextImageView;
	m_pFirstResultDotOneth->SetTexture("UIImage/font2.png");
	m_pFirstResultDotOneth->SetPosition(10, 0);

	// Second
	m_pSecond = new UITextImageView;
	m_pSecond->SetTexture("UIImage/font2.png");
	m_pSecond->SetXSize(1.0f);
	m_pSecond->SetYSize(1.0f);
	m_pSecond->SetPosition(0, 30);
	m_pSndPlayerName = new UITextImageView;
	m_pSndPlayerName->SetTexture("UIImage/font2.png");
	m_pSndPlayerName->SetPosition(30, 0);
	m_pSndPlayerName->SetColor(D3DCOLOR_ARGB(255, 61, 183, 204));
	m_pSndResultMinTenth = new UITextImageView;
	m_pSndResultMinTenth->SetTexture("UIImage/font2.png");
	m_pSndResultMinTenth->SetPosition(160, 0);
	m_pSndResultMinOneth = new UITextImageView;
	m_pSndResultMinOneth->SetTexture("UIImage/font2.png");
	m_pSndResultMinOneth->SetPosition(10, 0);
	m_pSndResultMinColon = new UITextImageView;
	m_pSndResultMinColon->SetTexture("UIImage/font2.png");
	m_pSndResultMinColon->SetPosition(10, 0);
	m_pSndResultSecTenth = new UITextImageView;
	m_pSndResultSecTenth->SetTexture("UIImage/font2.png");
	m_pSndResultSecTenth->SetPosition(10, 0);
	m_pSndResultSecOneth = new UITextImageView;
	m_pSndResultSecOneth->SetTexture("UIImage/font2.png");
	m_pSndResultSecOneth->SetPosition(10, 0);
	m_pSndResultSecColon = new UITextImageView;
	m_pSndResultSecColon->SetTexture("UIImage/font2.png");
	m_pSndResultSecColon->SetPosition(10, 0);
	m_pSndResultDotMilth = new UITextImageView;
	m_pSndResultDotMilth->SetTexture("UIImage/font2.png");
	m_pSndResultDotMilth->SetPosition(10, 0);
	m_pSndResultDotTenth = new UITextImageView;
	m_pSndResultDotTenth->SetTexture("UIImage/font2.png");
	m_pSndResultDotTenth->SetPosition(10, 0);
	m_pSndResultDotOneth = new UITextImageView;
	m_pSndResultDotOneth->SetTexture("UIImage/font2.png");
	m_pSndResultDotOneth->SetPosition(10, 0);

	// Third
	m_pThird = new UITextImageView;
	m_pThird->SetTexture("UIImage/font2.png");
	m_pThird->SetXSize(1.0f);
	m_pThird->SetYSize(1.0f);
	m_pThird->SetPosition(0, 30);
	m_pTrdPlayerName = new UITextImageView;
	m_pTrdPlayerName->SetTexture("UIImage/font2.png");
	m_pTrdPlayerName->SetPosition(30, 0);
	m_pTrdPlayerName->SetColor(D3DCOLOR_ARGB(255, 61, 183, 204));
	m_pTrdResultMinTenth = new UITextImageView;
	m_pTrdResultMinTenth->SetTexture("UIImage/font2.png");
	m_pTrdResultMinTenth->SetPosition(160, 0);
	m_pTrdResultMinOneth = new UITextImageView;
	m_pTrdResultMinOneth->SetTexture("UIImage/font2.png");
	m_pTrdResultMinOneth->SetPosition(10, 0);
	m_pTrdResultMinColon = new UITextImageView;
	m_pTrdResultMinColon->SetTexture("UIImage/font2.png");
	m_pTrdResultMinColon->SetPosition(10, 0);
	m_pTrdResultSecTenth = new UITextImageView;
	m_pTrdResultSecTenth->SetTexture("UIImage/font2.png");
	m_pTrdResultSecTenth->SetPosition(10, 0);
	m_pTrdResultSecOneth = new UITextImageView;
	m_pTrdResultSecOneth->SetTexture("UIImage/font2.png");
	m_pTrdResultSecOneth->SetPosition(10, 0);
	m_pTrdResultSecColon = new UITextImageView;
	m_pTrdResultSecColon->SetTexture("UIImage/font2.png");
	m_pTrdResultSecColon->SetPosition(10, 0);
	m_pTrdResultDotMilth = new UITextImageView;
	m_pTrdResultDotMilth->SetTexture("UIImage/font2.png");
	m_pTrdResultDotMilth->SetPosition(10, 0);
	m_pTrdResultDotTenth = new UITextImageView;
	m_pTrdResultDotTenth->SetTexture("UIImage/font2.png");
	m_pTrdResultDotTenth->SetPosition(10, 0);
	m_pTrdResultDotOneth = new UITextImageView;
	m_pTrdResultDotOneth->SetTexture("UIImage/font2.png");
	m_pTrdResultDotOneth->SetPosition(10, 0);

	// Fourth
	m_pFourth = new UITextImageView;
	m_pFourth->SetTexture("UIImage/font2.png");
	m_pFourth->SetXSize(1.0f);
	m_pFourth->SetYSize(1.0f);
	m_pFourth->SetPosition(0, 30);
	m_pFourthPlayerName = new UITextImageView;
	m_pFourthPlayerName->SetTexture("UIImage/font2.png");
	m_pFourthPlayerName->SetPosition(30, 0);
	m_pFourthPlayerName->SetColor(D3DCOLOR_ARGB(255, 61, 183, 204));
	m_pFourthResultMinTenth = new UITextImageView;
	m_pFourthResultMinTenth->SetTexture("UIImage/font2.png");
	m_pFourthResultMinTenth->SetPosition(160, 0);
	m_pFourthResultMinOneth = new UITextImageView;
	m_pFourthResultMinOneth->SetTexture("UIImage/font2.png");
	m_pFourthResultMinOneth->SetPosition(10, 0);
	m_pFourthResultMinColon = new UITextImageView;
	m_pFourthResultMinColon->SetTexture("UIImage/font2.png");
	m_pFourthResultMinColon->SetPosition(10, 0);
	m_pFourthResultSecTenth = new UITextImageView;
	m_pFourthResultSecTenth->SetTexture("UIImage/font2.png");
	m_pFourthResultSecTenth->SetPosition(10, 0);
	m_pFourthResultSecOneth = new UITextImageView;
	m_pFourthResultSecOneth->SetTexture("UIImage/font2.png");
	m_pFourthResultSecOneth->SetPosition(10, 0);
	m_pFourthResultSecColon = new UITextImageView;
	m_pFourthResultSecColon->SetTexture("UIImage/font2.png");
	m_pFourthResultSecColon->SetPosition(10, 0);
	m_pFourthResultDotMilth = new UITextImageView;
	m_pFourthResultDotMilth->SetTexture("UIImage/font2.png");
	m_pFourthResultDotMilth->SetPosition(10, 0);
	m_pFourthResultDotTenth = new UITextImageView;
	m_pFourthResultDotTenth->SetTexture("UIImage/font2.png");
	m_pFourthResultDotTenth->SetPosition(10, 0);
	m_pFourthResultDotOneth = new UITextImageView;
	m_pFourthResultDotOneth->SetTexture("UIImage/font2.png");
	m_pFourthResultDotOneth->SetPosition(10, 0);

	// Fifth
	m_pFifth = new UITextImageView;
	m_pFifth->SetTexture("UIImage/font2.png");
	m_pFifth->SetXSize(1.0f);
	m_pFifth->SetYSize(1.0f);
	m_pFifth->SetPosition(0, 30);
	m_pFifthPlayerName = new UITextImageView;
	m_pFifthPlayerName->SetTexture("UIImage/font2.png");
	m_pFifthPlayerName->SetPosition(30, 0);
	m_pFifthPlayerName->SetColor(D3DCOLOR_ARGB(255, 61, 183, 204));
	m_pFifthResultMinTenth = new UITextImageView;
	m_pFifthResultMinTenth->SetTexture("UIImage/font2.png");
	m_pFifthResultMinTenth->SetPosition(160, 0);
	m_pFifthResultMinOneth = new UITextImageView;
	m_pFifthResultMinOneth->SetTexture("UIImage/font2.png");
	m_pFifthResultMinOneth->SetPosition(10, 0);
	m_pFifthResultMinColon = new UITextImageView;
	m_pFifthResultMinColon->SetTexture("UIImage/font2.png");
	m_pFifthResultMinColon->SetPosition(10, 0);
	m_pFifthResultSecTenth = new UITextImageView;
	m_pFifthResultSecTenth->SetTexture("UIImage/font2.png");
	m_pFifthResultSecTenth->SetPosition(10, 0);
	m_pFifthResultSecOneth = new UITextImageView;
	m_pFifthResultSecOneth->SetTexture("UIImage/font2.png");
	m_pFifthResultSecOneth->SetPosition(10, 0);
	m_pFifthResultSecColon = new UITextImageView;
	m_pFifthResultSecColon->SetTexture("UIImage/font2.png");
	m_pFifthResultSecColon->SetPosition(10, 0);
	m_pFifthResultDotMilth = new UITextImageView;
	m_pFifthResultDotMilth->SetTexture("UIImage/font2.png");
	m_pFifthResultDotMilth->SetPosition(10, 0);
	m_pFifthResultDotTenth = new UITextImageView;
	m_pFifthResultDotTenth->SetTexture("UIImage/font2.png");
	m_pFifthResultDotTenth->SetPosition(10, 0);
	m_pFifthResultDotOneth = new UITextImageView;
	m_pFifthResultDotOneth->SetTexture("UIImage/font2.png");
	m_pFifthResultDotOneth->SetPosition(10, 0);

	// Sixth
	m_pSixth = new UITextImageView;
	m_pSixth->SetTexture("UIImage/font2.png");
	m_pSixth->SetXSize(1.0f);
	m_pSixth->SetYSize(1.0f);
	m_pSixth->SetPosition(0, 30);
	m_pSixthPlayerName = new UITextImageView;
	m_pSixthPlayerName->SetTexture("UIImage/font2.png");
	m_pSixthPlayerName->SetPosition(30, 0);
	m_pSixthPlayerName->SetColor(D3DCOLOR_ARGB(255, 61, 183, 204));
	m_pSixthResultMinTenth = new UITextImageView;
	m_pSixthResultMinTenth->SetTexture("UIImage/font2.png");
	m_pSixthResultMinTenth->SetPosition(160, 0);
	m_pSixthResultMinOneth = new UITextImageView;
	m_pSixthResultMinOneth->SetTexture("UIImage/font2.png");
	m_pSixthResultMinOneth->SetPosition(10, 0);
	m_pSixthResultMinColon = new UITextImageView;
	m_pSixthResultMinColon->SetTexture("UIImage/font2.png");
	m_pSixthResultMinColon->SetPosition(10, 0);
	m_pSixthResultSecTenth = new UITextImageView;
	m_pSixthResultSecTenth->SetTexture("UIImage/font2.png");
	m_pSixthResultSecTenth->SetPosition(10, 0);
	m_pSixthResultSecOneth = new UITextImageView;
	m_pSixthResultSecOneth->SetTexture("UIImage/font2.png");
	m_pSixthResultSecOneth->SetPosition(10, 0);
	m_pSixthResultSecColon = new UITextImageView;
	m_pSixthResultSecColon->SetTexture("UIImage/font2.png");
	m_pSixthResultSecColon->SetPosition(10, 0);
	m_pSixthResultDotMilth = new UITextImageView;
	m_pSixthResultDotMilth->SetTexture("UIImage/font2.png");
	m_pSixthResultDotMilth->SetPosition(10, 0);
	m_pSixthResultDotTenth = new UITextImageView;
	m_pSixthResultDotTenth->SetTexture("UIImage/font2.png");
	m_pSixthResultDotTenth->SetPosition(10, 0);
	m_pSixthResultDotOneth = new UITextImageView;
	m_pSixthResultDotOneth->SetTexture("UIImage/font2.png");
	m_pSixthResultDotOneth->SetPosition(10, 0);

	m_pSecondRetired = new UITextImageView;
	m_pSecondRetired->SetTexture("UIImage/font2.png");
	m_pSecondRetired->SetPosition(160, 0);

	m_pThridRetired = new UITextImageView;
	m_pThridRetired->SetTexture("UIImage/font2.png");
	m_pThridRetired->SetPosition(160, 0);

	m_pFourthRetired = new UITextImageView;
	m_pFourthRetired->SetTexture("UIImage/font2.png");
	m_pFourthRetired->SetPosition(160, 0);

	m_pFifthRetired = new UITextImageView;
	m_pFifthRetired->SetTexture("UIImage/font2.png");
	m_pFifthRetired->SetPosition(160, 0);

	m_pSixthRetired = new UITextImageView;
	m_pSixthRetired->SetTexture("UIImage/font2.png");
	m_pSixthRetired->SetPosition(160, 0);

	/*          Set Child          */

	//Basic
	m_pRootUI->AddChild(pLabCntFont);
	m_pRootUI->AddChild(pLastLabFont);
	m_pRootUI->AddChild(pImageView7);
	m_pRootUI->AddChild(pSpeedFrame);
	m_pRootUI->AddChild(pIV_arrowDir);

	pLabCntFont->AddChild(pImageView6);
	pLabCntFont->AddChild(m_pCurrentLab);
	m_pCurrentLab->AddChild(m_pMaxLab);
	pLastLabFont->AddChild(pBestLabFont);
	pLastLabFont->AddChild(pLabFont);
	pLastLabFont->AddChild(pRaceFont);
	pImageView6->AddChild(m_pItemImage);

	pImageView7->AddChild(pITV_Rank);
	pImageView7->AddChild(pITV_Rank2);

	pSpeedFrame->AddChild(m_pSpeedometerImage);
	pSpeedFrame->AddChild(m_pSpeedOne);
	pSpeedFrame->AddChild(pSpeed_mph);
	m_pSpeedOne->AddChild(m_pSpeedTen);
	m_pSpeedTen->AddChild(m_pSpeedHun);


	//Last Font
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

	// Result
	m_pRootUI->AddChild(m_pResultRing);
	m_pResultRing->AddChild(m_pRaceResult);
	m_pRaceResult->AddChild(m_pFirst);

	/*          First          */
	m_pFirst->AddChild(m_pFirstPlayerName);
	m_pFirst->AddChild(m_pSecond);
	m_pFirst->AddChild(m_pFirstResultMinTenth);
	m_pFirstResultMinTenth->AddChild(m_pFirstResultMinOneth);
	m_pFirstResultMinOneth->AddChild(m_pFirstResultMinColon);
	m_pFirstResultMinColon->AddChild(m_pFirstResultSecTenth);
	m_pFirstResultSecTenth->AddChild(m_pFirstResultSecOneth);
	m_pFirstResultSecOneth->AddChild(m_pFirstResultSecColon);
	m_pFirstResultSecColon->AddChild(m_pFirstResultDotMilth);
	m_pFirstResultDotMilth->AddChild(m_pFirstResultDotTenth);
	m_pFirstResultDotTenth->AddChild(m_pFirstResultDotOneth);

	/*          Second          */
	m_pSecond->AddChild(m_pSndPlayerName);
	m_pSecond->AddChild(m_pThird);

	m_pSecond->AddChild(m_pSecondRetired);;
	m_pSecond->AddChild(m_pSndResultMinTenth);

	m_pSndResultMinTenth->AddChild(m_pSndResultMinOneth);
	m_pSndResultMinOneth->AddChild(m_pSndResultMinColon);
	m_pSndResultMinColon->AddChild(m_pSndResultSecTenth);
	m_pSndResultSecTenth->AddChild(m_pSndResultSecOneth);
	m_pSndResultSecOneth->AddChild(m_pSndResultSecColon);
	m_pSndResultSecColon->AddChild(m_pSndResultDotMilth);
	m_pSndResultDotMilth->AddChild(m_pSndResultDotTenth);
	m_pSndResultDotTenth->AddChild(m_pSndResultDotOneth);

	/*          Third          */
	m_pThird->AddChild(m_pTrdPlayerName);
	m_pThird->AddChild(m_pFourth);

	m_pThird->AddChild(m_pThridRetired);
	m_pThird->AddChild(m_pTrdResultMinTenth);

	m_pTrdResultMinTenth->AddChild(m_pTrdResultMinOneth);
	m_pTrdResultMinOneth->AddChild(m_pTrdResultMinColon);
	m_pTrdResultMinColon->AddChild(m_pTrdResultSecTenth);
	m_pTrdResultSecTenth->AddChild(m_pTrdResultSecOneth);
	m_pTrdResultSecOneth->AddChild(m_pTrdResultSecColon);
	m_pTrdResultSecColon->AddChild(m_pTrdResultDotMilth);
	m_pTrdResultDotMilth->AddChild(m_pTrdResultDotTenth);
	m_pTrdResultDotTenth->AddChild(m_pTrdResultDotOneth);

	/*          Fourth          */
	m_pFourth->AddChild(m_pFourthPlayerName);
	m_pFourth->AddChild(m_pFifth);
	m_pFourth->AddChild(m_pFourthResultMinTenth);
	m_pFourth->AddChild(m_pFourthRetired);
	m_pFourthResultMinTenth->AddChild(m_pFourthResultMinOneth);
	m_pFourthResultMinOneth->AddChild(m_pFourthResultMinColon);
	m_pFourthResultMinColon->AddChild(m_pFourthResultSecTenth);
	m_pFourthResultSecTenth->AddChild(m_pFourthResultSecOneth);
	m_pFourthResultSecOneth->AddChild(m_pFourthResultSecColon);
	m_pFourthResultSecColon->AddChild(m_pFourthResultDotMilth);
	m_pFourthResultDotMilth->AddChild(m_pFourthResultDotTenth);
	m_pFourthResultDotTenth->AddChild(m_pFourthResultDotOneth);

	/*          Fifth          */
	m_pFifth->AddChild(m_pFifthPlayerName);
	m_pFifth->AddChild(m_pSixth);
	m_pFifth->AddChild(m_pFifthResultMinTenth);
	m_pFifth->AddChild(m_pFifthRetired);
	m_pFifthResultMinTenth->AddChild(m_pFifthResultMinOneth);
	m_pFifthResultMinOneth->AddChild(m_pFifthResultMinColon);
	m_pFifthResultMinColon->AddChild(m_pFifthResultSecTenth);
	m_pFifthResultSecTenth->AddChild(m_pFifthResultSecOneth);
	m_pFifthResultSecOneth->AddChild(m_pFifthResultSecColon);
	m_pFifthResultSecColon->AddChild(m_pFifthResultDotMilth);
	m_pFifthResultDotMilth->AddChild(m_pFifthResultDotTenth);
	m_pFifthResultDotTenth->AddChild(m_pFifthResultDotOneth);

	/*          Sixth          */
	m_pSixth->AddChild(m_pSixthPlayerName);
	m_pSixth->AddChild(m_pSixthResultMinTenth);
	m_pSixth->AddChild(m_pSixthRetired);
	m_pSixthResultMinTenth->AddChild(m_pSixthResultMinOneth);
	m_pSixthResultMinOneth->AddChild(m_pSixthResultMinColon);
	m_pSixthResultMinColon->AddChild(m_pSixthResultSecTenth);
	m_pSixthResultSecTenth->AddChild(m_pSixthResultSecOneth);
	m_pSixthResultSecOneth->AddChild(m_pSixthResultSecColon);
	m_pSixthResultSecColon->AddChild(m_pSixthResultDotMilth);
	m_pSixthResultDotMilth->AddChild(m_pSixthResultDotTenth);
	m_pSixthResultDotTenth->AddChild(m_pSixthResultDotOneth);

	//========================================
	// 시작시 321GO 
	// by. 태섭
	//========================================
	m_p321go = new c321GO;
	m_p321go->LinkRacingScene(m_pRacingScene);
	m_p321go->Setup();
}

void InGameUI::Update()
{
	iLobby::Update();
	
	if (m_p321go)
	{
		m_p321go->Update();
//		return;
	}

	UpdateSpeed();
	UpdateLabCount();

	UpdateArrowDir();

	

	int nTrackCount = m_pRacingScene->GettrackEndCount();
	if (m_LabCnt > -1 && m_LabCnt < nTrackCount)	UpdateLabTime();

	if (m_LabCnt >= nTrackCount)
	{
		RaceResults();
		if (g_pKeyManager->isOnceKeyDown(VK_RETURN))
		{
			g_SceneManager->ChangeScene("Lobby");
			*iLobby::m_gLobbyState = START_LOBBY;
		}
	}
}

void InGameUI::Render(LPD3DXSPRITE pSprite)
{
	iLobby::Render(pSprite);

	if (m_p321go)
	{
		m_p321go->Render();
	}
}

void InGameUI::Destroy()
{
	iLobby::Destroy();
	return;

	SAFE_DELETE(m_pItemImage);
	SAFE_DELETE(m_pLobby);
	//SAFE_DELETE(m_pLab);
	SAFE_DELETE(m_pCurrentLab);
	SAFE_DELETE(m_pMaxLab);
	SAFE_DELETE(m_pLastDotOneTh);
	SAFE_DELETE(m_pLastDotTenth);
	SAFE_DELETE(m_pLastDotMilth);
	SAFE_DELETE(m_pLastSecOneth);
	SAFE_DELETE(m_pLastSecTenth);
	SAFE_DELETE(m_pLastMinOneth);
	SAFE_DELETE(m_pLastMinTenth);
	SAFE_DELETE(m_pBestDotOneTh);
	SAFE_DELETE(m_pBestDotTenth);
	SAFE_DELETE(m_pBestDotMilth);
	SAFE_DELETE(m_pBestSecOneth);
	SAFE_DELETE(m_pBestSecTenth);
	SAFE_DELETE(m_pBestMinOneth);
	SAFE_DELETE(m_pBestMinTenth);
	SAFE_DELETE(m_pLabElapseTime);
	SAFE_DELETE(m_pLabDotTenth);
	SAFE_DELETE(m_pLabDotMilth);
	SAFE_DELETE(m_pLabSecOneth);
	SAFE_DELETE(m_pLabSecTenth);
	SAFE_DELETE(m_pLabMinOneth);
	SAFE_DELETE(m_pLabMinTenth);
	SAFE_DELETE(m_pElapseTime);
	SAFE_DELETE(m_pDotTenth);
	SAFE_DELETE(m_pDotMilth);
	SAFE_DELETE(m_pSecOneth);
	SAFE_DELETE(m_pSecTenth);
	SAFE_DELETE(m_pMinOneth);
	SAFE_DELETE(m_pMinTenth);
	SAFE_DELETE(m_pSpeedOne);
	SAFE_DELETE(m_pSpeedTen);
	SAFE_DELETE(m_pSpeedHun);
	SAFE_DELETE(m_pSpeedometerImage);
	SAFE_DELETE(pITV_Rank);
	SAFE_DELETE(pITV_Rank2);
	SAFE_DELETE(pIV_arrowDir);
	SAFE_DELETE(m_p321go);
	m_pTrack = NULL;
	m_pCar = NULL;
	m_pRacingScene = NULL;

	iLobby::Destroy();
}

void InGameUI::UpdateSpeed()
{
	int fTemp;
	fTemp = m_pCar->GetCurrentSpeed();
	if (fTemp >= 999)
		fTemp = 999;

	int nOne;
	int nTen;
	int nHun;

	nOne = (int)(fTemp % 10) + FONT2_NUM0;
	nTen = (int)((fTemp / 10)%10) + FONT2_NUM0;
	nHun = (int)(fTemp / 100) + FONT2_NUM0;

	if (nOne <= FONT2_NUM0) nOne = FONT2_NUM0;
	if (nTen <= FONT2_NUM0) nTen = FONT2_NUM0;
	if (nHun <= FONT2_NUM0) nHun = FONT2_NUM0;

	std::string strHun;
	std::string strTen;
	std::string strOne;

	strHun = nHun;
	strTen = nTen;
	strOne = nOne;

	m_pSpeedHun->SetText(strHun);
	m_pSpeedTen->SetText(strTen);
	m_pSpeedOne->SetText(strOne);
	m_pSpeedometerImage->SetRpmGauge(m_pCar->GetNxVehicle()->getWheel(1)->getRpm());
}

void InGameUI::UpdateLabCount()
{
	if (m_LabCnt < 1)	m_pCurrentLab->SetText("1");
	if (m_LabCnt == 1) m_pCurrentLab->SetText("2");
	if (m_LabCnt == 2) m_pCurrentLab->SetText("3");
	if (m_LabCnt > 2)
	{
		m_pCurrentLab->SetText("Finished");
		m_pMaxLab->SetText("");
	}
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

	if (m_LabCnt != -1)
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

	m_pLastDotOneTh->SetText(LastDotOneth);
	m_pLastDotTenth->SetText(LastDotTenth);
	m_pLastDotMilth->SetText(LastDotMilth);
	m_pLastSecOneth->SetText(LastSecOneth);
	m_pLastSecTenth->SetText(LastSecTenth);
	m_pLastMinOneth->SetText(LastMinOneth);
	m_pLastMinTenth->SetText(LastMinTenth);
}

void InGameUI::CompareBestTime()
{
	std::string BestDotOneth;
	std::string BestDotTenth;
	std::string BestDotMilth;
	std::string BestSecOneth;
	std::string BestSecTenth;
	std::string BestMinOneth;
	std::string BestMinTenth;

	int CurrentDotOneTh = 0;
	int CurrentDotTenth = 0;
	int CurrentDotMilth = 0;
	int CurrentSecOneth = 0;
	int CurrentSecTenth = 0;
	int CurrentMinOneth = 0;
	int CurrentMinTenth = 0;

	CurrentDotOneTh = m_WorldDotOneth;
	CurrentDotTenth = m_LabDotTenth;
	CurrentDotMilth = m_LabDotMilth;
	CurrentSecOneth = m_LabSecOneth;
	CurrentSecTenth = m_LabSecTenth;
	CurrentMinOneth = m_LabMinOneth;
	CurrentMinTenth = m_LabMinTenth;

	if (m_LabCnt == 1)
	{
		m_BestDotOneTh = CurrentDotOneTh;
		m_BestDotTenth = CurrentDotTenth;
		m_BestDotMilth = CurrentDotMilth;
		m_BestSecOneth = CurrentSecOneth;
		m_BestSecTenth = CurrentSecTenth;
		m_BestMinOneth = CurrentMinOneth;
		m_BestMinTenth = CurrentMinTenth;

		int Check = 1;
	}
	else if (m_LabCnt > 1)
	{
		if (m_BestMinTenth > CurrentMinTenth)
		{
			m_BestDotOneTh = CurrentDotOneTh;
			m_BestDotTenth = CurrentDotTenth;
			m_BestDotMilth = CurrentDotMilth;
			m_BestSecOneth = CurrentSecOneth;
			m_BestSecTenth = CurrentSecTenth;
			m_BestMinOneth = CurrentMinOneth;
			m_BestMinTenth = CurrentMinTenth;
		}
		else if (m_BestMinTenth == CurrentMinTenth)
		{
			if (m_BestMinOneth > CurrentMinOneth)
			{
				m_BestDotOneTh = CurrentDotOneTh;
				m_BestDotTenth = CurrentDotTenth;
				m_BestDotMilth = CurrentDotMilth;
				m_BestSecOneth = CurrentSecOneth;
				m_BestSecTenth = CurrentSecTenth;
				m_BestMinOneth = CurrentMinOneth;
				m_BestMinTenth = CurrentMinTenth;
			}
			else if (m_BestMinOneth == CurrentMinOneth)
			{
				if (m_BestSecTenth > CurrentSecTenth)
				{
					m_BestDotOneTh = CurrentDotOneTh;
					m_BestDotTenth = CurrentDotTenth;
					m_BestDotMilth = CurrentDotMilth;
					m_BestSecOneth = CurrentSecOneth;
					m_BestSecTenth = CurrentSecTenth;
					m_BestMinOneth = CurrentMinOneth;
					m_BestMinTenth = CurrentMinTenth;
				}
				else if (m_BestSecTenth == CurrentSecTenth)
				{
					if (m_BestSecOneth > CurrentSecOneth)
					{
						m_BestDotOneTh = CurrentDotOneTh;
						m_BestDotTenth = CurrentDotTenth;
						m_BestDotMilth = CurrentDotMilth;
						m_BestSecOneth = CurrentSecOneth;
						m_BestSecTenth = CurrentSecTenth;
						m_BestMinOneth = CurrentMinOneth;
						m_BestMinTenth = CurrentMinTenth;
					}
					else if (m_BestSecOneth == CurrentSecOneth)
					{
						if (m_BestDotMilth > CurrentDotMilth)
						{
							m_BestDotOneTh = CurrentDotOneTh;
							m_BestDotTenth = CurrentDotTenth;
							m_BestDotMilth = CurrentDotMilth;
							m_BestSecOneth = CurrentSecOneth;
							m_BestSecTenth = CurrentSecTenth;
							m_BestMinOneth = CurrentMinOneth;
							m_BestMinTenth = CurrentMinTenth;
						}
						else if (m_BestDotMilth == CurrentDotMilth)
						{
							if (m_BestDotTenth > CurrentDotTenth)
							{
								m_BestDotOneTh = CurrentDotOneTh;
								m_BestDotTenth = CurrentDotTenth;
								m_BestDotMilth = CurrentDotMilth;
								m_BestSecOneth = CurrentSecOneth;
								m_BestSecTenth = CurrentSecTenth;
								m_BestMinOneth = CurrentMinOneth;
								m_BestMinTenth = CurrentMinTenth;
							}
							else if (m_BestDotTenth == CurrentDotTenth)
							{
								if (m_BestDotOneTh > CurrentDotOneTh)
								{
									m_BestDotOneTh = CurrentDotOneTh;
									m_BestDotTenth = CurrentDotTenth;
									m_BestDotMilth = CurrentDotMilth;
									m_BestSecOneth = CurrentSecOneth;
									m_BestSecTenth = CurrentSecTenth;
									m_BestMinOneth = CurrentMinOneth;
									m_BestMinTenth = CurrentMinTenth;
								}
							}
						}
					}
				}
			}
		}
	}

	BestDotOneth = m_BestDotOneTh;
	BestDotTenth = m_BestDotTenth;
	BestDotMilth = m_BestDotMilth;
	BestSecOneth = m_BestSecOneth;
	BestSecTenth = m_BestSecTenth;
	BestMinOneth = m_BestMinOneth;
	BestMinTenth = m_BestMinTenth;

	m_pBestDotOneTh->SetText(BestDotOneth);
	m_pBestDotTenth->SetText(BestDotTenth);
	m_pBestDotMilth->SetText(BestDotMilth);
	m_pBestSecOneth->SetText(BestSecOneth);
	m_pBestSecTenth->SetText(BestSecTenth);
	m_pBestMinOneth->SetText(BestMinOneth);
	m_pBestMinTenth->SetText(BestMinTenth);
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

	//if (g_pKeyManager->isOnceKeyDown('B'))
	//{
	//	//if (m_LabCnt == -1) m_LabCnt += 1;
	//	//else m_LabCnt -= 1;
	//
	//	m_LabElapseTime = 0;
	//}

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
	m_LabDotTenth = (int)(CalcDP)+FONT2_NUM0;							//		x.?xx = x.8xx
	CalcDP -= (int)CalcDP;												//		CalcDP = 8.76 - 8 = 0.76
	CalcDP *= 10.0f;													//		CalcDP = 0.76 * 10 = 7.6
	m_LabDotMilth = (int)CalcDP + FONT2_NUM0;							//		x.8?x = x.87x
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

	m_ElapseTime = m_pCar->GetTotlaTimeCount();			// Uptate ElapsedTime
	int CalcMin = (int)(m_ElapseTime / 60.f);
	m_MinOneth = CalcMin % 10 + FONT2_NUM0;
	m_MinTenth = CalcMin / 10 + FONT2_NUM0;
	//if (m_ElapseTime > TIMEMAX)						// After 60 Second
	//{
	//	m_ElapseTime = 0;								// ElapsedTime = 0
	//	m_MinOneth += 1;								// Add 1 Minute
	//}
	//f (m_MinOneth > FONT2_NUM9)						// After 10 Minute
	//
	//	m_MinOneth = FONT2_NUM0;						// MinuteOneth = 0; 
	//	m_MinTenth += 1;								// Add MinuteTenth ( 09:59 -> 10:00 )
	//
	//if (m_MinTenth > FONT2_NUM9)
	//{
	//	m_MinTenth = FONT2_NUM0;
	//}
	m_SecTenth = (int(m_ElapseTime / 10) % 6) + FONT2_NUM0;		// Ex : m_ElapseTime = 59
	m_SecOneth = ((int)m_ElapseTime % 10) + FONT2_NUM0; //      m_ElapseTime / 10 = 5;	
														//      m_ElapseTime % 10 = 9;
														//      Therefore Current Second : 59

																//		EX : m_ElapseTime = 9.876
	float CalcDP = (m_ElapseTime - (int)m_ElapseTime) * 10.0f;	//		CalcDP = (9.876 - 9) * 10 = 8.76
	//DotMilth = m_DotMilth = (int)(CalcDP) + FONT2_NUM0;		//		x.?xx = x.8xx
	DotMilth = m_DotMilth = ((int)(m_ElapseTime * 10) % 10) + FONT2_NUM0;
	CalcDP -= (int)CalcDP;										//		CalcDP = 8.76 - 8 = 0.76
	CalcDP *= 10.0f;											//		CalcDP = 0.76 * 10 = 7.6
	//DotTenth = m_DotTenth = (int)CalcDP + FONT2_NUM0;			//		x.8?x = x.87x
	DotTenth = m_DotTenth = ((int)(m_ElapseTime * 100) % 10) + FONT2_NUM0;
	CalcDP -= (int)CalcDP;										//		CalcDP = 7.6 - 7 = 0.6
	CalcDP *= 10.0f;											//		CalcDP = 0.6 * 10 = 6
	ElapseTime = (int)CalcDP + FONT2_NUM0;						//		x.87? = x.876
	//m_WorldDotOneth = (int)CalcDP + FONT2_NUM0;				//		Therefore Calculation Decimal Point = 0.876
	m_WorldDotOneth = ((int)(m_ElapseTime * 1000) % 10) + FONT2_NUM0;

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

void InGameUI::UpdateArrowDir()
{
	int curboxID = m_pCar->GetNextCheckBoxID();
	cCheckBox* checkboxPt = (cCheckBox*)m_pTrack->GetCheckBoxs()[curboxID];
	D3DXVECTOR3 posCheckbox = checkboxPt->GetPosition();
	D3DXVECTOR3 tar = posCheckbox;
	tar.y = 0.0f;

	D3DXVECTOR3 pos = D3DXVECTOR3(m_pCar->GetPosition().x, 0.0f, m_pCar->GetPosition().z);	// 자동차 위치
	D3DXVECTOR3 carDir = D3DXVECTOR3(m_pCar->GetDirection().x, 0.0f, m_pCar->GetDirection().z);	// 차 방향
	D3DXVECTOR3 arrowDir = tar - checkboxPt->GetNextCheckBox()->GetPosition();				// 화살표 방향

	D3DXVec3Normalize(&carDir, &carDir);
	D3DXVec3Normalize(&arrowDir, &arrowDir);

	// 내적
	float dot = D3DXVec3Dot(&carDir, &arrowDir);
	float angle = acos(dot);

	// 오른쪽 왼쪽 방향 구분위해
	D3DXVECTOR3 rightDir;
	D3DXVec3Normalize(&rightDir, &rightDir);

	D3DXVec3Cross(&rightDir, &carDir, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));

	if (D3DXVec3Dot(&rightDir, &arrowDir) < 0)
	{
		angle = -angle;
	}

	pIV_arrowDir->SetArrowAngle(-angle);
}

void InGameUI::RaceResults()
{
	// String

	/*          First          */
	std::string FstResultDotOneth;
	std::string FstResultDotTenth;								
	std::string FstResultDotMilth;								
	std::string FstResultSecOneth;								
	std::string FstResultSecTenth;								
	std::string FstResultMinOneth;								
	std::string FstResultMinTenth;	

	/*          Sec          */
	std::string SndResultDotOneth;
	std::string SndResultDotTenth;
	std::string SndResultDotMilth;
	std::string SndResultSecOneth;
	std::string SndResultSecTenth;
	std::string SndResultMinOneth;
	std::string SndResultMinTenth;
	std::string SndRetired;

	/*         Third          */
	std::string TrdResultDotOneth;
	std::string TrdResultDotTenth;
	std::string TrdResultDotMilth;
	std::string TrdResultSecOneth;
	std::string TrdResultSecTenth;
	std::string TrdResultMinOneth;
	std::string TrdResultMinTenth;
	std::string TrdRetired;

	/*         Fourth          */
	std::string FourthResultDotOneth;
	std::string FourthResultDotTenth;
	std::string FourthResultDotMilth;
	std::string FourthResultSecOneth;
	std::string FourthResultSecTenth;
	std::string FourthResultMinOneth;
	std::string FourthResultMinTenth;
	std::string FourRetired;

	/*         Fifth          */
	std::string FifthResultDotOneth;
	std::string FifthResultDotTenth;
	std::string FifthResultDotMilth;
	std::string FifthResultSecOneth;
	std::string FifthResultSecTenth;
	std::string FifthResultMinOneth;
	std::string FifthResultMinTenth;
	std::string FifthRetired;

	/*         Sixth          */
	std::string SixthResultDotOneth;
	std::string SixthResultDotTenth;
	std::string SixthResultDotMilth;
	std::string SixthResultSecOneth;
	std::string SixthResultSecTenth;
	std::string SixthResultMinOneth;
	std::string SixthResultMinTenth;
	std::string SixthRetired;

	//DotMilth = m_DotMilth = (int)(CalcDP)+FONT2_NUM0;
	//CalcDP -= (int)CalcDP;
	//CalcDP *= 10.0f;
	//DotTenth = m_DotTenth = (int)CalcDP + FONT2_NUM0;
	//CalcDP -= (int)CalcDP;
	//CalcDP *= 10.0f;
	//ElapseTime = (int)CalcDP + FONT2_NUM0;
	//m_WorldDotOneth = (int)CalcDP + FONT2_NUM0;
	//
	//for (int i = 0; i < 6; ++i)
	//{
	//	float CalcDP = (m_ElapseTime - (int)m_ElapseTime) * 10.0f;
	//}

	float total = m_pRacingScene->GetRankVector(0)->GetTotlaTimeCount();
	FstResultDotOneth			= ((int)(total * 1000) % 10) + FONT2_NUM0;
	FstResultDotTenth			= ((int)(total * 100) % 10) + FONT2_NUM0;
	FstResultDotMilth			= ((int)(total * 10) % 10) + FONT2_NUM0;
	FstResultSecOneth			= ((int)total % 10) + FONT2_NUM0;
	FstResultSecTenth			= ((int)total / 10 % 6) + FONT2_NUM0;
	FstResultMinOneth			= (((int)total / 60) % 10) + FONT2_NUM0;
	FstResultMinTenth			= ((((int)total / 60) / 10) % 10) + FONT2_NUM0;

	total = m_pRacingScene->GetRankVector(1)->GetTotlaTimeCount();
	SndResultDotOneth			= ((int)(total * 1000) % 10) + FONT2_NUM0;
	SndResultDotTenth			= ((int)(total * 100) % 10) + FONT2_NUM0;
	SndResultDotMilth			= ((int)(total * 10) % 10) + FONT2_NUM0;
	SndResultSecOneth			= ((int)total % 10) + FONT2_NUM0;
	SndResultSecTenth			= ((int)total / 10 % 6) + FONT2_NUM0;
	SndResultMinOneth			= (((int)total / 60) % 10) + FONT2_NUM0;
	SndResultMinTenth			= ((((int)total / 60) / 10) % 10) + FONT2_NUM0;
	
	total = m_pRacingScene->GetRankVector(2)->GetTotlaTimeCount();
	TrdResultDotOneth			= ((int)(total * 1000) % 10) + FONT2_NUM0;
	TrdResultDotTenth			= ((int)(total * 100) % 10) + FONT2_NUM0;
	TrdResultDotMilth			= ((int)(total * 10) % 10) + FONT2_NUM0;
	TrdResultSecOneth			= ((int)total % 10) + FONT2_NUM0;
	TrdResultSecTenth			= ((int)total / 10 % 6) + FONT2_NUM0;
	TrdResultMinOneth			= (((int)total / 60) % 10) + FONT2_NUM0;
	TrdResultMinTenth			= ((((int)total / 60) / 10) % 10) + FONT2_NUM0;
	
	total = m_pRacingScene->GetRankVector(3)->GetTotlaTimeCount();
	FourthResultDotOneth		= ((int)(total * 1000) % 10) + FONT2_NUM0;
	FourthResultDotTenth		= ((int)(total * 100) % 10) + FONT2_NUM0;
	FourthResultDotMilth		= ((int)(total * 10) % 10) + FONT2_NUM0;
	FourthResultSecOneth		= ((int)total % 10) + FONT2_NUM0;
	FourthResultSecTenth		= ((int)total / 10 % 6) + FONT2_NUM0;
	FourthResultMinOneth		= (((int)total / 60) % 10) + FONT2_NUM0;
	FourthResultMinTenth		= ((((int)total / 60) / 10) % 10) + FONT2_NUM0;
	
	total = m_pRacingScene->GetRankVector(4)->GetTotlaTimeCount();
	FifthResultDotOneth		= ((int)(total * 1000) % 10) + FONT2_NUM0;
	FifthResultDotTenth		= ((int)(total * 100) % 10) + FONT2_NUM0;
	FifthResultDotMilth		= ((int)(total * 10) % 10) + FONT2_NUM0;
	FifthResultSecOneth		= ((int)total % 10) + FONT2_NUM0;
	FifthResultSecTenth		= ((int)total / 10 % 6) + FONT2_NUM0;
	FifthResultMinOneth		= (((int)total / 60) % 10) + FONT2_NUM0;
	FifthResultMinTenth		= ((((int)total / 60) / 10) % 10) + FONT2_NUM0;
	
	total = m_pRacingScene->GetRankVector(5)->GetTotlaTimeCount();
	SixthResultDotOneth		= ((int)(total * 1000) % 10) + FONT2_NUM0;
	SixthResultDotTenth		= ((int)(total * 100) % 10) + FONT2_NUM0;
	SixthResultDotMilth		= ((int)(total * 10) % 10) + FONT2_NUM0;
	SixthResultSecOneth		= ((int)total % 10) + FONT2_NUM0;
	SixthResultSecTenth		= ((int)total / 10 % 6) + FONT2_NUM0;
	SixthResultMinOneth		= (((int)total / 60) % 10) + FONT2_NUM0;
	SixthResultMinTenth		= ((((int)total / 60) / 10) % 10) + FONT2_NUM0;

	// Setting
	m_pResultRing->SetTexture("UIImage/ring.png");
	m_pRaceResult->SetText("Race Results");


	// Text Setting

	/*          First          */
	m_pFirstResultMinTenth->SetText(FstResultMinTenth);
	m_pFirstResultMinOneth->SetText(FstResultMinOneth);
	m_pFirstResultMinColon->SetText(":");
	m_pFirstResultSecTenth->SetText(FstResultSecTenth);
	m_pFirstResultSecOneth->SetText(FstResultSecOneth);
	m_pFirstResultSecColon->SetText(":");
	m_pFirstResultDotMilth->SetText(FstResultDotMilth);
	m_pFirstResultDotTenth->SetText(FstResultDotTenth);
	m_pFirstResultDotOneth->SetText(FstResultDotOneth);
	m_pFirstPlayerName->SetText(m_pRacingScene->GetRankVector(0)->GetUserNameW());
	m_pFirst->SetText("01");
	
	/*          Second          */
	//m_pSndResultMinTenth->SetText(SndResultMinTenth);
	//m_pSndResultMinOneth->SetText(SndResultMinOneth);
	//m_pSndResultMinColon->SetText(":");
	//m_pSndResultSecTenth->SetText(SndResultSecTenth);
	//m_pSndResultSecOneth->SetText(SndResultSecOneth);
	//m_pSndResultSecColon->SetText(":");
	//m_pSndResultDotMilth->SetText(SndResultDotMilth);
	//m_pSndResultDotTenth->SetText(SndResultDotTenth);
	//m_pSndResultDotOneth->SetText(SndResultDotOneth);
	m_pSndPlayerName->SetText(m_pRacingScene->GetRankVector(1)->GetUserNameW());
	m_pSecond->SetText("02");
	//m_pSecondRetired->SetText("Retired");

	/*          Thrid          */
	//m_pTrdResultMinTenth->SetText(TrdResultMinTenth);
	//m_pTrdResultMinOneth->SetText(TrdResultMinOneth);
	//m_pTrdResultMinColon->SetText(":");
	//m_pTrdResultSecTenth->SetText(TrdResultSecTenth);
	//m_pTrdResultSecOneth->SetText(TrdResultSecOneth);
	//m_pTrdResultSecColon->SetText(":");
	//m_pTrdResultDotMilth->SetText(TrdResultDotMilth);
	//m_pTrdResultDotTenth->SetText(TrdResultDotTenth);
	//m_pTrdResultDotOneth->SetText(TrdResultDotOneth);
	m_pTrdPlayerName->SetText(m_pRacingScene->GetRankVector(2)->GetUserNameW());
	m_pThird->SetText("03");

	/*          Fourth          */
	//m_pFourthResultMinTenth->SetText(FourthResultMinTenth);
	//m_pFourthResultMinOneth->SetText(FourthResultMinOneth);
	//m_pFourthResultMinColon->SetText(":");
	//m_pFourthResultSecTenth->SetText(FourthResultSecTenth);
	//m_pFourthResultSecOneth->SetText(FourthResultSecOneth);
	//m_pFourthResultSecColon->SetText(":");
	//m_pFourthResultDotMilth->SetText(FourthResultDotMilth);
	//m_pFourthResultDotTenth->SetText(FourthResultDotTenth);
	//m_pFourthResultDotOneth->SetText(FourthResultDotOneth);
	m_pFourthPlayerName->SetText(m_pRacingScene->GetRankVector(3)->GetUserNameW());
	m_pFourth->SetText("04");
	//m_pFourthRetired->SetText("Retired");

	/*          Fifth          */
	//m_pFifthResultMinTenth->SetText(FifthResultMinTenth);
	//m_pFifthResultMinOneth->SetText(FifthResultMinOneth);
	//m_pFifthResultMinColon->SetText(":");
	//m_pFifthResultSecTenth->SetText(FifthResultSecTenth);
	//m_pFifthResultSecOneth->SetText(FifthResultSecOneth);
	//m_pFifthResultSecColon->SetText(":");
	//m_pFifthResultDotMilth->SetText(FifthResultDotMilth);
	//m_pFifthResultDotTenth->SetText(FifthResultDotTenth);
	//m_pFifthResultDotOneth->SetText(FifthResultDotOneth);
	m_pFifthPlayerName->SetText(m_pRacingScene->GetRankVector(4)->GetUserNameW());
	m_pFifth->SetText("05");

	/*          Sixth          */
	//m_pSixthResultMinTenth->SetText(SixthResultMinTenth);
	//m_pSixthResultMinOneth->SetText(SixthResultMinOneth);
	//m_pSixthResultMinColon->SetText(":");
	//m_pSixthResultSecTenth->SetText(SixthResultSecTenth);
	//m_pSixthResultSecOneth->SetText(SixthResultSecOneth);
	//m_pSixthResultSecColon->SetText(":");
	//m_pSixthResultDotMilth->SetText(SixthResultDotMilth);
	//m_pSixthResultDotTenth->SetText(SixthResultDotTenth);
	//m_pSixthResultDotOneth->SetText(SixthResultDotOneth);
	m_pSixthPlayerName->SetText(m_pRacingScene->GetRankVector(5)->GetUserNameW());
	m_pSixth->SetText("06");

	// 1
	if (m_pCar->GetCurRank() == 1)
	{
		m_pSndResultMinTenth->SetText("");
		m_pSndResultMinOneth->SetText("");
		m_pSndResultMinColon->SetText("Retired");
		m_pSndResultSecTenth->SetText("");
		m_pSndResultSecOneth->SetText("");
		m_pSndResultSecColon->SetText("");
		m_pSndResultDotMilth->SetText("");
		m_pSndResultDotTenth->SetText("");
		m_pSndResultDotOneth->SetText("");

		m_pTrdResultMinTenth->SetText("");
		m_pTrdResultMinOneth->SetText("");
		m_pTrdResultMinColon->SetText("Retired");
		m_pTrdResultSecTenth->SetText("");
		m_pTrdResultSecOneth->SetText("");
		m_pTrdResultSecColon->SetText("");
		m_pTrdResultDotMilth->SetText("");
		m_pTrdResultDotTenth->SetText("");
		m_pTrdResultDotOneth->SetText("");

		m_pFourthResultMinTenth->SetText("");
		m_pFourthResultMinOneth->SetText("");
		m_pFourthResultMinColon->SetText("Retired");
		m_pFourthResultSecTenth->SetText("");
		m_pFourthResultSecOneth->SetText("");
		m_pFourthResultSecColon->SetText("");
		m_pFourthResultDotMilth->SetText("");
		m_pFourthResultDotTenth->SetText("");
		m_pFourthResultDotOneth->SetText("");

		m_pFifthResultMinTenth->SetText("");
		m_pFifthResultMinOneth->SetText("");
		m_pFifthResultMinColon->SetText("Retired");
		m_pFifthResultSecTenth->SetText("");
		m_pFifthResultSecOneth->SetText("");
		m_pFifthResultSecColon->SetText("");
		m_pFifthResultDotMilth->SetText("");
		m_pFifthResultDotTenth->SetText("");
		m_pFifthResultDotOneth->SetText("");

		m_pSixthResultMinTenth->SetText("");
		m_pSixthResultMinOneth->SetText("");
		m_pSixthResultMinColon->SetText("Retired");
		m_pSixthResultSecTenth->SetText("");
		m_pSixthResultSecOneth->SetText("");
		m_pSixthResultSecColon->SetText("");
		m_pSixthResultDotMilth->SetText("");
		m_pSixthResultDotTenth->SetText("");
		m_pSixthResultDotOneth->SetText("");
	}
	// 2
	else if (m_pCar->GetCurRank() == 2)
	{
		m_pSndResultMinTenth->SetText(SndResultMinTenth);
		m_pSndResultMinOneth->SetText(SndResultMinOneth);
		m_pSndResultMinColon->SetText(":");
		m_pSndResultSecTenth->SetText(SndResultSecTenth);
		m_pSndResultSecOneth->SetText(SndResultSecOneth);
		m_pSndResultSecColon->SetText(":");
		m_pSndResultDotMilth->SetText(SndResultDotMilth);
		m_pSndResultDotTenth->SetText(SndResultDotTenth);
		m_pSndResultDotOneth->SetText(SndResultDotOneth);

		m_pTrdResultMinTenth->SetText("");
		m_pTrdResultMinOneth->SetText("");
		m_pTrdResultMinColon->SetText("Retired");
		m_pTrdResultSecTenth->SetText("");
		m_pTrdResultSecOneth->SetText("");
		m_pTrdResultSecColon->SetText("");
		m_pTrdResultDotMilth->SetText("");
		m_pTrdResultDotTenth->SetText("");
		m_pTrdResultDotOneth->SetText("");

		m_pFourthResultMinTenth->SetText("");
		m_pFourthResultMinOneth->SetText("");
		m_pFourthResultMinColon->SetText("Retired");
		m_pFourthResultSecTenth->SetText("");
		m_pFourthResultSecOneth->SetText("");
		m_pFourthResultSecColon->SetText("");
		m_pFourthResultDotMilth->SetText("");
		m_pFourthResultDotTenth->SetText("");
		m_pFourthResultDotOneth->SetText("");

		m_pFifthResultMinTenth->SetText("");
		m_pFifthResultMinOneth->SetText("");
		m_pFifthResultMinColon->SetText("Retired");
		m_pFifthResultSecTenth->SetText("");
		m_pFifthResultSecOneth->SetText("");
		m_pFifthResultSecColon->SetText("");
		m_pFifthResultDotMilth->SetText("");
		m_pFifthResultDotTenth->SetText("");
		m_pFifthResultDotOneth->SetText("");

		m_pSixthResultMinTenth->SetText("");
		m_pSixthResultMinOneth->SetText("");
		m_pSixthResultMinColon->SetText("Retired");
		m_pSixthResultSecTenth->SetText("");
		m_pSixthResultSecOneth->SetText("");
		m_pSixthResultSecColon->SetText("");
		m_pSixthResultDotMilth->SetText("");
		m_pSixthResultDotTenth->SetText("");
		m_pSixthResultDotOneth->SetText("");
	}
	// 3
	else if (m_pCar->GetCurRank() == 3)
	{
		m_pSndResultMinTenth->SetText(SndResultMinTenth);
		m_pSndResultMinOneth->SetText(SndResultMinOneth);
		m_pSndResultMinColon->SetText(":");
		m_pSndResultSecTenth->SetText(SndResultSecTenth);
		m_pSndResultSecOneth->SetText(SndResultSecOneth);
		m_pSndResultSecColon->SetText(":");
		m_pSndResultDotMilth->SetText(SndResultDotMilth);
		m_pSndResultDotTenth->SetText(SndResultDotTenth);
		m_pSndResultDotOneth->SetText(SndResultDotOneth);

		m_pTrdResultMinTenth->SetText(TrdResultMinTenth);
		m_pTrdResultMinOneth->SetText(TrdResultMinOneth);
		m_pTrdResultMinColon->SetText(":");
		m_pTrdResultSecTenth->SetText(TrdResultSecTenth);
		m_pTrdResultSecOneth->SetText(TrdResultSecOneth);
		m_pTrdResultSecColon->SetText(":");
		m_pTrdResultDotMilth->SetText(TrdResultDotMilth);
		m_pTrdResultDotTenth->SetText(TrdResultDotTenth);
		m_pTrdResultDotOneth->SetText(TrdResultDotOneth);

		m_pFourthResultMinTenth->SetText("");
		m_pFourthResultMinOneth->SetText("");
		m_pFourthResultMinColon->SetText("Retired");
		m_pFourthResultSecTenth->SetText("");
		m_pFourthResultSecOneth->SetText("");
		m_pFourthResultSecColon->SetText("");
		m_pFourthResultDotMilth->SetText("");
		m_pFourthResultDotTenth->SetText("");
		m_pFourthResultDotOneth->SetText("");

		m_pFifthResultMinTenth->SetText("");
		m_pFifthResultMinOneth->SetText("");
		m_pFifthResultMinColon->SetText("Retired");
		m_pFifthResultSecTenth->SetText("");
		m_pFifthResultSecOneth->SetText("");
		m_pFifthResultSecColon->SetText("");
		m_pFifthResultDotMilth->SetText("");
		m_pFifthResultDotTenth->SetText("");
		m_pFifthResultDotOneth->SetText("");

		m_pSixthResultMinTenth->SetText("");
		m_pSixthResultMinOneth->SetText("");
		m_pSixthResultMinColon->SetText("Retired");
		m_pSixthResultSecTenth->SetText("");
		m_pSixthResultSecOneth->SetText("");
		m_pSixthResultSecColon->SetText("");
		m_pSixthResultDotMilth->SetText("");
		m_pSixthResultDotTenth->SetText("");
		m_pSixthResultDotOneth->SetText("");
	}
	// 4
	else if (m_pCar->GetCurRank() == 4)
	{
		m_pSndResultMinTenth->SetText(SndResultMinTenth);
		m_pSndResultMinOneth->SetText(SndResultMinOneth);
		m_pSndResultMinColon->SetText(":");
		m_pSndResultSecTenth->SetText(SndResultSecTenth);
		m_pSndResultSecOneth->SetText(SndResultSecOneth);
		m_pSndResultSecColon->SetText(":");
		m_pSndResultDotMilth->SetText(SndResultDotMilth);
		m_pSndResultDotTenth->SetText(SndResultDotTenth);
		m_pSndResultDotOneth->SetText(SndResultDotOneth);

		m_pTrdResultMinTenth->SetText(TrdResultMinTenth);
		m_pTrdResultMinOneth->SetText(TrdResultMinOneth);
		m_pTrdResultMinColon->SetText(":");
		m_pTrdResultSecTenth->SetText(TrdResultSecTenth);
		m_pTrdResultSecOneth->SetText(TrdResultSecOneth);
		m_pTrdResultSecColon->SetText(":");
		m_pTrdResultDotMilth->SetText(TrdResultDotMilth);
		m_pTrdResultDotTenth->SetText(TrdResultDotTenth);
		m_pTrdResultDotOneth->SetText(TrdResultDotOneth);

		m_pFourthResultMinTenth->SetText(FourthResultMinTenth);
		m_pFourthResultMinOneth->SetText(FourthResultMinOneth);
		m_pFourthResultMinColon->SetText(":");
		m_pFourthResultSecTenth->SetText(FourthResultSecTenth);
		m_pFourthResultSecOneth->SetText(FourthResultSecOneth);
		m_pFourthResultSecColon->SetText(":");
		m_pFourthResultDotMilth->SetText(FourthResultDotMilth);
		m_pFourthResultDotTenth->SetText(FourthResultDotTenth);
		m_pFourthResultDotOneth->SetText(FourthResultDotOneth);

		m_pFifthResultMinTenth->SetText("");
		m_pFifthResultMinOneth->SetText("");
		m_pFifthResultMinColon->SetText("Retired");
		m_pFifthResultSecTenth->SetText("");
		m_pFifthResultSecOneth->SetText("");
		m_pFifthResultSecColon->SetText("");
		m_pFifthResultDotMilth->SetText("");
		m_pFifthResultDotTenth->SetText("");
		m_pFifthResultDotOneth->SetText("");

		m_pSixthResultMinTenth->SetText("");
		m_pSixthResultMinOneth->SetText("");
		m_pSixthResultMinColon->SetText("Retired");
		m_pSixthResultSecTenth->SetText("");
		m_pSixthResultSecOneth->SetText("");
		m_pSixthResultSecColon->SetText("");
		m_pSixthResultDotMilth->SetText("");
		m_pSixthResultDotTenth->SetText("");
		m_pSixthResultDotOneth->SetText("");
	}
	// 5
	else if (m_pCar->GetCurRank() == 5)
	{
		m_pSndResultMinTenth->SetText(SndResultMinTenth);
		m_pSndResultMinOneth->SetText(SndResultMinOneth);
		m_pSndResultMinColon->SetText(":");
		m_pSndResultSecTenth->SetText(SndResultSecTenth);
		m_pSndResultSecOneth->SetText(SndResultSecOneth);
		m_pSndResultSecColon->SetText(":");
		m_pSndResultDotMilth->SetText(SndResultDotMilth);
		m_pSndResultDotTenth->SetText(SndResultDotTenth);
		m_pSndResultDotOneth->SetText(SndResultDotOneth);

		m_pTrdResultMinTenth->SetText(TrdResultMinTenth);
		m_pTrdResultMinOneth->SetText(TrdResultMinOneth);
		m_pTrdResultMinColon->SetText(":");
		m_pTrdResultSecTenth->SetText(TrdResultSecTenth);
		m_pTrdResultSecOneth->SetText(TrdResultSecOneth);
		m_pTrdResultSecColon->SetText(":");
		m_pTrdResultDotMilth->SetText(TrdResultDotMilth);
		m_pTrdResultDotTenth->SetText(TrdResultDotTenth);
		m_pTrdResultDotOneth->SetText(TrdResultDotOneth);

		m_pFourthResultMinTenth->SetText(FourthResultMinTenth);
		m_pFourthResultMinOneth->SetText(FourthResultMinOneth);
		m_pFourthResultMinColon->SetText(":");
		m_pFourthResultSecTenth->SetText(FourthResultSecTenth);
		m_pFourthResultSecOneth->SetText(FourthResultSecOneth);
		m_pFourthResultSecColon->SetText(":");
		m_pFourthResultDotMilth->SetText(FourthResultDotMilth);
		m_pFourthResultDotTenth->SetText(FourthResultDotTenth);
		m_pFourthResultDotOneth->SetText(FourthResultDotOneth);

		m_pFifthResultMinTenth->SetText(FifthResultMinTenth);
		m_pFifthResultMinOneth->SetText(FifthResultMinOneth);
		m_pFifthResultMinColon->SetText(":");
		m_pFifthResultSecTenth->SetText(FifthResultSecTenth);
		m_pFifthResultSecOneth->SetText(FifthResultSecOneth);
		m_pFifthResultSecColon->SetText(":");
		m_pFifthResultDotMilth->SetText(FifthResultDotMilth);
		m_pFifthResultDotTenth->SetText(FifthResultDotTenth);
		m_pFifthResultDotOneth->SetText(FifthResultDotOneth);

		m_pSixthResultMinTenth->SetText("");
		m_pSixthResultMinOneth->SetText("");
		m_pSixthResultMinColon->SetText("Retired");
		m_pSixthResultSecTenth->SetText("");
		m_pSixthResultSecOneth->SetText("");
		m_pSixthResultSecColon->SetText("");
		m_pSixthResultDotMilth->SetText("");
		m_pSixthResultDotTenth->SetText("");
		m_pSixthResultDotOneth->SetText("");
	}
	// 6
	else if (m_pCar->GetCurRank() == 6)
	{
		m_pSndResultMinTenth->SetText(SndResultMinTenth);
		m_pSndResultMinOneth->SetText(SndResultMinOneth);
		m_pSndResultMinColon->SetText(":");
		m_pSndResultSecTenth->SetText(SndResultSecTenth);
		m_pSndResultSecOneth->SetText(SndResultSecOneth);
		m_pSndResultSecColon->SetText(":");
		m_pSndResultDotMilth->SetText(SndResultDotMilth);
		m_pSndResultDotTenth->SetText(SndResultDotTenth);
		m_pSndResultDotOneth->SetText(SndResultDotOneth);

		m_pTrdResultMinTenth->SetText(TrdResultMinTenth);
		m_pTrdResultMinOneth->SetText(TrdResultMinOneth);
		m_pTrdResultMinColon->SetText(":");
		m_pTrdResultSecTenth->SetText(TrdResultSecTenth);
		m_pTrdResultSecOneth->SetText(TrdResultSecOneth);
		m_pTrdResultSecColon->SetText(":");
		m_pTrdResultDotMilth->SetText(TrdResultDotMilth);
		m_pTrdResultDotTenth->SetText(TrdResultDotTenth);
		m_pTrdResultDotOneth->SetText(TrdResultDotOneth);

		m_pFourthResultMinTenth->SetText(FourthResultMinTenth);
		m_pFourthResultMinOneth->SetText(FourthResultMinOneth);
		m_pFourthResultMinColon->SetText(":");
		m_pFourthResultSecTenth->SetText(FourthResultSecTenth);
		m_pFourthResultSecOneth->SetText(FourthResultSecOneth);
		m_pFourthResultSecColon->SetText(":");
		m_pFourthResultDotMilth->SetText(FourthResultDotMilth);
		m_pFourthResultDotTenth->SetText(FourthResultDotTenth);
		m_pFourthResultDotOneth->SetText(FourthResultDotOneth);

		m_pFifthResultMinTenth->SetText(FifthResultMinTenth);
		m_pFifthResultMinOneth->SetText(FifthResultMinOneth);
		m_pFifthResultMinColon->SetText(":");
		m_pFifthResultSecTenth->SetText(FifthResultSecTenth);
		m_pFifthResultSecOneth->SetText(FifthResultSecOneth);
		m_pFifthResultSecColon->SetText(":");
		m_pFifthResultDotMilth->SetText(FifthResultDotMilth);
		m_pFifthResultDotTenth->SetText(FifthResultDotTenth);
		m_pFifthResultDotOneth->SetText(FifthResultDotOneth);

		m_pSixthResultMinTenth->SetText(SixthResultMinTenth);
		m_pSixthResultMinOneth->SetText(SixthResultMinOneth);
		m_pSixthResultMinColon->SetText(":");
		m_pSixthResultSecTenth->SetText(SixthResultSecTenth);
		m_pSixthResultSecOneth->SetText(SixthResultSecOneth);
		m_pSixthResultSecColon->SetText(":");
		m_pSixthResultDotMilth->SetText(SixthResultDotMilth);
		m_pSixthResultDotTenth->SetText(SixthResultDotTenth);
		m_pSixthResultDotOneth->SetText(SixthResultDotOneth);
	}
}

void InGameUI::LinkCarPt(cCar * car)
{
	m_pCar = car;
}
