#include "stdafx.h"
#include "stage_3rdFloor_Corridor.h"

HRESULT stage_3rdFloor_Corridor::init()
{
	IMAGEMANAGER->addImage("3rdFloor_BackGround", "img/stage/stage2/3rdFloor.bmp", 4224, 864, true, RGB(255, 0, 255));
	_background1 = IMAGEMANAGER->findImage("3rdFloor_BackGround");
	IMAGEMANAGER->addImage("3rdFloorPixel", "img/stage/stage2/3rdFloorPixel.bmp", 4224, 1112, true, RGB(255, 0, 255));
	_background2 = IMAGEMANAGER->findImage("3rdFloorPixel");
	IMAGEMANAGER->addImage("L3_lockers1", "img/stage/stage2/L3_lockers1.bmp", 558, 291, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("L3_lockers2", "img/stage/stage2/L3_lockers2.bmp", 555, 273, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("L3_pillar1", "img/stage/stage2/L3_pillar1.bmp", 207, 864, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("L3_pillar2", "img/stage/stage2/L3_pillar2.bmp", 198, 543, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("L3_pillar3", "img/stage/stage2/L3_pillar3.bmp", 198, 543, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("L3_pillar4", "img/stage/stage2/L3_pillar4.bmp", 207, 864, true, RGB(255, 0, 255), true);
	_background3 = IMAGEMANAGER->findImage("BackGround3");


	// 플레이어 생성 및 초기화
	_player = new player;
	_player->init();
	_tagPlayer = _player->getPlayerData();
	_tagPlayer->state = new idleState;
	_tagPlayer->state->enter(_player);

	// 문렉트 초기화
	
	_door = RectMakeCenter(1400, 600, 260, 40);
	doorAlpha = 0;
	RENDERMANAGER->setCameraX(-(_tagPlayer->x - WINSIZEX / 2));
	return S_OK;
}

void stage_3rdFloor_Corridor::release()
{
}

void stage_3rdFloor_Corridor::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_F7)) 
	{
		RENDERMANAGER->setCameraX(0);
		RENDERMANAGER->setCameraY(0);
		SCENEMANAGER->changeScene("테스트씬");
	}
	_player->update();
	_tagPlayer = _player->getPlayerData();
	
	KEYANIMANAGER->update();
	// 카메라 처리
	cameraWork();
	doorWork();
}

void stage_3rdFloor_Corridor::render()
{
	//레터박스의 크기는 위아래 각각 114;
	RENDERMANAGER->push_BackRenderInfo(-1000, "3rdFloor_BackGround", 0, 114, true);
	_player->render();
	// 픽셀
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		//RENDERMANAGER->push_BackRenderInfo(-999, "3rdFloorPixel", 0, 0, true);
		_background2->render(getMemDC(), 0, 0);
	}
	// 락커
	RENDERMANAGER->push_BackRenderInfo(380, "L3_lockers1", 3345, 380, true);
	RENDERMANAGER->push_BackRenderInfo(390 + 273, "L3_lockers2", 1920, 390, true);
	// 기둥
	RENDERMANAGER->push_BackRenderInfo(3000, "L3_pillar1", 492, 114, true, true, 155);
	RENDERMANAGER->push_BackRenderInfo(3000, "L3_pillar4", 3141, 114, true, true, 155);
	// 문 ui
	RENDERMANAGER->push_BackRenderInfo(3000, "UI_UNLOCKED_DOOR", 1400, 450, false, true, doorAlpha);

	// 렌더 매니저
	RENDERMANAGER->render(getMemDC());
	// 레터 박스
	_background3->render(getMemDC());
	

	// 캐릭터 렉트
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		RECT rc = RectMake(_tagPlayer->rc.left + RENDERMANAGER->getCameraX(), _tagPlayer->rc.top + RENDERMANAGER->getCameraY(), _tagPlayer->rc.right - _tagPlayer->rc.left, _tagPlayer->rc.bottom - _tagPlayer->rc.top);
		Rectangle(getMemDC(), rc);
		rc = RectMakeCenter(1400 + RENDERMANAGER->getCameraX(), 600 + RENDERMANAGER->getCameraY(), 260, 40);
		Rectangle(getMemDC(), rc);
	}
}

void stage_3rdFloor_Corridor::cameraWork()
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
		RENDERMANAGER->setCameraY(-(_tagPlayer->y - WINSIZEY / 2 + 57 - 200 - _tagPlayer->z));
	}

	if (_tagPlayer->y - _tagPlayer->z < WINSIZEY / 2 - 57 + 200)
	{
		RENDERMANAGER->setCameraY(0);
	}
}

void stage_3rdFloor_Corridor::doorWork()
{
	if (IntersectRect(&_temp, &_tagPlayer->rc, &_door))
	{
		if (doorAlpha < 200)
			doorAlpha += 5;
		if (KEYMANAGER->isOnceKeyDown('Y'))
		{
			RENDERMANAGER->setCameraX(0);
			RENDERMANAGER->setCameraY(0);
			SCENEMANAGER->changeScene("2층홀A");
		}
	}
	else if (doorAlpha > 0)
	{
		doorAlpha -= 5;
	}
}
