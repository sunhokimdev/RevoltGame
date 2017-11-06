#pragma once

#define NAME_SIZE 20
#define BUF_SIZE 1024

#define g_pNetworkManager cNetworkManager::GetInstance()

class cNetworkManager
{
private:
	SOCKET m_hSock;

	char name[NAME_SIZE];
	char roomName[NAME_SIZE];
	int data[BUF_SIZE];

	std::string m_msg;
public:
	SINGLETONE(cNetworkManager);

	void Start();
	void Release();

	DWORD SendMsg(const char* msg);
	bool RecvMsg();
	void ErrorHandling(char* msg);

	void SetRoomName(std::string str);
	void SetName(std::string str);

	SYNTHESIZE(bool, m_isNetwork, IsNetwork);

	std::string GetMsg() { return m_msg; }
};

