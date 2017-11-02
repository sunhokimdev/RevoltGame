#pragma once
#include "cAI.h"
#include "cPhysX.h"

class cAI_Collider :
	public cAI
{
public:
	cPhysX* pColl_Speed;
	cPhysX* pColl_01;
	cPhysX* pColl_02;
	cPhysX* pColl_03;
	cPhysX* pColl_04;
	cPhysX* pColl_05;


public:
	cAI_Collider();
	~cAI_Collider();

};

