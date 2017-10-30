#pragma once
class GameNode
{
public:
	GameNode();
	virtual	~GameNode();

	virtual void Setup() {}
	virtual void Destroy() {}
	virtual void Update() {}
	virtual void Render() {}
};

