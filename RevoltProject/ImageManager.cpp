#include "stdafx.h"
#include "ImageManager.h"


ImageManager::ImageManager()
{
}


ImageManager::~ImageManager()
{
}

HRESULT ImageManager::init(void)
{
	return S_OK;
}

void ImageManager::release(void)
{
	deleteAll();
}

Image * ImageManager::addImage(std::string strKey, int width, int height)
{
	Image* img = findImage(strKey);

	//이미지가 있으면 반환한다
	if (img) return img;

	img = new Image;

	//이미지 초기화가 실패했으면
	if (FAILED(img->init(width, height)))
	{
		SAFE_DELETE(img);

		return NULL;
	}

	//여기까지 왔다면 초기화가 잘 되었을 것.
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

Image * ImageManager::addImage(std::string strKey, const DWORD resID, int width, int height, bool trans, COLORREF transColor)
{
	Image* img = findImage(strKey);

	//이미지가 있으면 반환한다
	if (img) return img;

	img = new Image;

	//이미지 초기화가 실패했으면
	if (FAILED(img->init(resID, width, height, trans, transColor)))
	{
		SAFE_DELETE(img);

		return NULL;
	}

	//여기까지 왔다면 초기화가 잘 되었을 것.
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

Image * ImageManager::addImage(std::string strKey, const char * fileName, int width, int height, bool trans, COLORREF transColor)
{
	Image* img = findImage(strKey);

	//이미지가 있으면 반환한다
	if (img) return img;

	img = new Image;

	//이미지 초기화가 실패했으면
	if (FAILED(img->init(fileName, width, height, trans, transColor)))
	{
		SAFE_DELETE(img);

		return NULL;
	}

	//여기까지 왔다면 초기화가 잘 되었을 것.
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

Image * ImageManager::addImage(std::string strKey, const char * fileName, float x, float y, int width, int height, bool trans, COLORREF transColor)
{
	Image* img = findImage(strKey);

	//이미지가 있으면 반환한다
	if (img) return img;

	img = new Image;

	//이미지 초기화가 실패했으면
	if (FAILED(img->init(fileName, x, y, width, height, trans, transColor)))
	{
		SAFE_DELETE(img);

		return NULL;
	}

	//여기까지 왔다면 초기화가 잘 되었을 것.
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

Image * ImageManager::addImage(std::string strKey, const char * fileName, float x, float y, int width, int height, bool trans, COLORREF transColor, int transSize)
{
	Image* img = findImage(strKey);

	//이미지가 있으면 반환한다
	if (img) return img;

	img = new Image;

	//이미지 초기화가 실패했으면
	if (FAILED(img->init(fileName, x, y, width, height, trans, transColor, transSize)))
	{
		SAFE_DELETE(img);

		return NULL;
	}

	//여기까지 왔다면 초기화가 잘 되었을 것.
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

Image * ImageManager::addFrameImage(std::string strKey, const char * fileName, float x, float y, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor)
{
	Image* img = findImage(strKey);

	//이미지가 있으면 반환한다
	if (img) return img;

	img = new Image;

	//이미지 초기화가 실패했으면
	if (FAILED(img->init(fileName, x, y, width, height, frameX, frameY, trans, transColor)))
	{
		SAFE_DELETE(img);

		return NULL;
	}

	//여기까지 왔다면 초기화가 잘 되었을 것.
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

Image * ImageManager::addFrameImage(std::string strKey, const char * fileName, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor)
{
	Image* img = findImage(strKey);

	//이미지가 있으면 반환한다
	if (img) return img;

	img = new Image;

	//이미지 초기화가 실패했으면
	if (FAILED(img->init(fileName, width, height, frameX, frameY, trans, transColor)))
	{
		SAFE_DELETE(img);

		return NULL;
	}

	//여기까지 왔다면 초기화가 잘 되었을 것.
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

Image * ImageManager::findImage(std::string strKey)
{
	mapImageIter key = _mImageList.find(strKey);

	//키 값이 있으면
	if (key != _mImageList.end())
	{
		return key->second;
	}

	return NULL;
}

BOOL ImageManager::deleteImage(std::string strKey)
{
	mapImageIter key = _mImageList.find(strKey);

	if (key != _mImageList.end())
	{
		key->second->release();
		SAFE_DELETE(key->second);
		_mImageList.erase(key);

		return true;
	}

	return false;
}

BOOL ImageManager::deleteAll(void)
{
	mapImageIter iter = _mImageList.begin();

	for (; iter != _mImageList.end();)
	{
		if (iter->second != NULL)
		{
			SAFE_DELETE(iter->second);
			iter = _mImageList.erase(iter);
		}
		else
		{
			++iter;
		}
	}

	_mImageList.clear();

	return TRUE;
}

void ImageManager::render(std::string strKey, HDC hdc)
{
	Image* img = findImage(strKey);

	if (img) img->render(hdc);
}

void ImageManager::render(std::string strKey, HDC hdc, int destX, int destY)
{
	Image* img = findImage(strKey);

	if (img) img->render(hdc, destX, destY);
}

void ImageManager::render(std::string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	Image* img = findImage(strKey);

	if (img) img->render(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight);
}

void ImageManager::frameRender(std::string strKey, HDC hdc, int destX, int destY)
{
	Image* img = findImage(strKey);

	if (img) img->frameRender(hdc, destX, destY);
}

void ImageManager::frameRender(std::string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	Image* img = findImage(strKey);

	if (img) img->frameRender(hdc, destX, destY, currentFrameX, currentFrameY);
}

void ImageManager::loopRender(std::string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	Image* img = findImage(strKey);

	if (img) img->loopRender(hdc, drawArea, offsetX, offsetY);
}

void ImageManager::alphaRender(std::string strKey, HDC hdc, BYTE alpha)
{
	Image* img = findImage(strKey);

	if (img) img->alphaRender(hdc, alpha);
}

void ImageManager::alphaRender(std::string strKey, HDC hdc, int destX, int destY, BYTE alpha)
{
	Image* img = findImage(strKey);

	if (img) img->alphaRender(hdc, destX, destY, alpha);
}

void ImageManager::alphaRender(std::string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	Image* img = findImage(strKey);

	if (img) img->alphaRender(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight, alpha);
}
