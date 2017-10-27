#include "stdafx.h"
#include "ProfileList.h"

#include "UserFileLoader.h"
#include "UIImageView.h"
#include "UITextImageView.h"

ProfileList::ProfileList()
{
}


ProfileList::~ProfileList()
{
}

void ProfileList::ListLoad()
{
	UserFileLoader*	pProfileLoader = new UserFileLoader;
	m_vProfileList = pProfileLoader->LoadProfileList();
}

UIImageView* ProfileList::GetProfileList()
{
	ListLoad();

	UIImageView* pImageView4 = new UIImageView;
	pImageView4->SetPosition(40, 40);
	pImageView4->SetXSize(4.0f);
	pImageView4->SetYSize(4.0f);
	pImageView4->SetIsBoard(true);
	pImageView4->SetTexture("Maps/Front/Image/blueRing.png");

	UIImageView* pImageView5 = new UIImageView;
	pImageView5->SetPosition(120, 20);
	pImageView5->SetXSize(24.0f);
	pImageView5->SetYSize(1.2f);
	pImageView5->SetIsBoard(true);
	pImageView5->SetTexture("Maps/Front/Image/ring.png");

	UITextImageView* pImageView6 = new UITextImageView;
	pImageView6->SetIndex(INT_MAX);
	pImageView6->SetPosition(150, 40);
	pImageView6->SetXSize(1.5f);
	pImageView6->SetYSize(1.5f);
	pImageView6->SetText("SELECT PROFILE");
	pImageView6->SetTexture("Maps/Front/Image/font1.png");

	UIImageView* pImageView7 = new UIImageView;
	pImageView7->SetPosition(18, 18);
	pImageView7->SetXSize(1.2f);
	pImageView7->SetYSize(1.2f);
	pImageView7->SetTexture("Maps/Front/Image/blueflag.png");

	UIImageView* pImageView8 = new UIImageView;
	pImageView8->SetPosition(350, 180);
	pImageView8->SetXSize(15.0f);
	pImageView8->SetYSize(1.2f);
	pImageView8->SetIsBoard(true);
	pImageView8->SetTexture("Maps/Front/Image/ring.png");

	UITextImageView* pImageView9 = new UITextImageView;
	pImageView9->SetPosition(90, 25);
	pImageView9->SetIndex(INT_MAX);
	pImageView9->SetIsVectorText(true);
	pImageView9->SetAddText("Load Profile");
	pImageView9->SetAddText("Create Profile");
	pImageView9->SetAddText("Delete Profile");
	pImageView9->SetXSize(1.0f);
	pImageView9->SetYSize(1.0f);
	pImageView9->SetColor(D3DCOLOR_ARGB(255, 242, 150, 97));
	pImageView9->SetTexture("Maps/Front/Image/font2.png");

	UIImageView* pImageView10 = new UIImageView;
	pImageView10->SetPosition(220, 22);
	pImageView10->SetXSize(1.5f);
	pImageView10->SetYSize(1.5f);
	pImageView10->SetTexture("Maps/Front/Image/arrowright.png");

	UIImageView* pImageView11 = new UIImageView;
	pImageView11->SetPosition(30, 22);
	pImageView11->SetXSize(1.5f);
	pImageView11->SetYSize(1.5f);
	pImageView11->SetTexture("Maps/Front/Image/arrowleft.png");

	UIImageView* pImageView12 = new UIImageView;
	pImageView12->SetPosition(50, 100);
	pImageView12->SetIsBoard(true);
	pImageView12->SetXSize(8.0f);
	pImageView12->SetYSize(12.0f);
	pImageView12->SetTexture("Maps/Front/Image/ring.png");

	UIImageView* pImageView13 = new UIImageView;
	pImageView13->SetPosition(70, 10);
	pImageView13->SetXSize(1.5f);
	pImageView13->SetYSize(1.5f);
	pImageView13->SetTexture("Maps/Front/Image/arrowup.png");

	UIImageView* pImageView14 = new UIImageView;
	pImageView14->SetPosition(70, 190);
	pImageView14->SetXSize(1.5f);
	pImageView14->SetYSize(1.5f);
	pImageView14->SetTexture("Maps/Front/Image/arrowdown.png");

	UITextImageView* pImageViewProfileList = new UITextImageView;
	pImageViewProfileList->SetPosition(50, 100);
	pImageViewProfileList->SetIndex(INT_MAX);
	pImageViewProfileList->SetIsVectorText2(true);
	for (int i = 0; i < m_vProfileList.size(); i++)
		pImageViewProfileList->SetAddText(m_vProfileList[i].c_str());
	pImageViewProfileList->SetXSize(1.0f);
	pImageViewProfileList->SetYSize(1.0f);
	pImageViewProfileList->SetColor(D3DCOLOR_ARGB(255, 100, 200, 150));
	pImageViewProfileList->SetTexture("Maps/Front/Image/font2.png");

	pImageView4->AddChild(pImageView5);
	pImageView4->AddChild(pImageView6);
	pImageView4->AddChild(pImageView7);
	pImageView4->AddChild(pImageView8);
	pImageView8->AddChild(pImageView9);
	pImageView8->AddChild(pImageView10);
	pImageView8->AddChild(pImageView11);
	pImageView8->AddChild(pImageView12);
	pImageView12->AddChild(pImageView13);
	pImageView12->AddChild(pImageView14);
	pImageView12->AddChild(pImageViewProfileList);

	return pImageView4;
}

