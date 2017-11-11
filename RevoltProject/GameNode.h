#pragma once
class GameNode
{
protected:
	
	std::string strName;

public:
	GameNode();
	virtual	~GameNode();

	virtual void Setup() {}
	virtual void Destroy() {}
	virtual void Update() {}
	virtual void LastUpdate() {}
	virtual void Render() {}

	std::string GetSceneName() { return strName; }
	void SetSceneName(std::string name) { strName = name; }
};

