#pragma once

#define g_pObjectManager	ObjectManager::GetInstance()

class Object;

class ObjectManager
{
public:
	void AddObject(Object* pObject)
	{
		// : add 
		m_setObject.insert(pObject);
	}

	void RemoveObject(Object* pObject)
	{
		// : remove
		m_setObject.erase(pObject);
	}

	void Destroy()
	{
		// : clear
		m_setObject.clear();

	}
private:
	SINGLETONE(ObjectManager);
	std::set<Object*>	m_setObject;
};

