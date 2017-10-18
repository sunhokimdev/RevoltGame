#include "stdafx.h"
#include "ObjectMap.h"
#include "ObjectLoader.h"

ObjectMap::ObjectMap(IN char * szFolder, IN char * szFile, IN D3DXMATRIXA16 * pmat)
{
	Load(szFolder, szFile, pmat);
}

ObjectMap::~ObjectMap()
{
}

void ObjectMap::Load(IN char * szFolder, IN char * szFile, IN D3DXMATRIXA16 * pmat)
{
	ObjectLoader loader;
	loader.LoadSurface(m_vecSurface, szFolder,
		szFile, pmat);
}

bool ObjectMap::GetHeight(IN float x, OUT float & y, IN float z)
{
	D3DXVECTOR3 vRayPos(x, 1000.0f, z);
	D3DXVECTOR3 vRayDir(0, -1, 0);

	for (size_t i = 0; i < m_vecSurface.size(); i += 3)
	{
		float u, v, f;
		if (D3DXIntersectTri(
			&m_vecSurface[i + 0],
			&m_vecSurface[i + 1],
			&m_vecSurface[i + 2],
			&vRayPos,
			&vRayDir,
			&u, &v,
			&f)
			)
		{
			y = 1000.0f - f;
			return true;
		}
	}
	return false;
}
