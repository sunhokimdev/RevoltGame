#include "stdafx.h"
#include "cNetworkManager.h"
#include "MainGame.h"

cNetworkManager::cNetworkManager()
	: m_isNextStage(false)
{
	for (int i = 0; i < 20; i++)
	{
		ST_NETUSER netUser;
		netUser.IsReady = false;
		netUser.IsUse = false;
		m_vecUserIP.push_back(netUser);
	}
}

cNetworkManager::~cNetworkManager()
{
	Release();

	m_vecUserIP.clear();
	m_vecMyIP.clear();
}

void cNetworkManager::Start()
{
	WSADATA wsaData;
	SOCKADDR_IN servAdr;
	char args[NAME_SIZE];

	{
		m_user.IsReady = false;
	}

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error");

	m_hSock = socket(PF_INET, SOCK_STREAM, 0);

	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;

	servAdr.sin_addr.s_addr = inet_addr(m_serverIP.c_str());

	servAdr.sin_port = htons(8080);

	if (connect(m_hSock, (SOCKADDR*)&servAdr, sizeof(servAdr)) == SOCKET_ERROR)
	{
		ErrorHandling("connect() error");
		MessageBoxA(g_hWnd, "소켓통신에러", "소켓통신에러", MB_OK);
	}

	GetDefaultMyIP();

	return;
}

void cNetworkManager::Release()
{
	m_user.index = 0;
	m_user.IsReady = false;
	m_user.IsUse = false;

	closesocket(m_hSock);
	WSACleanup();
}

DWORD cNetworkManager::SendMsg(const char* msg)
{
	std::string str = msg;

	send(m_hSock, msg, strlen(msg), 0);

	return 0;
}

bool cNetworkManager::RecvMsg()
{
	SOCKET hSock = m_hSock;

	char nameMsg[NAME_SIZE + BUF_SIZE];
	int strLen = recv(hSock, nameMsg, NAME_SIZE + BUF_SIZE - 1, 0);

	nameMsg[strLen] = 0;

	m_msg = std::string(nameMsg);
	std::string sIP;
	std::string sIndex;
	std::string sUserID;
	std::string sCarName;
	std::string sReady;
	std::string sSend;

	/*   서버로 부터 받는 메시지   */

	if (m_msg.find("&") != -1 && !GetIsInGameNetwork())
	{
		sIP = strtok((char*)m_msg.c_str(), "&#!");
		sIndex = strtok(NULL, "&#!");

		if (sIP.c_str() != NULL && sIndex.c_str() != NULL)
		{
			m_vecUserIP[atoi(sIndex.c_str())].userIP = sIP;
			m_vecUserIP[atoi(sIndex.c_str())].IsUse = false;
			m_vecUserIP[atoi(sIndex.c_str())].IsReady = false;
			m_vecUserIP[atoi(sIndex.c_str())].index = atoi(sIndex.c_str());
		}

		SendClientData();

		return false;
	}

	else if (m_msg.find("@") != -1 && !GetIsInGameNetwork())
	{
		ST_NETUSER netUser;
		int index = 0;

		sIP = strtok((char*)m_msg.c_str(), "@#");
		sIndex = strtok(NULL, "@");
		sUserID = strtok(NULL, "@");
		sCarName = strtok(NULL, "@");
		sReady = strtok(NULL, "@#");

		netUser.userIP = sIP;
		netUser.index = atoi(sIndex.c_str());
		netUser.userID = sUserID;
		netUser.carName = sCarName;
		netUser.IsReady = atoi(sReady.c_str());
		netUser.IsUse = true;

		m_vecUserIP[netUser.index] = netUser;

		printf("%s %s\n", sIP.c_str(), sIndex.c_str());

		return false;
	}

	else if (m_msg.find("@Start!") != -1)
	{
		SetIsInGameNetwork(true);

		return false;
	}

	return true;
}

void cNetworkManager::ErrorHandling(char * msg)
{
	fputs(msg, stderr);
	fputc('\n', stderr);
	Release();
}

void cNetworkManager::SetUserReady()
{
	if (m_user.IsReady)
		m_user.IsReady = false;
	else
		m_user.IsReady = true;
}

void cNetworkManager::SetResetKeyEvent()
{
	m_keyEvent.ctrl = false;
	m_keyEvent.down = false;
	m_keyEvent.f_key = false;
	m_keyEvent.left = false;
	m_keyEvent.right = false;
	m_keyEvent.r_key = false;
	m_keyEvent.up = false;
}

void cNetworkManager::SendClientData()
{
	std::string str;

	str = "@" + m_user.userIP + 
		"@" + std::to_string(m_user.index) +
		"@" + m_user.userID + 
		"@" + m_user.carName +
		"@" + std::to_string(m_user.IsReady);

	SendMsg(str.c_str());
}

std::string cNetworkManager::GetKeYString()
{
	std::string str = "";

	if (m_keyEvent.up)
		str += "1";
	else
		str += "0";

	if (m_keyEvent.down)
		str += "1";
	else
		str += "0";
	if (m_keyEvent.left)
		str += "1";
	else
		str += "0";

	if (m_keyEvent.right)
		str += "1";
	else
		str += "0";

	if (m_keyEvent.ctrl)
		str += "1";
	else
		str += "0";

	if (m_keyEvent.r_key)
		str += "1";
	else
		str += "0";

	if (m_keyEvent.f_key)
		str += "1";
	else
		str += "0";

	return str;
}

void cNetworkManager::SetClientPosition(NxVec3 v)
{
	std::string str = "";
	str += std::to_string(v.x) + "/";
	str += std::to_string(v.y) + "/";
	str += std::to_string(v.z);

	m_vPosition = str;
}

std::string cNetworkManager::GetClientPosition()
{
	return m_vPosition;
}

void cNetworkManager::SetClientReadyReset()
{
	for (int i = 0;i < USER_SIZE;i++)
		m_vecUserIP[i].IsReady = false;
}

sockaddr_in cNetworkManager::GetDefaultMyIP()
{
	char localhostname[1024];
	sockaddr_in addr;

	if (gethostname(localhostname, 1024) == SOCKET_ERROR)
		return addr;

	HOSTENT* ptr = gethostbyname(localhostname);

	if (ptr)
	{
		for (int i = 0;ptr->h_addr_list[i] != NULL;i++)
		{
			memcpy(&addr.sin_addr, ptr->h_addr_list[i], ptr->h_length);
			printf("%s\n", inet_ntoa(addr.sin_addr));
			m_vecMyIP.push_back(inet_ntoa(addr.sin_addr));
		}
	}

	m_user.userIP = m_vecMyIP[m_vecMyIP.size() - 1];

	return addr;
}
