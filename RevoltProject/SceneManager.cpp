#include "stdafx.h"
#include "SceneManager.h"
#include "GameNode.h"

GameNode* SceneManager::_scCurrent = NULL;
GameNode* SceneManager::_scLoading = NULL;
GameNode* SceneManager::_scReady = NULL;

SceneManager::SceneManager(){}

SceneManager::~SceneManager(){}

void SceneManager::Setup()
{
	_scCurrent = NULL;
	_scLoading = NULL;
	_scReady = NULL;
}

void SceneManager::Update()
{
	if (_scCurrent) _scCurrent->Update();
}

void SceneManager::LastUpdate()
{
	if (_scCurrent) _scCurrent->LastUpdate();
}

void SceneManager::Render()
{
	if (_scCurrent) _scCurrent->Render();
}

void SceneManager::Destroy()
{
	for each(auto sc in _mSceneList)
	{
		sc.second->Destroy();
	}
	_mSceneList.clear();

	SAFE_DESTROY(_scCurrent);
	_scCurrent = NULL;
}

GameNode * SceneManager::AddScene(std::string sceneName, GameNode * scene)
{
	if (!scene) return NULL;

	_mSceneList.insert(make_pair(sceneName, scene));

	return scene;
}

GameNode * SceneManager::AddLoadingScene(std::string loadingSceneName, GameNode * scene)
{
	if (!scene) return NULL;

	_mSceneList.insert(make_pair(loadingSceneName, scene));

	return scene;
}

HRESULT SceneManager::ChangeScene(std::string sceneName)
{
	//바꾸려 하는 씬이 있는지 찾는다.
	mapSceneIter find = _mSceneList.find(sceneName);

	//없으면 false
	if (find == _mSceneList.end()) return E_FAIL;

	//바꾸려 하는 씬과 현재의 씬이 같으면 OK
	if (find->second == _scCurrent) return S_OK;

	
	{
		//새롭게 변경되는 씬의 Setup실행
		find->second->Setup();

		//씬을 바꿨으니 현재씬 해제
		if (_scCurrent) _scCurrent->Destroy();

		_scCurrent = find->second;

		return S_OK;
	}

	return E_FAIL;
}


HRESULT SceneManager::ChangeScene(std::string sceneName, std::string loadingSceneName)
{
	////바꾸려 하는 씬이 있는지 찾는다.
	//mapSceneIter find = _mSceneList.find(sceneName);

	////없으면 false
	//if (find == _mSceneList.end()) return E_FAIL;

	//if (find->second == _scCurrent) return S_OK;

	////로딩하려는 씬 있으면 넣어줌
	//mapSceneIter findLoading = _mLoadingSceneList.find(loadingSceneName);


	//{

	//	find->second->Setup();

	//	if (_scCurrent) _scCurrent->Destroy();

	//	//로딩씬을 먼저 틀고
	//	_scLoading = findLoading->second;

	//	//다음 씬 준비
	//	_scReady = find->second;

	//	//쓰레드 종료
	//	CloseHandle(CreateThread(NULL, 0, LoadingThread, NULL, 0, &_LoadThreadID));
	//}

	return E_FAIL;
}

