#include "stdafx.h"
#include "renderManager.h"

HRESULT renderManager::init()
{
	_cameraX = 0;
	_cameraY = 0;
	return S_OK;
}

void renderManager::push_BackRenderInfo(float zOrder_Bottom, const char * imagekey, float x, float y, bool _isLeftTop, bool _isBlend, BYTE _alpha)
{
	tagUnit _Unit;
	ZeroMemory(&_Unit, sizeof(_Unit));

	_Unit.x = x;
	_Unit.y = y;
	_Unit.ani = nullptr;
	_Unit.imageKey = imagekey;
	_Unit.isLeftTop = _isLeftTop;
	_Unit.isBlend = _isBlend;
	_Unit.alpha = _alpha;


	_Unit.img = IMAGEMANAGER->findImage(_Unit.imageKey);
	_Unit.isAni = false;
	_Unit.isFrame = false;

	_zOrder.push_back(make_pair(zOrder_Bottom, _Unit));
}

void renderManager::push_BackAniRenderInfo(float zOrder_Bottom, const char * imagekey, animation * _animation, float x, float y, bool _isLeftTop, bool _isBlend, BYTE _alpha)
{
	tagUnit _Unit;
	ZeroMemory(&_Unit, sizeof(_Unit));

	
	_Unit.x = x;
	_Unit.y = y;
	_Unit.ani = _animation;
	_Unit.imageKey = imagekey;
	_Unit.isLeftTop = _isLeftTop;
	_Unit.isBlend = _isBlend;
	_Unit.alpha = _alpha;
	

	_Unit.img = IMAGEMANAGER->findImage(_Unit.imageKey);
	_Unit.isAni = true;
	_Unit.isFrame = false;

	_zOrder.push_back(make_pair(zOrder_Bottom, _Unit));
}

void renderManager::push_BackEffectRenderInfo(float zOrder_Bottom, animation * ani, image * img, float x, float y, bool isLeftTop, bool _isBlend, BYTE alpha)
{
	tagUnit _Unit;
	ZeroMemory(&_Unit, sizeof(_Unit));


	_Unit.x = x;
	_Unit.y = y;
	_Unit.ani = ani;
	_Unit.isLeftTop = isLeftTop;
	_Unit.isBlend = _isBlend;
	_Unit.alpha = alpha;
	_Unit.img = img;
	_Unit.isAni = true;
	_Unit.isFrame = false;

	_zOrder.push_back(make_pair(zOrder_Bottom, _Unit));
}

void renderManager::push_BackFrameRenderInfo(float zOrder_Bottom, const char * imagekey, float x, float y, bool _isLeftTop, bool _isBlend, BYTE _alpha)
{
	tagUnit _Unit;
	ZeroMemory(&_Unit, sizeof(_Unit));

	_Unit.x = x;
	_Unit.y = y;
	_Unit.frameX = -1;
	_Unit.frameY = -1;
	_Unit.imageKey = imagekey;
	_Unit.isLeftTop = _isLeftTop;
	_Unit.isBlend = _isBlend;
	_Unit.alpha = _alpha;

	_Unit.img = IMAGEMANAGER->findImage(_Unit.imageKey);
	_Unit.isAni = false;
	_Unit.isFrame = true;

	_zOrder.push_back(make_pair(zOrder_Bottom, _Unit));
}

void renderManager::push_BackFrameRenderInfo(float zOrder_Bottom, const char * imagekey, float x, float y, int frameX, int frameY, bool _isLeftTop, bool _isBlend, BYTE _alpha)
{
	tagUnit _Unit;
	ZeroMemory(&_Unit, sizeof(_Unit));

	_Unit.x = x;
	_Unit.y = y;
	_Unit.frameX = frameX;
	_Unit.frameY = frameY;
	_Unit.imageKey = imagekey;
	_Unit.isLeftTop = _isLeftTop;
	_Unit.isBlend = _isBlend;
	_Unit.alpha = _alpha;

	_Unit.img = IMAGEMANAGER->findImage(_Unit.imageKey);
	_Unit.isAni = false;
	_Unit.isFrame = true;

	_zOrder.push_back(make_pair(zOrder_Bottom, _Unit));
}




