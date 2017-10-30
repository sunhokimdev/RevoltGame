#pragma once

class cItem;

#define g_pItemManager ItemManager::GetInstance();

//===================================================================
// - written by 김선호
// - ###아이템 물리적용 시켜주는 아이템 매니저###
// - 모든 아이템들은 여기서 적용시켜준다
//===================================================================

class ItemManager
{
private:
	std::vector<cItem*> m_vecItem;		// 아이템들을 관리하는 클래스
public:
	SINGLETONE(ItemManager);
};

