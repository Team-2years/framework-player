#include "stdafx.h"
#include "Enemy_Basic.h"
#include "Enemy_Idle.h"
#include "Enemy_Move.h"
#include "Enemy_Attack.h"
#include "Enemy_Die.h"


void Enemy_Basic::input_state_data(int targetX, int targetY)
{
	Enemy_State* _newState = _state->input_state(this,true,targetX,targetY); //새로 넣어줄 state 클래스 임시변수



	if (_newState != nullptr)//만약 현재 데이터가 있으면 현재 데이터를 삭제 후, nullptr로 만들어줌
	{
		SAFE_DELETE(_state);
		_state = _newState;
		_state->enter_this_state(this);
	}
}

HRESULT Enemy_Basic::init(int _x, int _y, const char * _imageName,int _Hp)
{
	_EnemyInfo.x = _x;
	_EnemyInfo.y = _y;

	_EnemyInfo.imageName = _imageName;
	_EnemyInfo.imageName_RenderManager = _EnemyInfo.imageName;

	//_EnemyInfo._image = new image;
	//_EnemyInfo._image = IMAGEMANAGER->findImage(_EnemyInfo.imageName);

	_state = new Enemy_Idle();
	_state->enter_this_state(this);


	TIMEMANAGER->init();

	//_EnemyInfo._rc = RectMakeCenter(_EnemyInfo.x, _EnemyInfo.y, _EnemyInfo._image->getFrameWidth(), _EnemyInfo._image->getFrameHeight());
	_EnemyInfo._rc = RectMakeCenter(_EnemyInfo.x, _EnemyInfo.y, _EnemyInfo._image->getFrameWidth(), _EnemyInfo._image->getFrameHeight());


	_EnemyInfo.Hp = _Hp;

	_EnemyInfo.isRight = true;

	testText = "NON";

	_EnemyInfo.range = 400;

	_EnemyInfo.ShedowRect = RectMakeCenter(_EnemyInfo.x, _EnemyInfo._rc.bottom, 80, 20);

	return S_OK;
}

void Enemy_Basic::update(int targetX, int targetY)
{

	input_state_data(targetX, targetY);
	
	_state->update(this, targetX, targetY);

	_EnemyInfo._rc = RectMakeCenter(_EnemyInfo.x, _EnemyInfo.y, _EnemyInfo._image->getFrameWidth(), _EnemyInfo._image->getFrameHeight());
	_EnemyInfo.ShedowRect = RectMakeCenter(_EnemyInfo.x, _EnemyInfo._rc.bottom, 80, 20);

	//디버깅용
	//ImageUpdateFunc();	
	//Controller(_FieldImage);


	

}


void Enemy_Basic::release()
{
}

void Enemy_Basic::render()
{
	Rectangle(getMemDC(), _EnemyInfo._rc);


	_EnemyInfo._image->frameRender(getMemDC(), 
		_EnemyInfo.x - _EnemyInfo._image->getFrameWidth()/2,
		_EnemyInfo.y - _EnemyInfo._image->getFrameHeight()/2,
		_EnemyInfo._image->getFrameX(), _EnemyInfo._image->getFrameY());
	

	Rectangle(getMemDC(), _EnemyInfo.ShedowRect);

	//RENDERMANAGER->push_BackFrameImageRenderInfo(_EnemyInfo._rc.bottom,
	//	);


	char str[128];

	sprintf_s(str,testText);

	TextOut(getMemDC(), _EnemyInfo.x - 20, _EnemyInfo.y - 60, str, strlen(str));
	
}


void Enemy_Basic::set_Enemy_State(Enemy_State * _new_State)
{
	_state = _new_State;

	_state->enter_this_state(this);
	

}

void Enemy_Basic::Controller(image* _FieldImage)
{

	//if (KEYMANAGER->isStayKeyDown(VK_LEFT)) moveLeft(_FieldImage);
	//if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) moveRight(_FieldImage);
	//if (KEYMANAGER->isStayKeyDown(VK_UP)) moveUp(_FieldImage);
	//if (KEYMANAGER->isStayKeyDown(VK_DOWN)) moveDown(_FieldImage);
}

void Enemy_Basic::moveLeft(image* _FieldImage)
{
	if (_EnemyInfo.isRight)
	{
		_EnemyInfo.isRight = false;
		_EnemyInfo._image->setFrameX(_EnemyInfo._image->getMaxFrameX());
	}
	//_image->setX(_image->getX() - 3);
	_EnemyInfo.x -= 3;

	COLORREF FieldPixel = GetPixel(_FieldImage->getMemDC(), _EnemyInfo._rc.left, _EnemyInfo._rc.bottom);

	int r = GetRValue(FieldPixel);
	int g = GetGValue(FieldPixel);
	int b = GetBValue(FieldPixel);

	if (!(r == 255 && g == 0 && b == 255)) _EnemyInfo.x += 3;

}

void Enemy_Basic::moveRight(image* _FieldImage)
{
	if (!_EnemyInfo.isRight)
	{
		_EnemyInfo.isRight = true;
		_EnemyInfo._image->setFrameX(_EnemyInfo._image->getMaxFrameX());
	}
	//_image->setX(_image->getX() - 3);
	_EnemyInfo.x += 3;

	COLORREF FieldPixel = GetPixel(_FieldImage->getMemDC(), _EnemyInfo._rc.right, _EnemyInfo._rc.bottom);

	int r = GetRValue(FieldPixel);
	int g = GetGValue(FieldPixel);
	int b = GetBValue(FieldPixel);

	if (!(r == 255 && g == 0 && b == 255)) _EnemyInfo.x -= 3;
}

void Enemy_Basic::moveUp(image* _FieldImage)
{
	
	

	COLORREF FieldPixel = GetPixel(_FieldImage->getMemDC(), _EnemyInfo.x, _EnemyInfo._rc.bottom-5); //y + _image->getFrameHeight()/2);

	int r = GetRValue(FieldPixel);
	int g = GetGValue(FieldPixel);
	int b = GetBValue(FieldPixel);

	

	_EnemyInfo.y -= 3;

	if (!(r == 255 && g == 0 && b == 255)) _EnemyInfo.y += 3;

	

}

void Enemy_Basic::moveDown(image* _FieldImage)
{
	_EnemyInfo.y += 3;

	COLORREF FieldPixel = GetPixel(_FieldImage->getMemDC(), _EnemyInfo.x, _EnemyInfo.y + _EnemyInfo._image->getFrameHeight()/2);

	int r = GetRValue(FieldPixel);
	int g = GetGValue(FieldPixel);
	int b = GetBValue(FieldPixel);

	if (!(r == 255 && g == 0 && b == 255)) _EnemyInfo.y -= 3;
}
