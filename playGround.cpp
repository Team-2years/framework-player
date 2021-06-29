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

//�ʱ�ȭ�� ����� �ϼ��� ����
HRESULT playGround::init()
{
	gameNode::init(true);
	// ���͹ڽ�
	IMAGEMANAGER->addImage("BackGround3", "img/stage/stage1/BackBg3.bmp", 2016, WINSIZEY, true, RGB(255, 0, 255));

	EFFECTMANAGER->addEffect("����Ʈ1", "img/enemy/school_girl/school_girl_Climb.bmp", 174, 71, 29, 71, 1, 0.1, 3, true);
	SCENEMANAGER->addScene("3������", new stage_3rdFloor_Corridor);
	SCENEMANAGER->addScene("�׽�Ʈ��", new testScene);
	SCENEMANAGER->addScene("�ݼ���", new stage_Detention);
	SCENEMANAGER->addScene("2��ȦA", new stage_2ndFloor_HallA);
	SCENEMANAGER->addScene("2����", new stage_2ndFloor_room);
	SCENEMANAGER->addScene("2��ȦB", new stage_2ndFloor_HallB);
	SCENEMANAGER->addScene("1��ȦA", new stage_1stFloor_HallA);
	SCENEMANAGER->addScene("1��ȦB", new stage_1stFloor_HallB);
	SCENEMANAGER->addScene("1����", new stage_1stFloor_room);
	SCENEMANAGER->addScene("�Ĵ�", new stage_cafeteria);
	SCENEMANAGER->addScene("�κ�", new stage_lobby);
	SCENEMANAGER->changeScene("�Ĵ�");

	IMAGEMANAGER->addImage("UI_UNLOCKED_DOOR", "img/ui/UI_UNLOCKED_DOOR.bmp", 78, 114, true, RGB(255, 0, 255), true);

	return S_OK;
}

//�޸� ������ ����� �ϼ��� ����
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
	// ���� �ǵ�������
	//================���� �� ���̿� �� �׸��ô�==========================
	
	SCENEMANAGER->render();
	if (KEYMANAGER->isToggleKey(VK_F5))
	{
		SetTextColor(getMemDC(), RGB(0, 0, 0));
		TIMEMANAGER->render(getMemDC());
	}
	//==================================================
	//���⵵ �ǵ�������
	this->getBackBuffer()->render(getHDC(), 0, 0);
}
