#include "stdafx.h"
#include "cViewCarLob.h"
#include "UIImageView.h"
#include "UITextImageView.h"

cViewCarLob::cViewCarLob()
	: m_isNetwork(false)
{
}


cViewCarLob::~cViewCarLob()
{
}

void cViewCarLob::Setup()
{
	iLobby::Setup();

	pImageView1 = new UIImageView;	
	pImageView1->SetPosition(80, 50);
	pImageView1->SetXSize(4.0f);
	pImageView1->SetYSize(4.0f);
	pImageView1->SetIsBoard(true);
	pImageView1->SetTexture("UIImage/blueRing.png");

	pImageView2 = new UIImageView;
	pImageView2->SetXSize(1.2f);
	pImageView2->SetYSize(1.2f);
	pImageView2->SetPosition(17, 17);
	pImageView2->SetTexture("UIImage/bluecar.png");

	pImageView3 = new UIImageView;
	pImageView3->SetPosition(120, 25);
	pImageView3->SetIsBoard(true);
	pImageView3->SetXSize(20.0f);
	pImageView3->SetYSize(1.0f);
	pImageView3->SetTexture("UIImage/ring.png");

	pImageView4 = new UITextImageView;
	pImageView4->SetTexture("UIImage/font1.png");
	pImageView4->SetText("SELECT CAR");
	pImageView4->SetIndex(INT_MAX);
	pImageView4->SetXSize(1.5f);
	pImageView4->SetYSize(1.5f);
	pImageView4->SetPosition(180, 45);

	m_pRootUI->AddChild(pImageView1);
	pImageView1->AddChild(pImageView2);
	pImageView1->AddChild(pImageView3);
	pImageView1->AddChild(pImageView4);
}

void cViewCarLob::Update()
{
	iLobby::Update();
}

void cViewCarLob::Render(LPD3DXSPRITE pSprite)
{
	iLobby::Render(pSprite);
}

void cViewCarLob::Destroy()
{
	SAFE_DELETE(pImageView1);
	SAFE_DELETE(pImageView2);
	SAFE_DELETE(pImageView3);
	SAFE_DELETE(pImageView4);

	iLobby::Destroy();
}
