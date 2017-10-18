#include "stdafx.h"
#include "SkinnedMesh.h"
#include "AllocateHierarchy.h"
#include "FrustomView.h"

SkinnedMesh::SkinnedMesh()
	:m_pRoot(NULL)
	, m_pAnimController(NULL)
	, m_fBlendTime(0.3f)
	, m_fPassedBlendTime(0.0f)
	, m_isAnimBlend(false)
	, m_ChangeAni(0.0f)
	, m_pFrustom(NULL)
	, m_vDirection(0, 0, 1)
	, m_vPosition(0, 0, 0)
	, m_fRotY(0.0f)
{
}


SkinnedMesh::~SkinnedMesh()
{
	AllocateHierarchy ah;
	D3DXFrameDestroy(m_pRoot, &ah);
	SAFE_RELEASE(m_pAnimController);
}

void SkinnedMesh::Setup(char * szFolder, char * szFile, D3DXVECTOR3 pos, bool isMove)
{
	m_isMove = isMove;
	std::string sFullPath(szFolder);
	sFullPath = sFullPath + std::string("/") + std::string(szFile);
	AllocateHierarchy ah;
	ah.SetFolder(szFolder);

	m_vPosition = pos;

	D3DXLoadMeshHierarchyFromXA(
		sFullPath.c_str(),
		D3DXMESH_MANAGED,
		g_pD3DDevice,
		&ah,
		NULL,
		&m_pRoot,
		&m_pAnimController);

	m_pFrustom = new FrustomView;
	m_pFrustom->Setup();
	m_pFrustom->SetFrustom(false);

	D3DXMatrixTranslation(&m_pRoot->TransformationMatrix, pos.x, pos.y, pos.z);

	SetUpMeshState();
	SetupBoneMatrixPtrs(m_pRoot);
}

void SkinnedMesh::Update()
{
	if (m_currentID != m_dwStanding && m_currentID != m_dwWalking)
		m_ChangeAni += g_pTimeManager->GetElapsedTime();

	if (m_isAnimBlend)
	{
		m_fPassedBlendTime += g_pTimeManager->GetElapsedTime();
		if (m_fPassedBlendTime >= m_fBlendTime)
		{
			m_isAnimBlend = false;
			m_pAnimController->SetTrackWeight(0, 1.0f);
			m_pAnimController->SetTrackEnable(1, false);
		}
		else
		{
			float fWeight = m_fPassedBlendTime / m_fBlendTime;
			m_pAnimController->SetTrackWeight(0, fWeight);
			m_pAnimController->SetTrackWeight(1, 1.0 - fWeight);
		}
	}

	m_pAnimController->AdvanceTime(g_pTimeManager->GetElapsedTime(), NULL);

	KeyEvent();
	Update(m_pRoot, NULL);
	UpdateSkinnedMesh(m_pRoot);
}

void SkinnedMesh::Update(LPD3DXFRAME pFrame, LPD3DXFRAME pParent)
{
	ST_BONE* pBone = (ST_BONE*)pFrame;

	if (pFrame == NULL)
	{
		pFrame = m_pRoot;
	}

	pBone = (ST_BONE*)pFrame;

	pBone->CombinedTransformationMatrix = pBone->TransformationMatrix;

	if (pParent)
	{
		pBone->CombinedTransformationMatrix *= ((ST_BONE*)pParent)->CombinedTransformationMatrix;
	}

	if (pFrame->pFrameFirstChild)
	{
		Update(pFrame->pFrameFirstChild, pFrame);
	}
	if (pFrame->pFrameSibling)
	{
		Update(pFrame->pFrameSibling, pParent);
	}
}

void SkinnedMesh::Render(LPD3DXFRAME pFrame)
{
	if (pFrame == NULL)
	{
		pFrame = m_pRoot;
	}
	ST_BONE* pBone = (ST_BONE*)pFrame;

	if (pBone->pMeshContainer)
	{
		ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pBone->pMeshContainer;

		if (pBoneMesh->MeshData.pMesh)
		{
			g_pD3DDevice->SetTransform(D3DTS_WORLD,
				&pBone->CombinedTransformationMatrix);

			float x = pBoneMesh->pCurrentBoneMatrices->_41;
			float y = pBoneMesh->pCurrentBoneMatrices->_42;
			float z = pBoneMesh->pCurrentBoneMatrices->_43;

			if (m_pFrustom->GetFrustom())
			{
				if (m_pFrustom->CheckPoint(x, y, z))
				{
					for (size_t i = 0; i < pBoneMesh->vecMtl.size(); ++i)
					{
						g_pD3DDevice->SetTexture(0, pBoneMesh->vecTexture[i]);
						g_pD3DDevice->SetMaterial(&pBoneMesh->vecMtl[i]);
						pBoneMesh->MeshData.pMesh->DrawSubset(i);
					}
				}
			}
			else
			{
				for (size_t i = 0; i < pBoneMesh->vecMtl.size(); ++i)
				{
					g_pD3DDevice->SetTexture(0, pBoneMesh->vecTexture[i]);
					g_pD3DDevice->SetMaterial(&pBoneMesh->vecMtl[i]);
					pBoneMesh->MeshData.pMesh->DrawSubset(i);
				}
			}
		}
	}
	if (pFrame->pFrameFirstChild)
	{
		Render(pFrame->pFrameFirstChild);
	}
	if (pFrame->pFrameSibling)
	{
		Render(pFrame->pFrameSibling);
	}
}

