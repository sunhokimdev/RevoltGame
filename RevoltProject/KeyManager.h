#pragma once

#define g_pKeyManager KeyManager::GetInstance()

#define KEYMAX 256

#define KEY_MOVE_LEFT	VK_LEFT
#define KEY_MOVE_RIGHT	VK_RIGHT
#define KEY_ACCELERATOR VK_UP
#define KEY_REVERSE		VK_DOWN
#define KEY_FIRE_ITEM	VK_CONTROL
#define KEY_REPOSITION	'R'
#define KEY_CAR_FLIP	'F'
#define KEY_TIME_INFO	VK_F1

class KeyManager
{
private:
	std::bitset<KEYMAX> _keyUp;
	std::bitset<KEYMAX> _keyDown;
	int m_key;
	SINGLETONE(KeyManager);

public:
	HRESULT init(void);
	void release(void);

	bool isOnceKeyDown(int key);
	bool isOnceKeyUp(int key);
	bool isStayKeyDown(int key);
	bool isToggleKey(int key);

	std::bitset<KEYMAX> getKeyUp() { return _keyUp; }
	std::bitset<KEYMAX> getKeyDown() { return _keyDown; }

	void setKeyDown(int key, bool state) { _keyDown.set(key, state); }
	void setKeyUp(int key, bool state) { _keyUp.set(key, state); }
};

