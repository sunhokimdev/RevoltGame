#pragma once

using namespace FMOD;

#define SOUNDBUFFER 10
#define EXTRACHANNELBUFFER 5

#define TOTALSOUNDBUFFER SOUNDBUFFER + EXTRACHANNELBUFFER

#define g_pSoundManager SoundManager::GetInstance()

class SoundManager
{
private:
	typedef std::map<std::string, Sound**> arrSounds;
	typedef std::map<std::string, Sound**>::iterator arrSoundsIter;
	typedef std::map<std::string, Channel**> arrChannels;
	typedef std::map<std::string, Channel**>::iterator arrChannelsIter;

	System* _system;
	Sound** _sound;
	Channel** _channel;

	arrSounds _mTotalSounds;

	SINGLETONE(SoundManager);
public:
	HRESULT init();
	void release();
	void update();

	void addSound(std::string keyName, std::string soundName, bool bgm, bool loop);
	void play(std::string keyName, float volume = 1.0f);	//0 ~ 255, 0.0 ~ 1.0f
	void stop(std::string keyName);
	void pause(std::string keyName);
	void resume(std::string keyName);

	bool isPlaySound(std::string keyName);
	bool isPauseSound(std::string keyName);
};

