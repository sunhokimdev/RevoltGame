#pragma once
#include "Object.h"
#include "Thing.h"
#include "Camera.h"

#include "cCar.h"

typedef std::map<std::string, Object*> MAP_STR_OBJ;
typedef std::map<std::string, Object*>::iterator MAP_STR_OBJ_iter;

class cTrack : public Object
{
public:
	cTrack();
	~cTrack();
public:
	int trackNum = 0;
	std::string trackName;
	int m_nLightIdx;
	//인게임 에 들어갈 장애물 등등
	SYNTHESIZE(std::vector<Object*>, m_vecObject, VecObject);
	//std::vector<Object*>	m_vecObject;
	//멥에 있는 체크박스
	//std::map<std::string, Object*>	m_mapCheckBox;

	SYNTHESIZE(std::vector<Object*>, m_vecCheckBox, CheckBoxs);
//	SYNTHESIZE(MAP_STR_OBJ, m_mapCheckBox, CheckBoxs);
	std::vector<Object*>* GetCheckBoxsPt() { return  &m_vecCheckBox; }
	//NxVehicle* pVeh;

	void Update();
	void LastUpdate();
	void Render();
	void Destory();

	void SetData();
	void LoadTrack(std::string FileName);
	void CreateTrackPhysX();

//	int GetTrackCheckBoxSize() { return m_vecCheckBox.size(); }

	//스타트지점
	SYNTHESIZE(std::vector<D3DXVECTOR3>, vecStartPos, StartPositions);
};

