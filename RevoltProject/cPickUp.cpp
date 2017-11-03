#include "stdafx.h"
#include "cPickUp.h"


cPickUp::cPickUp()
{
}


cPickUp::~cPickUp()
{
}

void cPickUp::Update()
{
	//if (GetPhysXData()->m_pUserData->IsPickUp == NX_FALSE)
	//{
	//	m_isExist = false;
	//}
	//else
	//{
	//	m_isExist = true;
	//}
	//m_isEnable 체크후
	//lightIndex를 이용해 라이트 온/오프
}

void cPickUp::Render()
{
	//if (m_isExist)
	//{
		Object::Render();
	//}
}
