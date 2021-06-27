#include "stdafx.h"
#include "stage.h"

HRESULT stage::init()
{
	return S_OK;
}

void stage::release()
{
}

void stage::update()
{
}

void stage::render()
{
}

void stage::pixelCollision(tagPlayer* _tagplayer)
{
	_tagPlayer = _tagplayer;
	for (int i = _tagPlayer->rc.left; i <= _tagPlayer->rc.left + 20; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("BackGround")->getMemDC(), i, (_tagPlayer->rc.top + _tagPlayer->rc.bottom) / 2);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
		if (r == 0 && g == 255 && b == 0)
		{
			_tagPlayer->x = i;
		}
	}
	for (int i = _tagPlayer->rc.right; i >= _tagPlayer->rc.right - 20; i--)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("BackGround")->getMemDC(), i, (_tagPlayer->rc.top + _tagPlayer->rc.bottom) / 2);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
		if (r == 0 && g == 255 && b == 0)
		{
			_tagPlayer->x = i - (_tagPlayer->rc.right - _tagPlayer->rc.left);
		}
	}
	for (int i = _tagPlayer->rc.top + 10; i <= _tagPlayer->rc.top + 20; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("BackGround")->getMemDC(), (_tagPlayer->rc.left + _tagPlayer->rc.right) / 2, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
		if (r == 0 && g == 255 && b == 0)
		{
			_tagPlayer->y = i - 155;
		}
	}

	for (int i = _tagPlayer->rc.bottom; i >= _tagPlayer->rc.bottom - 15; i--)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("BackGround")->getMemDC(), (_tagPlayer->rc.left + _tagPlayer->rc.right) / 2, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
		if (r == 0 && g == 255 && b == 0)
		{
			_tagPlayer->y = i - 210;
		}
	}
}
