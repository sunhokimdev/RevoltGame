#pragma once

class Thing;

class ThingManager
{
private:
	std::map<std::string, Thing*>	m_mapThing;		// 오브젝트 들을 저장하는 map STL
public:
	SINGLETONE(ThingManager);

	/*   오브젝트를 추가하는 메서드   */
	void AddThing(std::string strKey, char* szFolder, char* szFile, bool isMove = false, bool isRot = false, float angle = 0.0f);

	void Render(std::string strKey);
};

