#pragma once

#include "Image.h"

#define g_pImageManager ImageManager::GetInstance()

class ImageManager
{
public:
	SINGLETONE(ImageManager);
private:
	typedef std::map<std::string, Image*> mapImageList;
	typedef std::map<std::string, Image*>::iterator mapImageIter;
	mapImageList _mImageList;
public:
	HRESULT init(void);
	void release(void);

	Image* addImage(std::string strKey, int width, int height);

	Image* addImage(std::string strKey, const DWORD resID, int width, int height, bool trans, COLORREF transColor);
	Image* addImage(std::string strKey, const char* fileName, int width, int height, bool trans, COLORREF transColor);
	Image* addImage(std::string strKey, const char* fileName, float x, float y, int width, int height, bool trans, COLORREF transColor);
	Image* addImage(std::string strKey, const char* fileName, float x, float y, int width, int height, bool trans, COLORREF transColor, int transSize);

	//프레임 이미지 추가
	Image* addFrameImage(std::string strKey, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor);
	Image* addFrameImage(std::string strKey, const char* fileName, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor);

	//이미지 키 값으로 찾는 함수
	Image* findImage(std::string strKey);

	BOOL deleteImage(std::string strKey);

	BOOL deleteAll(void);

	void render(std::string strKey, HDC hdc);
	void render(std::string strKey, HDC hdc, int destX, int destY);
	void render(std::string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	//프레임 렌더랑 루프 렌더
	void frameRender(std::string strKey, HDC hdc, int destX, int destY);
	void frameRender(std::string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	void loopRender(std::string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);

	void alphaRender(std::string strKey, HDC hdc, BYTE alpha);
	void alphaRender(std::string strKey, HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(std::string strKey, HDC hdc, int destX, int destY,
		int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);
};

