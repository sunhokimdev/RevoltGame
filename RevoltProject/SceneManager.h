#pragma once
#define g_SceneManager SceneManager::GetInstance()

class Camera;

class GameNode;

class SceneManager
{
	SINGLETONE(SceneManager);

public:
	typedef std::map<std::string, GameNode*> mapSceneList;
	typedef std::map<std::string, GameNode*>::iterator mapSceneIter;

private:
	static GameNode* _scCurrent;			//현재씬
	static GameNode* _scLoading;		//로딩씬
	static GameNode* _scReady;			//교체 대기씬

	mapSceneList _mSceneList;			//씬 리스트
	mapSceneIter _miSceneList;
	mapSceneList _mLoadingSceneList;	//로딩씬 리스트

	DWORD _LoadThreadID;

	Camera* m_pCam;

public:

	void Setup();
	void Update();
	void Render();
	void Destroy();

	//씬추가 함수
	GameNode* AddScene(std::string sceneName, GameNode* scene);
	//로딩씬 추가
	GameNode* AddLoadingScene(std::string loadingSceneName, GameNode* scene);


	//씬 교체 함수
	HRESULT ChangeScene(std::string sceneName);
	HRESULT ChangeScene(std::string sceneName, std::string loadingSceneName);

	//나중에 만들어 쓸때 사용
	friend DWORD CALLBACK LoadingThread(LPVOID prc);
};

