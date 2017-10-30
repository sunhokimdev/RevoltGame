#include "stdafx.h"
#include "cNetwork.h"

char cNetwork::name[NAME_SIZE];
char cNetwork::msg[BUF_SIZE];

cNetwork::cNetwork()
{
}


cNetwork::~cNetwork()
{
}

void cNetwork::Start()
{
	WSADATA wsaData;
	SOCKET hSock;
	SOCKADDR_IN servAdr;

	char args[NAME_SIZE];

	HANDLE hSndThread, hRcvThread;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error");

	std::cin >> name;

	hSock = socket(PF_INET, SOCK_STREAM, 0);

	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	servAdr.sin_addr.s_addr = inet_addr("172.30.1.3");
	servAdr.sin_port = htons(9190);

	if (connect(hSock, (SOCKADDR*)&servAdr, sizeof(servAdr)) == SOCKET_ERROR)
		ErrorHandling("connect() error");

	hSndThread = (HANDLE)_beginthreadex(NULL, 0, SendMsg, (void*)&hSock, 0, NULL);
	hRcvThread = (HANDLE)_beginthreadex(NULL, 0, RecvMsg, (void*)&hSock, 0, NULL);

	WaitForSingleObject(hSndThread, INFINITE);
	WaitForSingleObject(hRcvThread, INFINITE);

	closesocket(hSock);
	WSACleanup();

	return;
}

void cNetwork::Release()
{
}

unsigned cNetwork::SendMsg(void * arg)
{
	SOCKET hSock = *((SOCKET*)arg);
	char nameMsg[NAME_SIZE + BUF_SIZE];
	while (true)
	{
		fgets(msg, BUF_SIZE, stdin);
		if (!strcmp(msg, "q\n") || !strcmp(msg, "Q\n"))
		{
			closesocket(hSock);
			return 0;
		}

		sprintf(nameMsg, "%s %s", name, msg);
		send(hSock, nameMsg, strlen(nameMsg), 0);
	}

	return 0;
}

unsigned cNetwork::RecvMsg(void * arg)
{
	int hSock = *((SOCKET*)arg);
	char nameMsg[NAME_SIZE + BUF_SIZE];
	int strLen;

	while (true)
	{
		strLen = recv(hSock, nameMsg, NAME_SIZE + BUF_SIZE - 1, 0);
		if (strLen == -1)
			return -1;
		nameMsg[strLen] = 0;
		fputs(nameMsg, stdout);
	}

	return 0;
}

void cNetwork::ErrorHandling(char * msg)
{
	fputs(msg, stderr);
	fputc('\n', stderr);
}
