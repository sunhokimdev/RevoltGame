#pragma once
#include <d3dx9.h>


struct ST_SIZE
{
	int nWitdh;
	int nHeight;
	ST_SIZE() : nWitdh(0), nHeight(0) {}
	ST_SIZE(int _nWidth, int _nHeight)
		: nWitdh(_nWidth), nHeight(_nHeight) {}
};

struct ST_PC_VERTEX
{
	D3DXVECTOR3  p;
	D3DCOLOR	c;
	enum { FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE };
};

struct ST_PN_VERTEX
{
	D3DXVECTOR3  p;
	D3DXVECTOR3  n;
	enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL };
};

struct ST_PNT_VERTEX
{
	D3DXVECTOR3  p;
	D3DXVECTOR3  n;
	D3DXVECTOR2  t;
	enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 };
};

struct ST_PT_VERTEX
{
	D3DXVECTOR3  p;
	D3DXVECTOR2  t;
	enum { FVF = D3DFVF_XYZ | D3DFVF_TEX1 };
};

struct ST_RHWC_VERTEX
{
	D3DXVECTOR4  p;
	D3DCOLOR	c;
	enum { FVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE };
};

struct ST_POS_SAMPLE
{
	int			n;
	D3DXVECTOR3	v;
	ST_POS_SAMPLE() : n(0), v(0, 0, 0) {}
};
struct ST_ROT_SAMPLE
{
	int			n;
	D3DXQUATERNION	q;
	ST_ROT_SAMPLE() : n(0)
	{
		D3DXQuaternionIdentity(&q);
	}
};

struct BoundingSphere
{
	D3DXVECTOR3 v;
	float radius;
	bool isPicking;
};

struct ST_SPHERE
{
	float				fRadius;
	D3DXVECTOR3 vCenter;
	bool				isPicked;
	ST_SPHERE() : fRadius(0.0f), vCenter(0, 0, 0), isPicked(false) { }
};

struct ST_ASTAR
{
	POINT wall;
	POINT path;
};