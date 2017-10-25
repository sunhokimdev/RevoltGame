#include "stdafx.h"
#include "CarBox.h"
#include "CarTextLoader.h"
#include "Car.h"

std::vector<ST_CAR> CarBox::g_vecCar;
int* CarBox::g_select;

CarBox::CarBox()
	: m_prevLobby(SELECT_CAR_LOBBY)
{
}

CarBox::~CarBox()
{
	SAFE_RELEASE(m_carboxTexture);
	SAFE_RELEASE(VB);

	SAFE_DELETE(m_car);
	SAFE_DELETE(g_select);
	g_vecCar.clear();
}

void CarBox::Setup()
{
}

void CarBox::Update()
{
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_matR);
	D3DXMatrixIdentity(&m_matRX);
	D3DXMatrixIdentity(&m_matRY);
	D3DXMatrixIdentity(&m_matR);
	D3DXMatrixIdentity(&m_matT);

	if (*g_LobbyState == SELECT_CAR_LOBBY)
	{
		if (m_prevLobby != *g_LobbyState)
		{
			m_prevLobby = *g_LobbyState;
			m_vPosition = m_vTarget;
		}

		if (m_index == *g_select)
		{
			if (m_vPosition.y < m_vTarget.y)
			{
				D3DXVECTOR3 tempV = (m_vTarget - m_vPrevPosition) / 30.0f;
				m_vPosition += tempV;
			}

			else if (m_vTarget.y >= m_vPosition.y)
			{
				m_vPosition = m_vTarget;
			}

			D3DXMatrixRotationX(&m_matRX, D3DX_PI / 4.0f);
			m_yAngle = D3DX_PI / 3.7f;
		}
		else
		{
			if (m_vPosition != m_vPrevPosition)
			{
				m_vPosition += (m_vPrevPosition - m_vTarget) / 40.0f;
			}

			m_vPosition = m_vPrevPosition;
			m_yAngle = m_prevYAngle;
			D3DXMatrixRotationX(&m_matRX, 0.0f);
		}
	}

	else if (*g_LobbyState == VIEW_CAR_LOBBY)
	{
		if (*g_select == m_index)
		{
			D3DXMatrixRotationX(&m_matRX, D3DX_PI / 2.0f);
			m_vPosition.y = 0.1f;
			m_vPosition.x = 14.0f;
			m_vPosition.z = 9.0f;
		}
	}

	else if (*g_LobbyState == SELECT_MAP_LOBBY)
	{
		m_vPosition = m_vPrevPosition;
		m_yAngle = m_prevYAngle;
	}

	m_car->Update();

	Thing::Update();

	m_prevLobby = *g_LobbyState;
}

void CarBox::Render()
{
	if (*g_select == m_index && *g_LobbyState == VIEW_CAR_LOBBY)
	{
		D3DXMatrixRotationX(&m_matWorld, 0.0f);
		D3DXMatrixRotationY(&m_matWorld, m_prevYAngle);

		m_matWorld._41 = m_vPrevPosition.x;
		m_matWorld._42 = m_vPrevPosition.y;
		m_matWorld._43 = m_vPrevPosition.z;

		m_car->Render();
	}

	Thing::Render();

	/*   자동차 표지 그리기   */
	g_pD3DDevice->SetStreamSource(0, VB, 0, sizeof(ST_PNT_VERTEX));
	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	g_pD3DDevice->SetTexture(0, m_carboxTexture);
	g_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
}

