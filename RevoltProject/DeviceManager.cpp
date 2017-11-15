#include "stdafx.h"
#include "DeviceManager.h"

DeviceManager::DeviceManager()
	: m_pD3D(NULL)
	, m_pD3DDevice(NULL)
{
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	D3DCAPS9   stCaps;
	int			nVertexProcessing;

	m_pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL, &stCaps);
	if (stCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		nVertexProcessing =
			D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}
	else
	{
		nVertexProcessing =
			D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}

	D3DPRESENT_PARAMETERS   stD3DPP;
	ZeroMemory(&stD3DPP, sizeof(D3DPRESENT_PARAMETERS));
	stD3DPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
	stD3DPP.Windowed = true;
	stD3DPP.BackBufferFormat = D3DFMT_UNKNOWN;
	stD3DPP.EnableAutoDepthStencil = TRUE;
	stD3DPP.AutoDepthStencilFormat = D3DFMT_D16;


	m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		g_hWnd,
		nVertexProcessing,
		&stD3DPP,
		&m_pD3DDevice);

	m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		g_hWnd,
		nVertexProcessing,
		&stD3DPP,
		&m_pD3DDevice2);

	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);


	//Texture
	//DWORD dwFactor = D3DCOLOR_RGBA(255, 255, 255, 255);
	//m_pD3DDevice->SetRenderState(D3DRS_TEXTUREFACTOR, dwFactor);
	////m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	//m_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	////아래 3줄이 알파블랜딩을 시작하겠다는 소스
	//m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	//m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//Maler
	// Use material's alpha
	m_pD3DDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

	// Use alpha for transparency
//	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
//	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
//	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

}


DeviceManager::~DeviceManager()
{
}

LPDIRECT3DDEVICE9 DeviceManager::GetDevice()
{
	return m_pD3DDevice;
}

void DeviceManager::Destroy()
{
	// : release
	SAFE_RELEASE(m_pD3D);
	ULONG UL = m_pD3DDevice->Release();
#ifdef _DEBUG 
	assert(UL == 0 && "디바이스를 이용 생성한 객체중 해제되지 않은 객체가 있습니다");
#endif
}