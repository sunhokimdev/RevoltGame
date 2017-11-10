#pragma once
#include "Lobby.h"

class UITextImageView;			// TextImageView Class
class UIImageView;				// ImageView Class

class SelectMap
{
private:
	LPDIRECT3DTEXTURE9	m_pTexture;
	ST_SIZE				m_stSize;

	/*     Noise     */
	float LeftNoiseX;
	float RightNoiseX;
	float UpNoiseY;
	float DownNoiseY;

	/*     UpdateTextureName     */
	char* m_FileName;

public:
	SelectMap();
	~SelectMap();

	void SetTexture(char * szFullPath);
	void Setup();
	void Update();
	void SetMapType(MAP_TYPE* mapType, int SelectNum);					   // Map Set
	void MapTypeUpdate(int SelectNum);									   // Map Update;
	void Render(LPD3DXSPRITE pSprite);
	void Destroy();


	SYNTHESIZE(MAP_TYPE, m_mapType, mapType);							   // Map Type

	SYNTHESIZE(int, m_selectMapType, selectMapType);
	SYNTHESIZE(int, m_LockedTime, LockedTime);

	SYNTHESIZE(bool, m_isMove, Move);									   // Noise
	SYNTHESIZE(bool, m_isOpenGarden, OpenGarden);						   // Map Open Garden
	SYNTHESIZE(bool, m_isOpenMuse, OpenMuse);							   // Map Open Muse 
	SYNTHESIZE(bool, m_isOpenShip, OpenShip);							   // Map Open Ship 

	SYNTHESIZE(bool, m_isUnLocked, UnLocked);							   // Control LockRender
	SYNTHESIZE(bool, m_isLockedRender, LockedRender);					   // Locked Image, Text Render

	SYNTHESIZE(UIImageView*, m_mapParent, mapParent);
	SYNTHESIZE(UITextImageView*, m_mapName, m_mapName);					   // Map Name
	SYNTHESIZE(UITextImageView*, m_mapLength, m_mapLength);				   // Map Length
	SYNTHESIZE(UITextImageView*, m_mapDifficulty, m_mapDifficulty);		   // Map Difficulty

	SYNTHESIZE(UIImageView*, m_LockedRing, m_LockedRing);				   // Locked Case
	SYNTHESIZE(UITextImageView*, m_LockedTextImage, m_LockedTextImage);	   // Locked Text												   
	
};

