// RevoltProject.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "RevoltProject.h"
#include "MainGame.h"

HWND g_hWnd;
HINSTANCE g_hInst;
MainGame* g_mg;

LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if(g_mg)
		g_mg->MsgProc(hWnd, msg, wParam, lParam);

	switch (msg)
	{
		case WM_COMMAND:
		{
			int wmId = LOWORD(wParam);
			switch (wmId)
			{
				case IDM_EXIT:
				DestroyWindow(hWnd);
				break;

				default:
				return DefWindowProc(hWnd, msg, wParam, lParam);
			}
		}
		break;
		case WM_PAINT:
			{
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(hWnd, &ps);
				// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다.
				EndPaint(hWnd, &ps);
			}
		break;
		case WM_DESTROY:
			PostQuitMessage(0);
		break;

		default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}


int APIENTRY WINAPI wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	WNDCLASSEX wc = { 
		sizeof(WNDCLASSEX), 
		CS_CLASSDC, 
		MsgProc, 
		0L,0L,
		GetModuleHandle(NULL),
		NULL,NULL,NULL,NULL,
		L"Revolt",NULL };

	RegisterClassEx(&wc);

	HWND hWnd = CreateWindowW(L"Revolt", L"RevoltProject", WS_OVERLAPPEDWINDOW,
		0, 0, WINSIZEX, WINSIZEY, nullptr, nullptr, wc.hInstance, nullptr);

	if (!hWnd)
		return false;

	g_hWnd = hWnd;
	g_hInst = wc.hInstance;

	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);

	MSG msg;

	g_mg = new MainGame;
	g_mg->Setup();

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0,PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			g_mg->Update();
			g_mg->Render();
		}
	}

	delete g_mg;

	UnregisterClass(L"Revolt", wc.hInstance);
	return 0;
}
