#pragma once

#define NAME_SIZE 20
#define BUF_SIZE 1024

#define g_pNetworkManager cNetworkManager::GetInstance()

class cCar;

struct ST_KEYSET
{
	bool up;
	bool down;
	bool left;
	bool right;
	bool r_key;
	bool f_key;
	bool ctrl;
};

class cNetworkManager
{
private:
	ST_KEYSET m_keyEvent;
	SOCKET m_hSock;
	std::vector<std::string> m_vecMyIP;

	char name[NAME_SIZE];		// 자동차 이름
	char roomName[NAME_SIZE];
	int data[BUF_SIZE];

	std::string m_serverIP;		// 서버 IP 주소
	std::string m_vPosition;	// 클라이언트 위치 지정

	std::string m_msg;			// 데이터 이름
	char* m_charMsg;
public:
	SINGLETONE(cNetworkManager);

	void Start();
	void Release();

	DWORD SendMsg(const char* msg);		// 데이터 서버에 보내기
	bool RecvMsg();		// 데이서 서버에 받기
	void ErrorHandling(char* msg);

	void SetRoomName(std::string str);
	void SetName(std::string str);

	SYNTHESIZE(bool, m_isNetwork, IsNetwork);
	SYNTHESIZE(bool, m_isInNetwork, IsInGameNetwork);

	std::string GetMsg() { return m_msg; }

	std::string GetKeYString();
	std::string GetClientIP() { return m_vecMyIP[m_vecMyIP.size() - 1]; };
	void SetClientPosition(NxVec3 v);
	std::string GetClientPosition();
	char* GetCharMsg() { return m_charMsg; };
	void SetServerIP(std::string str) { m_serverIP = str; }

	void SetUpKey(bool b) { m_keyEvent.up = b; };
	void SetDownKey(bool b) { m_keyEvent.down = b; };
	void SetLeftKey(bool b) { m_keyEvent.left = b; };
	void SetRightKey(bool b) { m_keyEvent.right = b; };
	void SetRKey(bool b) { m_keyEvent.r_key = b; };
	void SetFKey(bool b) { m_keyEvent.f_key = b; };
	void SetCtrlKey(bool b) { m_keyEvent.ctrl = b; };


	void SetResetKeyEvent();
	sockaddr_in GetDefaultMyIP();
};

