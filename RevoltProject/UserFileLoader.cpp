#include "stdafx.h"
#include "UserFileLoader.h"
#include <direct.h>			// mkdir(), rmdir()
#include <io.h>				// 폴더내 파일 검색하기위해 추가

UserFileLoader::UserFileLoader()
{
}


UserFileLoader::~UserFileLoader()
{
}

std::string UserFileLoader::LoadProfile(IN char * FileName)
{
	std::string sFullPath("Profile/");
	sFullPath += std::string(FileName) + '/' + std::string(FileName) + ".txt";

	FILE* fp;
	fopen_s(&fp, sFullPath.c_str(), "r");

	while (true)
	{
		if (feof(fp)) break;

		char szTemp[1024];
		fgets(szTemp, 1024, fp);
		if (szTemp[0] == '[')
		{
			continue;
		}
		else if (szTemp[0] == 'P')
		{
			char szName[1024];
			sscanf_s(szTemp, "%*s %*s %s", szName, 1024);
			m_PlayerName = szName;
		}
	} // << : while 끝

	fclose(fp);

	return m_PlayerName;
}

std::vector<std::string> UserFileLoader::LoadProfileList()
{
	std::string sFullPath("Profile/*");
	_finddata_t fd;
	intptr_t	handle;
	handle = _findfirst(sFullPath.c_str(), &fd);

	MessageBoxA(g_hWnd, fd.name, fd.name, MB_OK);

	do
	{
		m_ProfileList.push_back(fd.name);

		if (m_ProfileList.back() == "." || m_ProfileList.back() == "..")
		{
			m_ProfileList.pop_back();
		}
	} while (_findnext(handle, &fd) == 0);

	_findclose(handle);

	return m_ProfileList;
}

void UserFileLoader::CreateProfile(IN std::string FileName)
{
	std::string Folder = "Profile/";
	std::string FolderPath = Folder + std::string(FileName);
	
	mkdir(FolderPath.c_str());

	std::string sFullPath(Folder);
	sFullPath += FileName + std::string("/") + FileName + std::string(".txt");

	FILE* fp;
	fopen_s(&fp, sFullPath.c_str(), "w");

	char* ch = "[GAME]\n";
	char* ch2 = "PlayerName = ";
	fputs(ch, fp);
	fputs(ch2, fp);
	fputs(FileName.c_str(), fp);

	fclose(fp);
}

void UserFileLoader::DeleteProfile(IN std::string FileName)
{
	std::string Folder = "Profile/";
	std::string FolderPath = Folder + std::string(FileName);

	std::string FilePath(Folder);
	FilePath += std::string(FileName) + '/' + std::string(FileName) + ".txt";
	remove(FilePath.c_str());

	rmdir(FolderPath.c_str());
}