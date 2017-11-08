#pragma once

class Object;

class c321GO
{
	std::vector<Object*> m_vec321go;

	float m_fAngle;
	float m_fAngleRatio; // 0~1
	float m_fTime;
	int m_nCount;
	bool m_isStart;
	D3DXVECTOR3 posStart, posEnd;

public:
	c321GO();
	~c321GO();

	void Setup();
	void Update();
	void Render();
	void Destroy();
	void StartCount();
	void Count();
};

