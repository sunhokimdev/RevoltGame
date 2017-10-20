#pragma once
class Map
{
private:

public:
	Map();
	~Map();

	static LOBBY g_LobbyState;

	void Load(char* szFolder, char* szFile);

	void Setup();
	void Update();
	void Render();
};

