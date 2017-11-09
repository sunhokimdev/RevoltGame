#pragma once

#include "targetver.h"
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console") 
//======================================
// - ## 10.11.17 ##
// - written by 김선호
// - 헤더파일 선언 및 쓸만한 기능함수 선언
// - using 선언 하지말 것 -> 이름충돌 발생할 수 있음
//======================================

//======================================
// - ## 헤더파일 선언 및 전역 변수
//======================================

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:

//======================================
// - written by 이건배
// - <windows.h>와 PhysX내부의 <nxmath.h> 에서 max 와 min을 중복으로 사용중이기에 오류가 발생을 방지하기 위한 매크로 설정
//======================================

#define NOMINMAX	// <windows.h>와 PhysX내부의 <nxmath.h> 에서 max 와 min을 중복으로 사용중이기에 오류가 발생한다.
#ifdef max				// 이를 위해 {#define NOMINMAX ~ } 를 이용해 중복사용을 막아준다. 
	#undef max		
#endif min			
	#undef min		
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

/*   C++ 헤더파일   */
#include <iostream>
#include <fstream>
#include <mmsystem.h>
#include <istream>

/*   STL 헤더파일   */
#include <vector>
#include <string>
#include <map>
#include <set>
#include <list>
#include <bitset>

/*   프로세스 관련 헤더파일   */
#include <assert.h>
#include <thread>
#include <process.h>

/*   다이렉트3D 관련 헤더파일   */
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

/*   PhysX관련 헤더파일 설정   */
#include <NxPhysics.h>
#include <NxPhysicsSDK.h>
#include <NxDebugRenderable.h>
#include <NxCooking.h>
#include <NxStream.h>
#include <NxUserContactReport.h>

/*   사운드 관련 헤더파일   */
#pragma comment (lib, "fmodlib/fmodex_vc.lib")
#include "fmodinc/fmod.hpp"

/*   윈도우가 실행중인 시간을 알려주는 라이부러리   */
#pragma comment(lib, "winmm.lib")

/*   네트워크 소켓 관련 라이브러리   */
#pragma comment(lib,"ws2_32.lib")
#include <WinSock2.h>

/*   전역변수 설정   */
extern HWND			g_hWnd;
extern HINSTANCE	g_hInst;
extern POINT		g_ptMouse;

/*   열거체 형 설정   */
/*   현재 로비상태를 저장하는 열거형 구조체   */

enum LOBBY {
	LOBBY_NONE = 1001
	, INTRO1
	, INTRO2
	, INTRO3
	, START_LOBBY
	, MAIN_LOBBY
	, MAIN_LOBBY2
	, MAIN_LOBBY3
	, MAIN_LOBBY4
	, CREATE_PROFILE_LOBBY
	, NETWORK_LOBBY
	, NETWORK_CREATE_LOBBY
	, NETWORK_IN_LOBBY
	, GAME_QUIT
	, SELECT_MAP_LOBBY
	, SELECT_CAR_LOBBY
	, VIEW_CAR_LOBBY
	, IN_GAME_MAP
	, MARKET_MAP
	, GARDEN_MAP
};
enum CAR_CLASS { CLASS_NONE, CAR_ELECTRIC, CAR_GLOW, CAR_OTHER };
enum CAR_RATING { RATING_NONE, RATING_ROOKIE, RATING_AMATEUR, RATING_SEMI_PRO, RATING_PRO };
enum MAP_TYPE { NONE = 0, SUPERMARKET, GARDEN, MUSEUM, SHIP };
enum FONTFILE{FONT1=2001, FONT2};
//======================================
// - ## 10.14.17 ##
// - written by 김선호
// - ## 매크로 함수 및 변수 ##
// - ## 전역적으로 사용할 구조체 선언
// - ## 인라인 함수 선언
//======================================
#include "MacroFunction.h"
#include "StandardStructure.h"
#include "InlineFunction.h"

//======================================
// - ## 10.14.17 ##
// - written by 이태섭
// -  ##색상 매크로 변수 설정
//======================================
#define C_RED      D3DCOLOR_XRGB(255,0,0)
#define C_BLUE      D3DCOLOR_XRGB(0,0,255)
#define C_GREEN      D3DCOLOR_XRGB(0,255,0)
#define C_BLACK      D3DCOLOR_XRGB(0,0,0)
#define C_WHITE      D3DCOLOR_XRGB(255,255,255)
#define C_MAGENTA   D3DCOLOR_XRGB(255,0,255)
#define C_CYAN      D3DCOLOR_XRGB(0,255,255)
#define C_YELLOW   D3DCOLOR_XRGB(255,255,0)
#define C_GRAY      D3DCOLOR_XRGB(128, 128, 128)

// = D3DXCOLOR
#define CX_RED     D3DXCOLOR(1,0,0,0.1f)
#define CX_BLUE    D3DXCOLOR(0,0,1,1)
#define CX_GREEN   D3DXCOLOR(0,1,0,1)
#define CX_YELLOW  D3DXCOLOR(1,1,0,1)
#define CX_BLACK   D3DXCOLOR(0,0,0,1)
#define CX_WHITE   D3DXCOLOR(1,1,1,1)
#define CX_GRAY    D3DXCOLOR(0.5,0.5,0.5,1)

#define WINSIZEX 1024
#define WINSIZEY 760

// = FONT2NUMBER
#define FONT2_START 47
#define FONT2_NUM0	48
#define FONT2_NUM1	49
#define FONT2_NUM2	50
#define FONT2_NUM3	51
#define FONT2_NUM4	52
#define FONT2_NUM5	53
#define FONT2_NUM6	54
#define FONT2_NUM7	55
#define FONT2_NUM8	56
#define FONT2_NUM9	57


//======================================
// - ## 매니저 헤더파일 선언 ##
//======================================
#include "DeviceManager.h"
#include "Object.h"
#include "KeyManager.h"
#include "ObjectManager.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "FontManager.h"
#include "TimeManager.h"
#include "cNetworkManager.h"
#include "cPhysXManager.h"
#include "SceneManager.h"
#include "CameraManager.h"
#include "LightManager.h"
#include "ItemManager.h"
#include "TextManager.h"
#include "cDataManager.h"

//UTIL
#include "cStringUtil.h"