#pragma once

#define NAME_SIZE 20
#define BUF_SIZE 1024

#define g_pNetworkManager cNetworkManager::GetInstance()
#define USER_SIZE 20

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

struct ST_NETUSER
{
	std::string userIP;
	std::string userID;
	std::string carName;
	int carIndex;
	bool IsReady;
	bool IsUse;
	int index;
};

class cNetworkManager
{
private:
	ST_KEYSET m_keyEvent;
	SOCKET m_hSock;
	ST_NETUSER m_user;						// 클라이언트 유저
	std::vector<std::string> m_vecMyIP;		// 클라이언트 IP
	std::vector<ST_NETUSER> m_vecUserIP;		// 클라이언트를 제외한 유저 IP

	std::string m_serverIP;		// 서버 IP 주소
	std::string m_vPosition;	// 클라이언트 위치 지정

	std::string m_msg;			// 데이터 저장 변수
public:
	SINGLETONE(cNetworkManager);

	void Start();
	void Release();

	DWORD SendMsg(const char* msg);		// 데이터 서버에 보내기
	bool RecvMsg();		// 데이서 서버에 받기
	void ErrorHandling(char* msg);

	SYNTHESIZE(bool, m_isNetwork, IsNetwork);
	SYNTHESIZE(bool, m_isInNetwork, IsInGameNetwork);
	SYNTHESIZE(bool, m_isNextStage, IsNextStage);

	std::string GetMsg() { return m_msg; }

	std::string GetKeYString();
	std::string GetUserIP() { return m_user.userIP; };
	std::string GetClientIP(int index) { return m_vecUserIP[index].userIP; };

	void SetClientPosition(NxVec3 v);
	std::string GetClientPosition();

	void SetServerIP(std::string str) { m_serverIP = str; }

	void SetClientName(std::string str) { m_user.userID = str; };
	std::string GetClientName() { return m_user.userID; };

	void SetCarName(std::string str) { m_user.carName = str; };
	std::string GetCarName() { return m_user.carName; };

	bool GetReady(int index) { return m_vecUserIP[index].IsReady; };
	void SetClientReadyReset();

	std::string GetClientList(int index) { return m_vecUserIP[index].userID; };
	bool GetIsClientUse(int index) { return m_vecUserIP[index].IsUse; };

	// 클라이언트가 사용하는지
	void SetIsUse(bool b) { m_user.IsUse = b; };
	bool GetIsUse() { return m_user.IsUse; };

	int GetUserIndex() { return m_user.index; };
	bool GetIsReady() { return m_user.IsReady; };
	void SetIsReady(bool b) { m_user.IsReady = b; };

	void SetCarIndex(int d) { m_user.carIndex = d; };
	int GetCarIndex() { return m_user.carIndex; }

	bool GetClientReady(int index) { return m_vecUserIP[index].IsReady; };
	void SetUserReady();

	void SetUpKey(bool b) { m_keyEvent.up = b; };
	void SetDownKey(bool b) { m_keyEvent.down = b; };
	void SetLeftKey(bool b) { m_keyEvent.left = b; };
	void SetRightKey(bool b) { m_keyEvent.right = b; };
	void SetRKey(bool b) { m_keyEvent.r_key = b; };
	void SetFKey(bool b) { m_keyEvent.f_key = b; };
	void SetCtrlKey(bool b) { m_keyEvent.ctrl = b; };

	void SetResetKeyEvent();
	void SendClientData();
	sockaddr_in GetDefaultMyIP();
};

