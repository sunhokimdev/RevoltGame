#pragma once
class Image
{
public:
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE,	//리소스 파일 pk3, pak
		LOAD_FILE,		//BMP파일
		LOAD_EMPTY,		//빈 비트맵 파일
		LOAD_END
	};

	typedef struct tagImageInfo
	{
		DWORD	resID;
		HDC		hMemDC;
		HBITMAP hBit;
		HBITMAP hOBit;
		float	x;
		float	y;
		int		width;
		int		height;
		int		currentFrameX;	//현재 프레임 X(몇번째 장)
		int		currentFrameY;	//현재 프레임 Y(몇번째 장)
		int		maxFrameX;		//최대 프레임 X(몇번째 장)
		int		maxFrameY;		//초대 프레임 Y(몇번째 장)
		int		frameWidth;		//프레임 이미지 가로크기
		int		frameHeight;	//프레임 이미지 세로크기
		BYTE	loadType;

		tagImageInfo()
		{
			resID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			x = 0;
			y = 0;
			width = 0;
			height = 0;
			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			loadType = LOAD_RESOURCE;
		}
		//같은 구조체지만 구조체 변수에 동적할당했을떄 접근하기위한 포인터 LongPointerIMAGE_INFO
	}IMAGE_INFO, *LPIMAGE_INFO;
private:
	LPIMAGE_INFO		_imageInfo;		//이미지 구조체
	CHAR*				_fileName;		//파일이름
	BOOL				_trans;			//RGB 컬러 날릴껀지 여부
	COLORREF			_transColor;	//날린다면 어떤 컬러로

	BLENDFUNCTION		_blendFunc;		//알파블렌드를 사용키위한 정보
	LPIMAGE_INFO		_blendImage;	//알파블렌드를 사용할 이미지
public:
	Image();
	~Image();
	//초기화 함수 == 빈 비트맵 용
	HRESULT init(int width, int height);
	//초기화 함수 == 리소스 파일 용
	HRESULT init(const DWORD resID, int width, int height,
		BOOL trans = FALSE, COLORREF transColor = FALSE);
	//초기화 함수 == BMP파일 용
	HRESULT init(const char* fileName, int width, int height,
		BOOL trans = FALSE, COLORREF transColor = FALSE);
	HRESULT init(const char* fileName, float x, float y, int width, int height,
		BOOL trans = FALSE, COLORREF transColor = FALSE, int transSize = 0);

	//프레임 이미지 init()
	HRESULT init(const char* fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor);
	HRESULT init(const char* fileName, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor);


	void release(void);
	//도중에 트랜스 컬러 바꿀때가 오면 사용할 함쑤
	void setTransColor(BOOL trans, COLORREF transColor);

	void render(HDC hdc);
	//렌더(그려주는용) hdc, 뿌릴 곳X(left), 뿌릴 곳Y(top)
	void render(HDC hdc, int destX, int destY);
	//렌더					 뿌릴곳X    뿌릴곳Y     뿌려올곳X  뿌려올곳Y    뿌려올가로크기  뿌려올 세로크기
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	//루프렌더(이미지 한장용)
	void loopRender(HDC hdc, const LPRECT drawArea, int offSetX, int offSetY);

	//프레임 렌더
	void frameRender(HDC hdc, int destX, int destY);
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	void alphaRender(HDC hdc, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	//메모리 DC Getter(접근자)
	inline HDC getMemDC(void) { return _imageInfo->hMemDC; }

	//===============================
	// 이미지 관련 Getter, Setter
	//===============================

	inline void setX(float x) { _imageInfo->x = x; }
	inline float getX() { return _imageInfo->x; }

	inline void setY(float y) { _imageInfo->y = y; }
	inline float getY() { return _imageInfo->y; }

	inline void setCenter(float x, float y)
	{
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
	}

	//중점 X
	inline float getCenterX()
	{
		return _imageInfo->maxFrameX <= 0 ?
			_imageInfo->x + (_imageInfo->width / 2) :
			_imageInfo->x + (_imageInfo->frameWidth / 2);
	}

	//중점 Y
	inline float getCenterY()
	{
		return _imageInfo->maxFrameY <= 0 ?
			_imageInfo->y + (_imageInfo->height / 2) :
			_imageInfo->y + (_imageInfo->frameHeight / 2);
	}

	//이미지 가로
	inline int getWidth(void) { return _imageInfo->width; }

	//이미지 세로
	inline int getHeight(void) { return _imageInfo->height; }

	//프레임 관련 getter setter
	inline void setFrameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;
		if (frameX > _imageInfo->maxFrameX) _imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}

	inline void setFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;
		if (frameY > _imageInfo->maxFrameY) _imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}

	inline int getMaxFrameX(void) { return _imageInfo->maxFrameX; }
	inline int getMaxFrameY(void) { return _imageInfo->maxFrameY; }

	inline int getFrameX(void) { return _imageInfo->currentFrameX; }
	inline int getFrameY(void) { return _imageInfo->currentFrameY; }

	inline int getFrameWidth(void) { return _imageInfo->frameWidth; }
	inline int getFrameHeight(void) { return _imageInfo->frameHeight; }

};

