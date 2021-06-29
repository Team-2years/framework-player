#include "stdafx.h"
#include "stage_lobby.h"

HRESULT stage_lobby::init()
{
	// 배경
	IMAGEMANAGER->addImage("lobby_l1_debris_background", "img/stage/stage11/lobby_l1_debris_background.bmp", 2769, 1080, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("lobby_l1_background", "img/stage/stage11/lobby_l1_background.bmp", 2769, 1080, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("lobby_l1_background_Pixel", "img/stage/stage11/lobby_l1_background_Pixel.bmp", 2769, 1308, true, RGB(255, 0, 255));
	_background2 = IMAGEMANAGER->findImage("lobby_l1_background_Pixel");
	
	_background1A = IMAGEMANAGER->findImage("lobby_l1_debris_background");
	_background1B = IMAGEMANAGER->findImage("lobby_l1_background");
	_background3 = IMAGEMANAGER->findImage("BackGround3");

	IMAGEMANAGER->addImage("lobby_l1_wall_patch", "img/stage/stage11/lobby_l1_wall_patch.bmp", 408, 729, true, RGB(255, 0, 255));

	// 플레이어 초기화
	_player = new player;
	_player->init();
	_tagPlayer = _player->getPlayerData();
	_tagPlayer->state = new idleState;
	_tagPlayer->state->enter(_player);

	// 문 세팅
	_door1 = RectMakeCenter(250, 860, 200, 260);
	_door1Alpha = 0;
	_door2 = RectMakeCenter(1390, 600, 400, 40);
	_door2Alpha = 0;

	// 카메라 세팅
	RENDERMANAGER->setCameraX(-(_tagPlayer->x - WINSIZEX / 2));
	return S_OK;
}

void stage_lobby::release()
{
}

void stage_lobby::update()
{
	_player->update();
	_tagPlayer = _player->getPlayerData();

	cameraWork();
	doorWork();
	pixelCollision(_tagPlayer, "lobby_l1_background_Pixel", _player);
}

void stage_lobby::render()
{
	if(KEYMANAGER->isToggleKey(VK_TAB))
	RENDERMANAGER->push_BackRenderInfo(-1000, "lobby_l1_debris_background", 0, 114, true);
	else 
	{
		RENDERMANAGER->push_BackRenderInfo(-999, "lobby_l1_wall_patch", 2361, 426, true);
		RENDERMANAGER->push_BackRenderInfo(-1000, "lobby_l1_background", 0, 114, true);
		RENDERMANAGER->push_BackRenderInfo(-999, "lobby_l1_background_Pixel", 0, 0, true);
	}

	////////////////////
	_player->render();

	
	
	RENDERMANAGER->push_BackRenderInfo(3000, "UI_UNLOCKED_DOOR", 250, 760, false, true, _door1Alpha);
	RENDERMANAGER->push_BackRenderInfo(3000, "UI_UNLOCKED_DOOR", 1390, 450, false, true, _door2Alpha);

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

void stage_lobby::cameraWork()
{
	if (_tagPlayer->x > WINSIZEX / 2)
	{
		RENDERMANAGER->setCameraX(-(_tagPlayer->x - WINSIZEX / 2));
	}
	if (RENDERMANAGER->getCameraX() < -_background1A->getWidth() + WINSIZEX)
	{
		RENDERMANAGER->setCameraX(-_background1A->getWidth() + WINSIZEX);
	}
	if (_tagPlayer->y - 200 - _tagPlayer->z < _background1A->getHeight() - WINSIZEY / 2 + 114)
	{
		RENDERMANAGER->setCameraY(-(_tagPlayer->y - WINSIZEY / 2 + 114 - 200 - _tagPlayer->z));
	}
	if (_tagPlayer->y - _tagPlayer->z < WINSIZEY / 2 - 114 + 200)
	{
		RENDERMANAGER->setCameraY(0);
	}
}

void stage_lobby::doorWork()
{
	if (IntersectRect(&_temp, &_tagPlayer->rc, &_door1))
	{
		if (_door1Alpha < 200)
			_door1Alpha += 5;
		if (KEYMANAGER->isOnceKeyDown('Y'))
		{
			RENDERMANAGER->setCameraX(0);
			RENDERMANAGER->setCameraY(0);
			SCENEMANAGER->changeScene("식당");
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
			SCENEMANAGER->changeScene("식당");
		}
	}
	else if (_door2Alpha > 0)
	{
		_door2Alpha -= 5;
	}
}