void CarBox::SetTextFile(char * szFolder)
{
	ST_CAR tCar;
	CarTextLoader loader;

	std::string str = std::string(szFolder) + std::string("/") + std::string("Parameters.txt");

	/*   자동차 정보를 읽어온다.   */
	loader.Load(tCar, str.c_str());
	g_vecCar.push_back(tCar);

	/*   박스 표지를 그리기 위한 버텍스 버퍼 생성    */
	g_pD3DDevice->CreateVertexBuffer(6 * sizeof(ST_PNT_VERTEX), D3DUSAGE_WRITEONLY, ST_PC_VERTEX::FVF, D3DPOOL_MANAGED, &VB, 0);

	float zSize = -1.1f;
	float xSize = 0.0f;
	float ySize = 0.0f;

	/*   자동차 박스에서 자동차를 불러들이기 위한 변수   */
	m_car = new Car;
	m_car->SetPosition(14.0f, 0.1f, 9.0f);
	m_car->SetRotationY(-D3DX_PI / 3.7f);

	ST_PNT_VERTEX* vertices;
	VB->Lock(0, 0, (void**)&vertices, 0);

	/*   박스 표지 그리기 위한 변수   */
	if (str.find("tc1") != -1)
	{
		m_carboxTexture = g_pTextureManager->GetTexture("Maps/Front/carbox/carbox3.png");
		m_car->SetSTCar(tCar);
		m_car->SetMesh(szFolder, "tc1.obj");
		m_car->SetMeshWheel(szFolder, "tc1");

		xSize = 0.0f;
		ySize = 0.33333f;
	}
	else if (str.find("tc2") != -1)
	{
		m_carboxTexture = g_pTextureManager->GetTexture("Maps/Front/carbox/carbox2.png");
		m_car->SetMesh(szFolder, "tc2.obj");
		m_car->SetSTCar(tCar);
		m_car->SetMeshWheel(szFolder, "tc2");

		xSize = 0.66666f;
		ySize = 0.33333f;
	}
	else if (str.find("tc3") != -1)
	{
		m_carboxTexture = g_pTextureManager->GetTexture("Maps/Front/carbox/carbox3.png");
		m_car->SetMesh(szFolder, "tc3.obj");
		m_car->SetSTCar(tCar);
		m_car->SetMeshWheel(szFolder, "tc3");

		xSize = 0.0f;
		ySize = 0.0f;
	}
	else if (str.find("tc4") != -1)
	{
		m_carboxTexture = g_pTextureManager->GetTexture("Maps/Front/carbox/carbox2.png");
		m_car->SetMesh(szFolder, "tc4.obj");
		m_car->SetSTCar(tCar);
		m_car->SetMeshWheel(szFolder, "tc4");

		xSize = 0.66666f;
		ySize = 0.0f;
	}
	else if (str.find("tc5") != -1)
	{
		m_carboxTexture = g_pTextureManager->GetTexture("Maps/Front/carbox/carbox2.png");
		m_car->SetMesh(szFolder, "tc5.obj");
		m_car->SetSTCar(tCar);
		m_car->SetMeshWheel(szFolder, "tc5");

		xSize = 0.33333f;
		ySize = 0.66666f;
	}
	else if (str.find("tc6") != -1)
	{
		m_carboxTexture = g_pTextureManager->GetTexture("Maps/Front/carbox/carbox1.png");
		m_car->SetMesh(szFolder, "tc6.obj");
		m_car->SetSTCar(tCar);
		m_car->SetMeshWheel(szFolder, "tc6");

		xSize = 0.33333f;
		ySize = 0.66666f;
	}
	else if (str.find("toyeca") != -1)
	{
		m_carboxTexture = g_pTextureManager->GetTexture("Maps/Front/carbox/carbox3.png");
		m_car->SetMesh(szFolder, "toyeca.obj");
		m_car->SetSTCar(tCar);
		m_car->SetMeshWheel(szFolder, "toyeca");

		xSize = 0.33333f;
		ySize = 0.66666f;
	}
	else if (str.find("volken") != -1)
	{
		m_carboxTexture = g_pTextureManager->GetTexture("Maps/Front/carbox/carbox1.png");
		m_car->SetMesh(szFolder, "volken.obj");
		m_car->SetSTCar(tCar);
		m_car->SetMeshWheel(szFolder, "volken");

		xSize = 0.00000f;
		ySize = 0.66666f;
	}
	vertices[0].p = D3DXVECTOR3(-0.3831, 0.3831, zSize);
	vertices[0].t = D3DXVECTOR2(xSize, ySize);

	vertices[1].p = D3DXVECTOR3(0.8000, 0.3831, zSize);
	vertices[1].t = D3DXVECTOR2(xSize + 0.33333f, ySize);

	vertices[2].p = D3DXVECTOR3(-0.3831, -0.6831, zSize);
	vertices[2].t = D3DXVECTOR2(xSize, ySize + 0.33333f);

	vertices[3].p = D3DXVECTOR3(-0.3831, -0.6831, zSize);
	vertices[3].t = D3DXVECTOR2(xSize, ySize + 0.33333f);

	vertices[4].p = D3DXVECTOR3(0.8000, 0.3831, zSize);
	vertices[4].t = D3DXVECTOR2(xSize + 0.33333f, ySize);

	vertices[5].p = D3DXVECTOR3(0.8000, -0.6831, zSize);
	vertices[5].t = D3DXVECTOR2(xSize + 0.33333f, ySize + 0.33333f);
	VB->Unlock();

	Thing::SetMesh("Maps/Front/carbox", "carbox.obj");
}

void CarBox::SetIndex(int index)
{
	m_index = index;
}
