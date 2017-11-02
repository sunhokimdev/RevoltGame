#pragma once

class Camera;
class Grid;
class MtlTex;

class Lobby;
class Map;

class cCar;
//======================================
// - ## 10.03.17 ##
// - written by 김선호
// -  게임 시작 헤더파일
// - 매니저 규칙 - g_p클래스이름
//======================================

class MainGame
{
public:
	MainGame();
	~MainGame();

	/*   기본 세팅   */
	void Setup();
	void Update();
	void Render();
	void MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	/*   사운드 트랙 추가 메서드   */
	void SetAddSound();


	ID3DXMesh* TestMesh;

	

private:
	/*   기본 세팅   */
	Camera* m_pCamera;
	Grid*	m_pGrid;

	Map* m_pMap;
	Lobby* m_pLobby;


//	cCar* pCar;
};

