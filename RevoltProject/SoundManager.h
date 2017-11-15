#pragma once

using namespace FMOD;

#define SOUNDBUFFER 10
#define EXTRACHANNELBUFFER 5

#define SOUND_MAX_CHANNEL	10

#define TOTALSOUNDBUFFER SOUNDBUFFER + EXTRACHANNELBUFFER

#define g_pSoundManager SoundManager::GetInstance()

class SoundManager
{
private:
	System* m_pSystem;
	std::map<std::string, Sound*> m_sounds;
	std::list<Channel*> m_channels;

	std::string m_bgmSound;
	int m_bgmVoiune;
	Channel* m_pBgmChnnel;

	FMOD_VECTOR m_fmVector_Listener;
	FMOD_VECTOR m_forward;
	FMOD_VECTOR m_up;

	SINGLETONE(SoundManager);
public:
	void Setup();
	void Destroy();
	void Update();

	void Setup3DCamera(D3DXVECTOR3 pos, D3DXVECTOR3 forward, D3DXVECTOR3 up = D3DXVECTOR3(0.f, 1.f, 0.f));

	Sound* FindSound(std::string key);
	Channel* FindChannel(std::string key);

	void LoadSound(std::string folderName, std::string fileName, bool loop);
	void LoadSound(std::string folderName, std::string fileName, std::string key, bool loop, bool is3D);

	void Play(std::string fileName, float volume = 1.0f, D3DXVECTOR3 soundPos = D3DXVECTOR3(0, 0, 0));
	void Play_BGM(std::string fileName, float volume = 1.0f);
	void Play_Loop(std::string fileName, float volume = 1.0f);
	
	bool isPlay(std::string fileName);

	void SetVolum(std::string key, float volume);

	void SetSoundPosition(std::string fileName, D3DXVECTOR3 position);
	void SetSoundPosition(Channel* pChannel, D3DXVECTOR3 position);
	void SetSoundPosition(Channel* pChannel, FMOD_VECTOR position);

	void SetPosVolPitch(std::string pChannel, D3DXVECTOR3 position, float volume, float freq);

	void Stop(std::string fileName);
	void Pause(std::string fileName);
	void Resume(std::string fileName);

	void SetPitch(std::string fileName, float frequency);

	void AllSoundIsStop();
	void AllSoundIsPause();
	void AllSoundIsResume();
};

