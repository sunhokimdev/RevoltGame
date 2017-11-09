#include "stdafx.h"
#include "cNetworkManager.h"
#include "MainGame.h"

cNetworkManager::cNetworkManager()
{
}

cNetworkManager::~cNetworkManager()
{
	Release();
}

void cNetworkManager::Start()
{
	WSADATA wsaData;
	SOCKADDR_IN servAdr;

	char args[NAME_SIZE];

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error");

	m_hSock = socket(PF_INET, SOCK_STREAM, 0);

	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	//servAdr.sin_addr.s_addr = inet_addr("192.168.0.72");
	servAdr.sin_addr.s_addr = inet_addr("192.168.0.13");
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

	return true;
}

void cNetworkManager::ErrorHandling(char * msg)
{
	fputs(msg, stderr);
	fputc('\n', stderr);
	Release();
}

void cNetworkManager::SetRoomName(std::string str)
{
	for (int i = 0; i < str.size(); ++i)
		roomName[i] = str[i];
}

void cNetworkManager::SetName(std::string str)
{
	for (int i = 0; i < str.size(); ++i)
		name[i] = str[i];
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

	return addr;
}