void SkinnedMesh::SetupBoneMatrixPtrs(LPD3DXFRAME pFrame)
{
	if (pFrame && pFrame->pMeshContainer)
	{
		ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pFrame->pMeshContainer;

		if (pBoneMesh->pSkinInfo)
		{
			LPD3DXSKININFO pSkinInfo = pBoneMesh->pSkinInfo;
			DWORD dwNumBones = pSkinInfo->GetNumBones();
			for (DWORD i = 0; i < dwNumBones; ++i)
			{
				ST_BONE* pBone = (ST_BONE*)D3DXFrameFind(m_pRoot, pSkinInfo->GetBoneName(i));
				pBoneMesh->ppBoneMatrixPtrs[i] = &(pBone->CombinedTransformationMatrix);
			}
		}
	}

	if (pFrame->pFrameFirstChild)
	{
		SetupBoneMatrixPtrs(pFrame->pFrameFirstChild);
	}

	if (pFrame->pFrameSibling)
	{
		SetupBoneMatrixPtrs(pFrame->pFrameSibling);
	}
}

void SkinnedMesh::UpdateSkinnedMesh(LPD3DXFRAME pFrame)
{
	if (pFrame && pFrame->pMeshContainer)
	{
		ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pFrame->pMeshContainer;

		if (pBoneMesh->pSkinInfo)
		{
			LPD3DXSKININFO pSkinInfo = pBoneMesh->pSkinInfo;
			DWORD dwNumBones = pSkinInfo->GetNumBones();
			for (DWORD i = 0; i < dwNumBones; ++i)
			{
				pBoneMesh->pCurrentBoneMatrices[i] =
					pBoneMesh->pBoneOffsetMatrices[i] * *(pBoneMesh->ppBoneMatrixPtrs[i]);
			} // << :for
		} // << : if

		BYTE* src = NULL;
		BYTE* dest = NULL;
		pBoneMesh->pOrigMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&src);
		pBoneMesh->MeshData.pMesh->LockVertexBuffer(0, (void**)&dest);

		pBoneMesh->pSkinInfo->UpdateSkinnedMesh(
			pBoneMesh->pCurrentBoneMatrices, NULL, src, dest);
		pBoneMesh->MeshData.pMesh->UnlockVertexBuffer();
		pBoneMesh->pOrigMesh->UnlockVertexBuffer();

	} // << : if

	if (pFrame->pFrameFirstChild)
	{
		UpdateSkinnedMesh(pFrame->pFrameFirstChild);
	}
	if (pFrame->pFrameSibling)
	{
		UpdateSkinnedMesh(pFrame->pFrameSibling);
	}
}

