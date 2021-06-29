#include "stdafx.h"
#include "stage_1stFloor_HallA.h"

HRESULT stage_1stFloor_HallA::init()
{
	// 배경
	IMAGEMANAGER->addImage("1stFloor_HallA", "img/stage/stage6/1stFloor_HallA.bmp", 2400, 864, true, RGB(255, 0, 255));
	_background1 = IMAGEMANAGER->findImage("1stFloor_HallA");
	IMAGEMANAGER->addImage("1stFloor_HallA_Pixel", "img/stage/stage6/1stFloor_HallA_Pixel.bmp", 2400, 1092, true, RGB(255, 0, 255));
	_background2 = IMAGEMANAGER->findImage("1stFloor_HallA_Pixel");
	_background3 = IMAGEMANAGER->findImage("BackGround3");

	IMAGEMANAGER->addImage("L3_lockers5", "img/stage/stage6/L3_lockers5.bmp", 555, 279, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("L3_lockers6", "img/stage/stage6/L3_lockers6.bmp", 630, 282, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("L3_pillar7", "img/stage/stage6/L3_pillar7.bmp", 198, 543, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("L3_pillar8", "img/stage/stage6/L3_pillar8.bmp", 207, 864, true, RGB(255, 0, 255), true);

	// 플레이어 초기화
	_player = new player;
	_player->init();
	_tagPlayer = _player->getPlayerData();
	_tagPlayer->state = new idleState;
	_tagPlayer->state->enter(_player);
	_tagPlayer->y = WINSIZEY;
	// 문 세팅
	_door1 = RectMakeCenter(200, 770, 200, 260);
	_door1Alpha = 0;
	_door2 = RectMakeCenter(1010, 600, 280, 40);
	_door2Alpha = 0;

	// 카메라 세팅
	RENDERMANAGER->setCameraX(-(_tagPlayer->x - WINSIZEX / 2));
	RENDERMANAGER->setCameraY(-(_tagPlayer->y - WINSIZEY / 2 + 114 - 200 - _tagPlayer->z));
	if (_background1->getHeight() - WINSIZEY / 2 + 114 < _tagPlayer->y - 200 - _tagPlayer->z)
	{
		RENDERMANAGER->setCameraY(-(_background1->getHeight() - WINSIZEY * 3/4  ));
	}
	return S_OK;
}

void stage_1stFloor_HallA::release()
{
}

void stage_1stFloor_HallA::update()
{
	_player->update();
	_tagPlayer = _player->getPlayerData();

	cameraWork();
	doorWork();
	pixelCollision(_tagPlayer,"1stFloor_HallA_Pixel",_player);
}

void stage_1stFloor_HallA::render()
{
	RENDERMANAGER->push_BackRenderInfo(-1000, "1stFloor_HallA", 0, 114, true);
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		RENDERMANAGER->push_BackRenderInfo(-999, "1stFloor_HallA_Pixel", 0, 0, true);
	}
	////////////////////
	_player->render();

	RENDERMANAGER->push_BackRenderInfo(114, "L3_lockers5", 320, 390, true);
	RENDERMANAGER->push_BackRenderInfo(0, "L3_lockers6", 1452, 390, true);
	RENDERMANAGER->push_BackRenderInfo(114, "L3_pillar7", 1326, 114, true);
	RENDERMANAGER->push_BackRenderInfo(3000, "L3_pillar8", 1700, 114, true, true, 150);

	RENDERMANAGER->push_BackRenderInfo(3000, "UI_UNLOCKED_DOOR", 210, 580, false, true, _door1Alpha);
	RENDERMANAGER->push_BackRenderInfo(3000, "UI_UNLOCKED_DOOR", 1010, 450, false, true, _door2Alpha);

	// 이 위에 렌더 이미지 인포
	RENDERMANAGER->render(getMemDC());
	_background3->render(getMemDC());

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		RECT rc = RectMake(_door1.left + RENDERMANAGER->getCameraX(), _door1.top + RENDERMANAGER->getCameraY(),
			_door1.right - _door1.left, _door1.bottom - _door1.top);
		Rectangle(getMemDC(), rc);
		rc = RectMake(_door2.left + RENDERMANAGER->getCameraX(), _door2.top + RENDERMANAGER->getCameraY(),
			_door2.right - _door2.left, _door2.bottom - _door2.top);
		Rectangle(getMemDC(), rc);
		rc = RectMake(_tagPlayer->rc.left + RENDERMANAGER->getCameraX(), _tagPlayer->rc.top + RENDERMANAGER->getCameraY(), _tagPlayer->rc.right - _tagPlayer->rc.left, _tagPlayer->rc.bottom - _tagPlayer->rc.top);
		Rectangle(getMemDC(), rc);
	}
}

void stage_1stFloor_HallA::cameraWork()
{
	if (_tagPlayer->x > WINSIZEX / 2)
	{
		RENDERMANAGER->setCameraX(-(_tagPlayer->x - WINSIZEX / 2));
	}
	if (RENDERMANAGER->getCameraX() < -_background1->getWidth() + WINSIZEX)
	{
		RENDERMANAGER->setCameraX(-_background1->getWidth() + WINSIZEX);
	}
	if (_tagPlayer->y - 200 - _tagPlayer->z < _background1->getHeight() - WINSIZEY / 2 + 114)
	{
		RENDERMANAGER->setCameraY(-(_tagPlayer->y - WINSIZEY / 2 + 114 - 200 - _tagPlayer->z));
	}
	if (_tagPlayer->y - _tagPlayer->z < WINSIZEY / 2 - 114 + 200)
	{
		RENDERMANAGER->setCameraY(0);
	}
}

void stage_1stFloor_HallA::doorWork()
{
	if (IntersectRect(&_temp, &_tagPlayer->rc, &_door1))
	{
		if (_door1Alpha < 200)
			_door1Alpha += 5;
		if (KEYMANAGER->isOnceKeyDown('Y'))
		{
			RENDERMANAGER->setCameraX(0);
			RENDERMANAGER->setCameraY(0);
			SCENEMANAGER->changeScene("1층방");
		}
	}
	else if (_door1Alpha > 0)
	{
		_door1Alpha -= 5;
	}

	if (IntersectRect(&_temp, &_tagPlayer->rc, &_door2))
	{
		if (_door2Alpha < 200)
			_door2Alpha += 5;
		if (KEYMANAGER->isOnceKeyDown('Y'))
		{
			RENDERMANAGER->setCameraX(0);
			RENDERMANAGER->setCameraY(0);
			SCENEMANAGER->changeScene("2층홀B");
		}
	}
	else if (_door2Alpha > 0)
	{
		_door2Alpha -= 5;
	}
}
