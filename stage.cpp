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

void stage::pixelCollision(tagPlayer* _tagplayer, string strkey, player* _player)
{
	_tagPlayer = _tagplayer;
	for (int i = _tagPlayer->rc.left; i <= _tagPlayer->rc.left + 20; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage(strkey)->getMemDC(), i, (_tagPlayer->rc.top + _tagPlayer->rc.bottom) / 2);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
		if ((r == 0 && g == 255 && b == 0) || (r == 255 && g == 0 && b == 0 && 200 > _tagPlayer->z) || (r == 0 && g == 0 && b == 255 && 100 > _tagPlayer->z))

		{
			_tagPlayer->x = i + (_tagPlayer->rc.right - _tagPlayer->rc.left) / 2;
		}
		
	}
	for (int i = _tagPlayer->rc.right; i >= _tagPlayer->rc.right - 20; i--)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage(strkey)->getMemDC(), i, (_tagPlayer->rc.top + _tagPlayer->rc.bottom) / 2);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
		if ((r == 0 && g == 255 && b == 0) || (r == 255 && g == 0 && b == 0 && 200 > _tagPlayer->z) || (r == 0 && g == 0 && b == 255 && 100 > _tagPlayer->z))

		{
			_tagPlayer->x = i - (_tagPlayer->rc.right - _tagPlayer->rc.left)/2;
		}
		
	}
	
	for (int i = _tagPlayer->rc.bottom; i >= _tagPlayer->rc.bottom - 15; i--)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage(strkey)->getMemDC(), (_tagPlayer->rc.left + _tagPlayer->rc.right) / 2, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
		if ((r == 0 && g == 255 && b == 0)||(r == 255 && g == 0 && b == 0 && 200 > _tagPlayer->z) || (r == 0 && g == 0 && b == 255 && 100 > _tagPlayer->z))
		{
			_tagPlayer->y = i;
		}

		if (r == 255 && g == 0 && b == 0)
		{
			if (_tagPlayer->z < 210 && _tagPlayer->z > 190) 
			{
				_tagPlayer->z = 200;
				_tagPlayer->state = new idleState;
				
			}
		}
		if (r == 0 && g == 0 && b == 255)
		{
			if (_tagPlayer->z < 210 && _tagPlayer->z > 190)
			{
				_tagPlayer->z = 100;
				_tagPlayer->state = new idleState;
			}
		}

	}
	for (int i = _tagPlayer->rc.top + 10; i <= _tagPlayer->rc.top + 20; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage(strkey)->getMemDC(), (_tagPlayer->rc.left + _tagPlayer->rc.right) / 2, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
		if ((r == 0 && g == 255 && b == 0) || (r == 255 && g == 0 && b == 0 && 200 > _tagPlayer->z) || (r == 0 && g == 0 && b == 255 && 100 > _tagPlayer->z))

		{
			_tagPlayer->y = i + 30;
		}

	}

}
