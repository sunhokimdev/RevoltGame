#pragma once
class FrustomView
{
private:
	D3DXPLANE m_planes[6];
public:
	FrustomView();
	~FrustomView();

	void Setup();
	bool CheckPoint(float x, float y, float z);
	bool CheckCube(float x, float y, float z, float w);
	bool CheckSphere(float x, float y, float z, float w);
	bool CheckRectangle(float a, float b, float c, float d, float e, float f);

	SYNTHESIZE(bool, isFrustom, Frustom);
};