void renderManager::push_BackFrameImageRenderInfo(float zOrder_Bottom, image * imagekey, float x, float y, int frameX, int frameY, bool _isLeftTop, bool _isBlend, BYTE _alpha)
{
	tagUnit _Unit;
	ZeroMemory(&_Unit, sizeof(_Unit));

	_Unit.x = x;
	_Unit.y = y;
	_Unit.frameX = frameX;
	_Unit.frameY = frameY;
	_Unit.isLeftTop = _isLeftTop;
	_Unit.isBlend = _isBlend;
	_Unit.alpha = _alpha;

	_Unit.img = imagekey;
	_Unit.isAni = false;
	_Unit.isFrame = true;

	_zOrder.push_back(make_pair(zOrder_Bottom, _Unit));
}

void renderManager::release()
{

}

void renderManager::render(HDC _hdc)
{
	// 정렬 해줌
	mergeSort(_zOrder, 0, _zOrder.size() - 1);

	for (_zOrder_vector_iter iter = _zOrder.begin(); iter != _zOrder.end(); ++iter)
	{
		// 화면 밖은 안그림
		if (iter->second.x + iter->second.img->getWidth() + _cameraX >= 0  && iter->second.x + _cameraX <= WINSIZEX)
		// 프레임 이미지 인가?
		if (iter->second.isFrame) 
		{
			// 프레임 x, y를 쓰는가?
			if (iter->second.frameX != -1 && iter->second.frameY != -1)
			{
				if (iter->second.isBlend) // 블랜드 처리 함?
				{
					// 레프트탑?
					if (iter->second.isLeftTop)
					{
						IMAGEMANAGER->alphaFrameRender(iter->second.imageKey, _hdc, iter->second.x + _cameraX, iter->second.y + _cameraY, iter->second.frameX, iter->second.frameY,iter->second.alpha);

					}
					else // 레프트탑 no
					{
						IMAGEMANAGER->alphaFrameRender(iter->second.imageKey, _hdc, iter->second.x - iter->second.img->getFrameWidth() / 2 + _cameraX, iter->second.y - iter->second.img->getFrameHeight() / 2 + _cameraY, iter->second.frameX, iter->second.frameY, iter->second.alpha);
					}

				}
				else // blend 안함
				{
					// 레프트탑?
					if (iter->second.isLeftTop)
					{
						iter->second.img->frameRender(_hdc, iter->second.x + _cameraX, iter->second.y + _cameraY, iter->second.frameX, iter->second.frameY);
					}
					else // 레프트탑 no
					{
						iter->second.img->frameRender(_hdc, iter->second.x - iter->second.img->getFrameWidth() / 2 + _cameraX, iter->second.y - iter->second.img->getFrameHeight() / 2 + _cameraY, iter->second.frameX, iter->second.frameY);
					}
				}
			}
			else // 응 안써
			{
				if (iter->second.isBlend) // 블랜드 처리 함?
				{
					// 레프트탑?
					if (iter->second.isLeftTop)
					{
						IMAGEMANAGER->alphaFrameRender(iter->second.imageKey, _hdc, iter->second.x + _cameraX, iter->second.y + _cameraY, iter->second.alpha);

					}
					else // 레프트탑 no
					{
						IMAGEMANAGER->alphaFrameRender(iter->second.imageKey, _hdc, iter->second.x - iter->second.img->getFrameWidth() / 2 + _cameraX, iter->second.y - iter->second.img->getFrameHeight() / 2 + _cameraY, iter->second.alpha);

					}
				}
				else // blend 안함
				{
					// 레프트탑?
					if (iter->second.isLeftTop)
					{
						IMAGEMANAGER->frameRender(iter->second.imageKey, _hdc, iter->second.x + _cameraX, iter->second.y + _cameraY);

					}
					else // 레프트탑 no
					{
					iter->second.img->frameRender(_hdc, iter->second.x - iter->second.img->getFrameWidth() / 2 + _cameraX, iter->second.y - iter->second.img->getFrameHeight() / 2 + _cameraY);

					}
				}
			}
		}
		else if (iter->second.isAni) 
		{
			if (iter->second.isBlend) // 블랜드 처리 함?
			{
				// 레프트탑?
				if (iter->second.isLeftTop)
				{
					iter->second.img->alphaAniRender(_hdc, iter->second.x + _cameraX, iter->second.y + _cameraY, iter->second.ani, iter->second.alpha);
				}
				else
				{
					iter->second.img->alphaAniRender(_hdc, iter->second.x - iter->second.img->getFrameWidth() / 2 + _cameraX, iter->second.y - iter->second.img->getFrameHeight() / 2 + _cameraY, iter->second.ani, iter->second.alpha);
				}
			}
			else // 블랜드 안함
			{
				// 레프트탑?
				if (iter->second.isLeftTop)
				{
					iter->second.img->aniRender(_hdc, iter->second.x + _cameraX, iter->second.y + _cameraY, iter->second.ani);
				}
				else
				{
					iter->second.img->aniRender(_hdc, iter->second.x - iter->second.img->getFrameWidth() / 2 + _cameraX, iter->second.y - iter->second.img->getFrameHeight() / 2 + _cameraY, iter->second.ani);
				}
			}

		}
		else 
		{
			if (iter->second.isBlend)
			{
				if (iter->second.isLeftTop)
				{
					iter->second.img->alphaRender(_hdc, iter->second.x + _cameraX, iter->second.y + _cameraY, iter->second.alpha);
				}
				else
				{
					iter->second.img->alphaRender(_hdc, iter->second.x + _cameraX - iter->second.img->getWidth()/2, iter->second.y + _cameraY - iter->second.img->getHeight()/2, iter->second.alpha);
				}
			}
			else
			{
				if (iter->second.isLeftTop)
				{
					iter->second.img->render(_hdc, iter->second.x + _cameraX, iter->second.y + _cameraY);

				}
				else
				{
					iter->second.img->render(_hdc, iter->second.x + _cameraX - iter->second.img->getWidth()/2, iter->second.y - iter->second.img->getHeight()/2 + _cameraY);
				}

			}

		}
		
	}
	// 벡터 클리어 및 리사이즈 
	_zOrder.clear();
	_zOrder.resize(0);
}

// 합병 정렬 
void renderManager::mergeSort(vector<pair<float, tagUnit>>& v, int s, int e)
{
	if (s >= e) return;

	int m = (s + e) / 2;
	// divide 분할
	mergeSort(v, s, m); // s ~ m
	mergeSort(v, m + 1, e); // m+1 ~ e

	// conquer
	merge(v, s, e, m);
}

void renderManager::merge(vector<pair<float, tagUnit>>& v, int s, int e, int m)
{
	vector<pair<float, tagUnit>> ret(e + 1);
	int ret_idx = 0; //리턴 인덱스
	int firstidx = s; //맨 첫 인덱스
	int secondidx = m + 1; //


	while (firstidx <= m && secondidx <= e)
	{
		if (v[firstidx].first < v[secondidx].first) ret[ret_idx++] = v[firstidx++];
		else ret[ret_idx++] = v[secondidx++];
	}

	while (firstidx <= m) ret[ret_idx++] = v[firstidx++];
	while (secondidx <= e) ret[ret_idx++] = v[secondidx++];

	for (int k = s, ret_idx = 0; k <= e; k++, ret_idx++)
		v[k] = ret[ret_idx];
}
