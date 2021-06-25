#pragma once
#include "singletonBase.h"

struct tagUnit
{
	// 그려줄 위치
	float x, y;
	// 이미지 이름
	const char* imageKey;
	// 프레임 x, y
	int frameX, frameY;
	// lefttop?
	bool isLeftTop;
	// blend?
	bool isBlend;
	// frame?
	bool isFrame;
	// ani?
	bool isAni;
	// blend val
	BYTE alpha;
	// image
	image* img;
	// animation
	animation* ani;
};

class renderManager :
	public singletonBase<renderManager>
{
private:
	// 타입 정의
	typedef vector<pair<float, tagUnit>> _zOrder_vector;
	typedef vector<pair<float, tagUnit>>::iterator _zOrder_vector_iter;

private: 
	// 카메라 x, y
	float _cameraX;
	float _cameraY;
	// 이미지 저장하는 곳
	_zOrder_vector _zOrder;

public:
	HRESULT init();

	void push_BackRenderInfo(float zOrder_Bottom, const char* imagekey, float x = 0, float y = 0, bool _isLeftTop = FALSE, bool  _isBlend = FALSE, BYTE _alpha = 255);

	void push_BackFrameRenderInfo(float zOrder_Bottom, const char* imagekey, float x = 0, float y = 0,  bool _isLeftTop = FALSE, bool  _isBlend = FALSE,
							BYTE _alpha = 255);
	void push_BackFrameRenderInfo(float zOrder_Bottom, const char* imagekey, float x, float y, int frameX, int frameY, bool _isLeftTop = FALSE, bool  _isBlend = FALSE,
		BYTE _alpha = 255);

	void push_BackAniRenderInfo(float zOrder_Bottom, const char* imagekey, animation* _animation, float x = 0, float y = 0, bool _isLeftTop = FALSE, bool _isBlend = FALSE, BYTE _alpha = 255);
	void push_BackEffectRenderInfo(float zOrder_Bottom, animation* ani, image* img, float x = 0, float y = 0, bool isLeftTop = false, bool _isBlend = false, BYTE alpha = 255);
	
	void push_BackFrameImageRenderInfo(float zOrder_Bottom, image* imagekey, float x = 0, float y = 0, int frameX = -1, int frameY = -1, bool _isLeftTop = FALSE, bool  _isBlend = FALSE,
		BYTE _alpha = 255);
	void release();
	void render(HDC _hdc);

	void mergeSort(vector<pair<float, tagUnit>>& v, int s, int e);
	void merge(vector<pair<float, tagUnit>>& v, int s, int e, int m);
	
	void setCameraX(float x) { _cameraX = x; }
	void setCameraY(float y) { _cameraY = y; }
	float getCameraX() { return _cameraX; }
	float getCameraY() { return _cameraY; }
};	

