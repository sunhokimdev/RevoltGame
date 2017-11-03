#pragma once

#include "cImpact.h"

class GravityBallImpact : public cImpact
{
private:
	D3DXMATRIXA16	m_matWorld;
	D3DXVECTOR3 m_itemPos;
	std::vector<ST_PC_VERTEX>m_vecParticleVertex;
public:
	GravityBallImpact();
	virtual ~GravityBallImpact();

	virtual void Setup();
	virtual void Update();
	virtual void Render();
};

