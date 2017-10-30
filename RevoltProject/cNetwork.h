#pragma once

#define NAME_SIZE 20
#define BUF_SIZE 100

class cNetwork
{
private:

public:
	cNetwork();
	~cNetwork();

	void Start();
	void Release();

	static char name[NAME_SIZE];
	static char msg[BUF_SIZE];
	static unsigned WINAPI SendMsg(void* arg);
	static unsigned WINAPI RecvMsg(void* arg);
	void ErrorHandling(char* msg);
};