void SkinnedMesh::KeyEvent()
{
	if (!m_isMove)
		return;

	static int nAttackIndex = 0;
	LPD3DXANIMATIONSET pAnimset = NULL;

	m_pAnimController->GetAnimationSet(m_currentID, &pAnimset);

	if (m_currentID != m_dwStanding && m_currentID != m_dwWalking)
	{
		if (m_ChangeAni + m_fPassedBlendTime > pAnimset->GetPeriod())
		{
			m_currentID = m_dwStanding;
			m_ChangeAni = 0.0f;
			SetAnimationIndexBlend(m_currentID);
		}
	}

	if (g_pKeyManager->isOnceKeyDown('Z'))
	{
		SetAnimationIndexBlend(m_dwAttack[nAttackIndex]);
		m_currentID = m_dwAttack[nAttackIndex];
		nAttackIndex++;

		if (m_dwAttack.size() == nAttackIndex)
			nAttackIndex = 0;

		m_ChangeAni = 0.0f;
	}
	else if (g_pKeyManager->isOnceKeyDown('X'))
	{
		m_currentID = m_dwWalking;
		SetAnimationIndexBlend(m_dwWalking);
		m_ChangeAni = 0.0f;
	}
	else if (g_pKeyManager->isOnceKeyDown('C'))
	{
		m_currentID = m_dwStanding;
		SetAnimationIndexBlend(m_dwStanding);
		m_ChangeAni = 0.0f;
	}
	else if (g_pKeyManager->isOnceKeyDown(VK_RBUTTON))
	{
		m_pFrustom->SetFrustom(true);
	}
	else if (g_pKeyManager->isOnceKeyDown('V'))
	{
		m_pFrustom->SetFrustom(false);
	}
	else if (g_pKeyManager->isOnceKeyDown(VK_DOWN))
	{
		if (m_currentID != m_dwWalking)
		{
			m_currentID = m_dwWalking;
			SetAnimationIndexBlend(m_dwWalking);
			m_ChangeAni = 0.0f;
		}

		m_vPosition -= m_vDirection * 0.1f;
	}
	else if (g_pKeyManager->isOnceKeyDown(VK_UP))
	{
		if (m_currentID != m_dwWalking)
		{
			m_currentID = m_dwWalking;
			SetAnimationIndexBlend(m_dwWalking);
			m_ChangeAni = 0.0f;
		}

		m_vPosition += m_vDirection * 0.1f;
	}
	else if (g_pKeyManager->isOnceKeyDown(VK_LEFT))
	{
		if (m_currentID != m_dwWalking)
		{
			m_currentID = m_dwWalking;
			SetAnimationIndexBlend(m_dwWalking);
			m_ChangeAni = 0.0f;
		}

		m_fRotY -= 0.1f;
	}
	else if (g_pKeyManager->isOnceKeyDown(VK_RIGHT))
	{
		if (m_currentID != m_dwWalking)
		{
			m_currentID = m_dwWalking;
			SetAnimationIndexBlend(m_dwWalking);
			m_ChangeAni = 0.0f;
		}

		m_fRotY += 0.1f;
	}
	else if (g_pKeyManager->isOnceKeyUp(VK_RIGHT) ||
		g_pKeyManager->isOnceKeyUp(VK_LEFT) ||
		g_pKeyManager->isOnceKeyUp(VK_UP) ||
		g_pKeyManager->isOnceKeyUp(VK_DOWN))
	{
		if (m_currentID != m_dwStanding)
		{
			m_currentID = m_dwStanding;
			SetAnimationIndexBlend(m_dwStanding);
			m_ChangeAni = 0.0f;
		}
	}

	D3DXMATRIXA16 matR, matT;
	D3DXMatrixRotationY(&matR, m_fRotY);
	m_vDirection = D3DXVECTOR3(0, 0, 1);
	D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);
}

void SkinnedMesh::SetUpMeshState()
{
	int num = m_pAnimController->GetNumAnimationSets();
	LPD3DXANIMATIONSET pAnimset = NULL;

	for (int i = 0;i < num;i++)
	{
		m_pAnimController->GetAnimationSet(i, &pAnimset);
		std::string str = pAnimset->GetName();

		if (str.find("Attack") != std::string::npos)
		{
			m_dwAttack.push_back(i);
		}
		else if (str.find("Walk") != std::string::npos)
		{
			m_dwWalking = i;
		}
		else if (str.find("Stand") != std::string::npos)
		{
			m_dwStanding = i;
		}
	}

	m_currentID = m_dwStanding;
	SetAnimationIndexBlend(m_dwStanding);
}

void SkinnedMesh::SetAnimationIndex(int nIndex)
{
	int num = m_pAnimController->GetNumAnimationSets();
	if (nIndex > num) nIndex = nIndex % num;

	m_pAnimController->GetNumAnimationSets(); //트랙

	LPD3DXANIMATIONSET pAnimset = NULL;
	m_pAnimController->GetAnimationSet(nIndex, &pAnimset); //정보를 얻어서
	m_pAnimController->SetTrackAnimationSet(0, pAnimset);
	m_pAnimController->GetPriorityBlend();
	pAnimset->Release();
}

void SkinnedMesh::SetAnimationIndexBlend(int nIndex)
{
	m_isAnimBlend = true;
	m_fPassedBlendTime = 0.0f;

	int num = m_pAnimController->GetNumAnimationSets();
	if (nIndex > num) nIndex = nIndex % num;

	LPD3DXANIMATIONSET pPrevAnimSet = NULL;
	LPD3DXANIMATIONSET pNextAnimSet = NULL;

	D3DXTRACK_DESC stTrackDesc;
	m_pAnimController->GetTrackDesc(0, &stTrackDesc);
	m_pAnimController->GetTrackAnimationSet(0, &pPrevAnimSet);
	m_pAnimController->SetTrackAnimationSet(1, pPrevAnimSet);
	m_pAnimController->SetTrackDesc(1, &stTrackDesc);

	// : nextd
	m_pAnimController->GetAnimationSet(nIndex, &pNextAnimSet);
	m_pAnimController->SetTrackAnimationSet(0, pNextAnimSet);
	m_pAnimController->SetTrackPosition(0, 0.0f);

	// :
	m_pAnimController->SetTrackWeight(0, 0.0f);
	m_pAnimController->SetTrackWeight(1, 1.0f);
	SAFE_RELEASE(pPrevAnimSet);
	SAFE_RELEASE(pNextAnimSet);
}

void SkinnedMesh::Destroy()
{
}
