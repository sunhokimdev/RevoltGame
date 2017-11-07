#include "stdafx.h"
#include "c321GO.h"
#include "Object.h"

c321GO::c321GO()
{
}

c321GO::~c321GO()
{
}

void c321GO::Setup()
{
	Object* gogo = new Object;
	gogo->GetMeshData()->LoadMesh("Objects/gogo", "gogo.obj");
	m_vec321go.push_back(gogo);

	Object* go1 = new Object;
	go1->GetMeshData()->LoadMesh("Objects/go1", "go1.obj");
	m_vec321go.push_back(go1);

	Object* go2 = new Object;
	go2->GetMeshData()->LoadMesh("Objects/go2", "go2.obj");
	m_vec321go.push_back(go2);

	Object* go3 = new Object;
	go3->GetMeshData()->LoadMesh("Objects/go3", "go3.obj");
	m_vec321go.push_back(go3);

	m_fAngle = 0;
	m_nCount = 3;
	m_fTime = 0;
	m_isStart = false;
	m_fAngleRatio = 0.f;
}

void c321GO::Update()
{
	//매쉬 방향은 Y가 PI일때 정면


	m_fAngle = (m_fTime * D3DX_PI);
	if (g_pKeyManager->isOnceKeyDown('S'))
	{
		StartCount();
	}

	if (m_isStart)
	{
		m_fTime += g_pTimeManager->GetElapsedTime();
		
		if (m_fTime > 1.5f)
		{
			if (m_nCount != 0)
			{
				m_nCount--;
			}
			else
			{
				m_isStart = false;
			}
			m_fTime = 0.5f;
		}
	}

	float distToCam = 1.5f;
	float size = 0.5f;

	D3DXVECTOR3 camPos = *g_pCamManager->GetCamPos();
	D3DXVECTOR3 camLook = *g_pCamManager->GetLookAt();
	camLook.y += 1;

	D3DXVECTOR3 direc = camPos - camLook;
	D3DXVec3Normalize(&direc, &direc);
	D3DXVECTOR3 pos = camPos - (direc * distToCam);

	D3DXMATRIXA16 mat, matS, matR, matRY,matRX,matRZ, matT;
	D3DXMatrixIdentity(&mat);
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixIdentity(&matT);
	D3DXMatrixIdentity(&matRX);
	D3DXMatrixIdentity(&matRY);
	D3DXMatrixIdentity(&matRZ);

	D3DXMatrixRotationY(&matRY, m_fAngle);
	D3DXMatrixRotationX(&matRX, D3DX_PI);
	D3DXMatrixRotationZ(&matRZ, 0);
	matR = matRY * matRZ;

	D3DXMatrixTranslation(&matT, pos.x, pos.y, pos.z);
	
	mat = matR * matT;

	D3DXVec3TransformNormal(&direc, &direc, &mat);
	
	m_vec321go[m_nCount]->SetPosition(pos);
	m_vec321go[m_nCount]->SetQuaternion(direc);
	m_vec321go[m_nCount]->SetSize({ size, size, size });

	/*for (int i = 0; i < m_vec321go.size(); i++)
	{
		m_vec321go[i]->SetPosition(camLook.x, camLook.y + 1,camLook.z);
		m_vec321go[i]->SetQuaternion(direc);
	}*/
}

void c321GO::Render()
{
	m_vec321go[m_nCount]->Render();
}

void c321GO::Destroy()
{
	for each(Object* p in m_vec321go)
	{
		p->GetMeshData()->m_pMesh->Release();
		SAFE_DELETE(p);
	}
	m_vec321go.clear();
}

void c321GO::StartCount()
{
	m_isStart = true;
	m_fAngle = 0;
	m_nCount = 3;
	m_fTime = 0.5f;
}
