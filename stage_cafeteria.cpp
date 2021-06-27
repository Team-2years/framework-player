#include "stdafx.h"
#include "stage_cafeteria.h"

HRESULT stage_cafeteria::init()
{
	// 배경
	IMAGEMANAGER->addImage("cafeteria_background", "img/stage/stage10/cafeteria_background.bmp", 2862, 837, true, RGB(255, 0, 255));
	_background1 = IMAGEMANAGER->findImage("cafeteria_background");

	_background3 = IMAGEMANAGER->findImage("BackGround3");

	IMAGEMANAGER->addImage("cafeteria_snackmachine", "img/stage/stage10/cafeteria_snackmachine.bmp", 255, 255, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("cafeteria_table1", "img/stage/stage10/cafeteria_table1.bmp", 339, 156, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("cafeteria_table2", "img/stage/stage10/cafeteria_table2.bmp", 366, 150, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("cafeteria_table3", "img/stage/stage10/cafeteria_table3.bmp", 339, 165, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("cafeteria_table4", "img/stage/stage10/cafeteria_table4.bmp", 366, 171, true, RGB(255, 0, 255));


	// 플레이어 초기화
	_player = new player;
	_player->init();
	_tagPlayer = _player->getPlayerData();
	_tagPlayer->state = new idleState;
	_tagPlayer->state->enter(_player);

	// 문 세팅
	_door1 = RectMakeCenter(100, 770, 200, 260);
	_door1Alpha = 0;
	_door2 = RectMakeCenter(1880, 770, 200, 260);
	_door2Alpha = 0;

	// 카메라 세팅
	RENDERMANAGER->setCameraX(-(_tagPlayer->x - WINSIZEX / 2));

	return S_OK;
}

void stage_cafeteria::release()
{
}

void stage_cafeteria::update()
{
	_player->update();
	_tagPlayer = _player->getPlayerData();

	cameraWork();
	doorWork();
}

void stage_cafeteria::render()
{
	RENDERMANAGER->push_BackRenderInfo(-1000, "cafeteria_background", 0, 114, true);
	////////////////////
	_player->render();

	RENDERMANAGER->push_BackRenderInfo(100, "cafeteria_snackmachine", 2306, 357, true);
	RENDERMANAGER->push_BackRenderInfo(722 + 156, "cafeteria_table1", 330, 722, true);
	RENDERMANAGER->push_BackRenderInfo(880, "cafeteria_table2", 870, 805, true);
	RENDERMANAGER->push_BackRenderInfo(874, "cafeteria_table3", 1480, 790, true);
	RENDERMANAGER->push_BackRenderInfo(800, "cafeteria_table4", 2067, 715, true);




	// 이 위에 렌더 이미지 인포
	RENDERMANAGER->render(getMemDC());
	RENDERMANAGER->push_BackRenderInfo(3000, "UI_UNLOCKED_DOOR", 110, 580, false, true, _door1Alpha);
	RENDERMANAGER->push_BackRenderInfo(3000, "UI_UNLOCKED_DOOR", 1900, 580, false, true, _door2Alpha);
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

void stage_cafeteria::cameraWork()
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

void stage_cafeteria::doorWork()

{
	if (IntersectRect(&_temp, &_tagPlayer->rc, &_door1))
	{
		if (_door1Alpha < 200)
			_door1Alpha += 5;
		if (KEYMANAGER->isOnceKeyDown('Y'))
		{
			RENDERMANAGER->setCameraX(0);
			RENDERMANAGER->setCameraY(0);
			SCENEMANAGER->changeScene("1층홀B");
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