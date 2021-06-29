#include "stdafx.h"
#include "playGround.h"

#include <iostream>
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
using namespace std;

playGround::playGround()
{
}


playGround::~playGround()
{
}

//초기화는 여기다 하세요 제발
HRESULT playGround::init()
{
	gameNode::init(true);
	// 레터박스
	IMAGEMANAGER->addImage("BackGround3", "img/stage/stage1/BackBg3.bmp", 2016, WINSIZEY, true, RGB(255, 0, 255));

	EFFECTMANAGER->addEffect("이펙트1", "img/enemy/school_girl/school_girl_Climb.bmp", 174, 71, 29, 71, 1, 0.1, 3, true);
	SCENEMANAGER->addScene("3층복도", new stage_3rdFloor_Corridor);
	SCENEMANAGER->addScene("테스트씬", new testScene);
	SCENEMANAGER->addScene("반성실", new stage_Detention);
	SCENEMANAGER->addScene("2층홀A", new stage_2ndFloor_HallA);
	SCENEMANAGER->addScene("2층방", new stage_2ndFloor_room);
	SCENEMANAGER->addScene("2층홀B", new stage_2ndFloor_HallB);
	SCENEMANAGER->addScene("1층홀A", new stage_1stFloor_HallA);
	SCENEMANAGER->addScene("1층홀B", new stage_1stFloor_HallB);
	SCENEMANAGER->addScene("1층방", new stage_1stFloor_room);
	SCENEMANAGER->addScene("식당", new stage_cafeteria);
	SCENEMANAGER->addScene("로비", new stage_lobby);
	SCENEMANAGER->changeScene("식당");

	IMAGEMANAGER->addImage("UI_UNLOCKED_DOOR", "img/ui/UI_UNLOCKED_DOOR.bmp", 78, 114, true, RGB(255, 0, 255), true);

	return S_OK;
}

//메모리 해제는 여기다 하세요 제발
void playGround::release()
{
	gameNode::release();


}


void playGround::update()
{
	gameNode::update();

	if (KEYMANAGER->isOnceKeyDown('R'))
	{
		init();
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		cout << _ptMouse.x - RENDERMANAGER->getCameraX() << ", " << _ptMouse.y - RENDERMANAGER->getCameraY() << endl;
	}
		SCENEMANAGER->update();
}


void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	// 위에 건들지마라
	//================제발 이 사이에 좀 그립시다==========================
	
	SCENEMANAGER->render();
	if (KEYMANAGER->isToggleKey(VK_F5))
	{
		SetTextColor(getMemDC(), RGB(0, 0, 0));
		TIMEMANAGER->render(getMemDC());
	}
	//==================================================
	//여기도 건들지마라
	this->getBackBuffer()->render(getHDC(), 0, 0);
}
