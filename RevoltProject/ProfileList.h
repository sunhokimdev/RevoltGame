#pragma once

class UIImageView;

class ProfileList
{
private:
	std::vector<std::string> m_vProfileList;

public:
	ProfileList();
	~ProfileList();

	void Destroy();
	void ListLoad();								// 파일 검색해서 리스트 담기
	UIImageView*			  GetProfileList();		// 리스트 UI 가져오기
	std::vector<std::string>  GetUpdateList() { return m_vProfileList; }	// 리스트 업데이트

	SYNTHESIZE(std::string, m_CarName, CarName);
	SYNTHESIZE(std::string, m_UserName, UserNameText);
	SYNTHESIZE(std::string, m_MapName, MapName);
};

