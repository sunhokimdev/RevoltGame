#pragma once
class FrustomView;

class SkinnedMesh
{
public:
	SkinnedMesh();
	~SkinnedMesh();

	void Setup(char* szFolder, char* szFile, D3DXVECTOR3 pos, bool isMove = false);
	void Update();
	void Update(LPD3DXFRAME pFrame, LPD3DXFRAME pParent);
	void Render(LPD3DXFRAME pFrame);
	void SetupBoneMatrixPtrs(LPD3DXFRAME pFrame);
	void UpdateSkinnedMesh(LPD3DXFRAME pFrame);

	void KeyEvent();
	void SetUpMeshState();
	void SetAnimationIndex(int nIndex);
	void SetAnimationIndexBlend(int nIndex);
	void Destroy();

	SYNTHESIZE(D3DXVECTOR3, m_vMin, Min);
	SYNTHESIZE(D3DXVECTOR3, m_vMax, Max);
protected:
	LPD3DXFRAME									m_pRoot;
	LPD3DXANIMATIONCONTROLLER			m_pAnimController;
	float												m_fBlendTime;
	float												m_fPassedBlendTime;
	bool												m_isAnimBlend;
private:
	D3DXVECTOR3			m_vPosition;
	D3DXVECTOR3			m_vDirection;
	std::vector<DWORD>	m_dwAttack;
	DWORD					m_dwWalking;
	DWORD					m_dwStanding;
	float						m_ChangeAni;
	float						m_fRotY;
	int							m_currentID;
	bool						m_isMove;
	FrustomView*			m_pFrustom;
};

