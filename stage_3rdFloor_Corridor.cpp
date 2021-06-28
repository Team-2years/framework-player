#include "stdafx.h"
#include "stage_3rdFloor_Corridor.h"

HRESULT stage_3rdFloor_Corridor::init()
{
	IMAGEMANAGER->addImage("3rdFloor_BackGround", "img/stage/stage2/3rdFloor.bmp", 4224, 864, true, RGB(255, 0, 255));
	_background1 = IMAGEMANAGER->findImage("3rdFloor_BackGround");

	_background3 = IMAGEMANAGER->findImage("BackGround3");


	// 플레이어 생성 및 초기화
	_player = new player;
	_player->init();
	_tagPlayer = _player->getPlayerData();
	_tagPlayer->state = new idleState;
	_tagPlayer->state->enter(_player);
	RENDERMANAGER->setCameraX(-(_tagPlayer->x - WINSIZEX / 2));
	return S_OK;
}

void stage_3rdFloor_Corridor::release()
{
}

void stage_3rdFloor_Corridor::update()
{
	if (KEYMANAGER->isOnceKeyDown('Y')) 
	{
		RENDERMANAGER->setCameraX(0);
		RENDERMANAGER->setCameraY(0);
		SCENEMANAGER->changeScene("테스트씬");
	}
	if (KEYMANAGER->isOnceKeyDown('U'))
	{
		_player->getPlayerData()->isHit = true;
	}

	_player->update();
	_tagPlayer = _player->getPlayerData();
	
	KEYANIMANAGER->update();
	// 카메라 처리
	if (_tagPlayer->x > WINSIZEX / 2)
	{
		RENDERMANAGER->setCameraX(-(_tagPlayer->x - WINSIZEX / 2));
	}
	if (RENDERMANAGER->getCameraX() < -_background1->getWidth() + WINSIZEX)
	{
		RENDERMANAGER->setCameraX(-_background1->getWidth() + WINSIZEX);
	}
	if (_tagPlayer->y - 200 -_tagPlayer->z < _background1->getHeight() - WINSIZEY/2 + 114 )
	{
		RENDERMANAGER->setCameraY(-(_tagPlayer->y - WINSIZEY / 2 + 57 - 200 - _tagPlayer->z));
	}
	
	if (_tagPlayer->y - _tagPlayer->z  < WINSIZEY / 2 - 57  + 200)
	{
		RENDERMANAGER->setCameraY(0);
	}
	
}

void stage_3rdFloor_Corridor::render()
{
	//레터박스의 크기는 위아래 각각 114;
	RENDERMANAGER->push_BackRenderInfo(-1000, "3rdFloor_BackGround", 0, 114, true);
	_player->render();

	RENDERMANAGER->render(getMemDC());
	_background3->render(getMemDC());

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), _tagPlayer->rc);
	}
}
