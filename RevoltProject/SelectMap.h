#pragma once
#include "Lobby.h"

class UITextImageView;			// TextImageView Class
class UIImageView;				// ImageView Class

class SelectMap
{
public:
	SelectMap();
	~SelectMap();
	void Setup();

	bool GetIsLockState(int LeftAndRight);

	void SetMapType(MAP_TYPE* mapType, int SelectNum);
	void MapTypeUpdate(int SelectNum);												   // Map Update;

	SYNTHESIZE(MAP_TYPE, m_mapType, mapType);							   // Map Type

	SYNTHESIZE(int, m_selectMapType, selectMapType);
	SYNTHESIZE(int, m_LockedTime, LockedTime);

	SYNTHESIZE(bool, m_isOpenHood, OpenHood);							   // Map Open Hood
	SYNTHESIZE(bool, m_isOpenMuse, OpenMuse);							   // Map Open Muse 
	SYNTHESIZE(bool, m_isOpenShip, OpenShip);							   // Map Open Ship 

	SYNTHESIZE(bool, m_isUnLocked, UnLocked);							   // Control LockRender
	SYNTHESIZE(bool, m_isLockedRender, LockedRender);					   // Locked Image, Text Render

	SYNTHESIZE(UIImageView*, m_mapParent, mapParent);
	SYNTHESIZE(UIImageView*, m_mapImage, magImage);						   // Map Image
	SYNTHESIZE(UITextImageView*, m_mapName, m_mapName);					   // Map Name
	SYNTHESIZE(UITextImageView*, m_mapLength, m_mapLength);				   // Map Length
	SYNTHESIZE(UITextImageView*, m_mapDifficulty, m_mapDifficulty);		   // Map Difficulty

	SYNTHESIZE(UIImageView*, m_LockedRing, m_LockedRing);				   // Locked Case
	SYNTHESIZE(UITextImageView*, m_LockedTextImage, m_LockedTextImage);	   // Locked Text												   
	
};

