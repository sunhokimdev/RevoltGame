#pragma once
class UserFileLoader
{
private:
	std::string					m_PlayerName;
	std::vector<std::string>	m_ProfileList;

public:
	UserFileLoader();
	~UserFileLoader();

	std::string					LoadProfile(IN char* FileName);
	std::vector<std::string>	LoadProfileList();
	void						CreateProfile(IN std::string FileName);
	void						DeleteProfile(IN std::string FIleName);
};

