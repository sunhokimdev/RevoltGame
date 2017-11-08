#pragma once

#define NAME_SIZE 20
#define BUF_SIZE 1024

#define g_pNetworkManager cNetworkManager::GetInstance()

class cNetworkManager
{
private:
	SOCKET m_hSock;
	std::vector<std::string> m_vecMyIP;
	
	char name[NAME_SIZE];		// 자동차 이름
	char roomName[NAME_SIZE];
	int data[BUF_SIZE];

	std::string m_serverIP;
	std::string m_msg;			// 데이터 이름
public:
	SINGLETONE(cNetworkManager);

	void Start();
	void Release();

	DWORD SendMsg(const char* msg);		// 데이터 서버에 보내기
	bool RecvMsg();		// 데이서 서버에 받기
	void ErrorHandling(char* msg);

	void SetRoomName(std::string str);
	void SetName(std::string str);
	void SetServerIP(std::string str) { m_serverIP = str; };

	SYNTHESIZE(bool, m_isNetwork, IsNetwork);

	std::string GetMsg() { return m_msg; }
	

	sockaddr_in GetDefaultMyIP();
};

