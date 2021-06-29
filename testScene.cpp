#include "stdafx.h"
#include "testScene.h"

HRESULT testScene::init()
{
	// 이미지 초기화 나중에 몇개는 로딩으로 옮기자
	IMAGEMANAGER->addImage("BackGround", "img/stage/stage1/Detention_PixelBG2.bmp", 2016, WINSIZEY, true, RGB(255, 0, 255));
	_background = IMAGEMANAGER->findImage("BackGround");
	IMAGEMANAGER->addImage("BackGround2", "img/stage/stage1/Detention_BG.bmp", 2016, 672, true, RGB(255, 0, 255));
	_background2 = IMAGEMANAGER->findImage("BackGround2");
	IMAGEMANAGER->addImage("BackGround3", "img/stage/stage1/BackBg3.bmp", 2016, WINSIZEY, true, RGB(255, 0, 255));
	_background3 = IMAGEMANAGER->findImage("BackGround3");
	IMAGEMANAGER->addImage("Desk1", "img/stage/stage1/Detention_OBJ_Desks_01.bmp", 189, 171, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Desk2", "img/stage/stage1/Detention_OBJ_Desks_02.bmp", 186, 171, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Desk3", "img/stage/stage1/Detention_OBJ_Desks_03.bmp", 186, 171, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Desk4", "img/stage/stage1/Detention_OBJ_Desks_04.bmp", 186, 171, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Desk5", "img/stage/stage1/Detention_OBJ_Desks_05.bmp", 189, 144, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Desk6", "img/stage/stage1/Detention_OBJ_Desks_06.bmp", 186, 144, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Desk7", "img/stage/stage1/Detention_OBJ_Desks_07.bmp", 186, 144, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Desk8", "img/stage/stage1/Detention_OBJ_Desks_08.bmp", 183, 144, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("TeacherDesk", "img/stage/stage1/Detention_OBJ_TeacherDesk.bmp", 261, 102, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("school_girl_Idle", "img/enemy/school_girl/school_girl_Idle.bmp", 1170, 354, 10, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("Chair1", "img/stage/stage1/Detention_Chair_2.bmp", 129, 120, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Chair2", "img/stage/stage1/Detention_Chair_3.bmp", 153, 132, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SB_sit_idle", "img/stage/stage1/SB_sit_idle.bmp", 732, 180, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SG_sit_idle", "img/stage/stage1/SG_sit_idle.bmp", 408, 216, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("MrRudis_idle", "img/stage/stage1/MrRudis_idle.bmp", 396, 237, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("UI_UNLOCKED_DOOR", "img/ui/UI_UNLOCKED_DOOR.bmp", 78, 114, true, RGB(255, 0, 255), true);
	_school_girl = IMAGEMANAGER->findImage("school_girl_Idle");
	doorAlpha = 0;

	// 오브젝트 애니메이션
	int boy_sleep[] = { 0, 1, 2, 3 };
	KEYANIMANAGER->addArrayFrameAnimation("SIT_BOY_SLEEP", "SB_sit_idle", boy_sleep, 4, 1, true);
	int girl_sit[] = { 0, 1 };
	KEYANIMANAGER->addArrayFrameAnimation("SIT_GIRL_SIT", "SG_sit_idle", girl_sit, 2, 2, true);
	_sit_boy_ani = KEYANIMANAGER->findAnimation("SIT_BOY_SLEEP");
	KEYANIMANAGER->findAnimation("SIT_GIRL_SIT")->start();
	KEYANIMANAGER->addArrayFrameAnimation("MRRUDIS_IDLE_LEFT", "MrRudis_idle", girl_sit, 2, 14, true);
	int _MrRudis_Right[] = { 2, 3 };
	KEYANIMANAGER->addArrayFrameAnimation("MRRUDIS_IDLE_RIGHT", "MrRudis_idle", _MrRudis_Right, 2, 14, true);
	_MrRudis_idle_ani = KEYANIMANAGER->findAnimation("MRRUDIS_IDLE_RIGHT");

	// 애니메이션을 만들었으면 실행을 해야쥬?
	_MrRudis_idle_ani->start();
	_sit_boy_ani->start();

	// 스쿨걸 렉트생성
	_rc = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, _school_girl->getFrameWidth(), _school_girl->getFrameHeight());
	
	// door 렉트 생성
	_door = RectMakeCenter(1438, 500, 300, 20);
	// 플레이어 생성 및 초기화
	_player = new player;
	_player->init();
	_tagPlayer = _player->getPlayerData();
	_tagPlayer->state = new idleState;
	_tagPlayer->state->enter(_player);
	RENDERMANAGER->setCameraY(0);



	//==================================================
	//에너미
	//==================================================
	addEnemyImage_school_girl();
	addEnemyImage_school_boy();

	_em = new enemyManager;
	_em->init();
	_em->setAddressLinkPlayer(_player);



	return S_OK;
}

void testScene::release()
{
	
}

void testScene::update()
{

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) 
	{
		cout << _ptMouse.x << ", " << _ptMouse.y << endl;
		//EFFECTMANAGER->play("이펙트1", _ptMouse.x, _ptMouse.y, true, 150);
	}

	_player->update();

	// 스쿨걸 프레임 돌리기
	if (_count % 5 == 0) 
	{
		if (_school_girl->getFrameX() >= _school_girl->getMaxFrameX()) _school_girl->setFrameX(0);
		_school_girl->setFrameX(_school_girl->getFrameX() + 1);
		
	}
	_count++;

	// 플레이어 데이터를 가져옴
	_tagPlayer = _player->getPlayerData();
	
	// 픽셀 충돌
	//pixelCollision();

	// 카메라 처리
	if (_tagPlayer->x > WINSIZEX / 2 )
	{
		RENDERMANAGER->setCameraX(-(_tagPlayer->x - WINSIZEX / 2));
	}
	
	if (RENDERMANAGER->getCameraX() < -_background2->getWidth() + WINSIZEX)
	{
		RENDERMANAGER->setCameraX(-_background2->getWidth() + WINSIZEX);
	}
	// 테스트 학생 rc
	_rc = RectMake(WINSIZEX / 2, WINSIZEY / 2 + 90, _school_girl->getFrameWidth(), _school_girl->getFrameHeight() - 70);
	EFFECTMANAGER->update();

	// 문 UI blend 값 조정
	
	if (IntersectRect(&_temp, &_tagPlayer->rc, &_door)) 
	{
		if (doorAlpha < 200)
		doorAlpha += 5;
		if (KEYMANAGER->isOnceKeyDown('Y')) 
		{
			RENDERMANAGER->setCameraX(0);
			RENDERMANAGER->setCameraY(0);
			SCENEMANAGER->changeScene("반성실");
		}
	}
	else if (doorAlpha > 0) 
	{
		doorAlpha -= 5;
	}

	// 이거 주석시 애니메이션이 실행이 안되는 것을 우리는 확인할 수 있을 겁니다 ^^
	KEYANIMANAGER->update();

	//==================================================
	//에너미
	//==================================================

	_em->update();
}

// 그리기는 여기에
void testScene::render()
{

	RENDERMANAGER->push_BackFrameRenderInfo(_rc.bottom, "school_girl_Idle", WINSIZEX / 2, WINSIZEY / 2,
		_school_girl->getFrameX(),
		_school_girl->getFrameY(),true);
	

	RENDERMANAGER->push_BackRenderInfo(-1000, "Chair2", 1570, 520, true);
	RENDERMANAGER->push_BackRenderInfo(-1000, "Chair1", 1760, 650, true);
	RENDERMANAGER->push_BackRenderInfo(-1000, "BackGround2", 0, (WINSIZEY - _background2->getHeight()) / 2, true);


	RENDERMANAGER->push_BackAniRenderInfo(450 + 237, "MrRudis_idle", _MrRudis_idle_ani, 1650, 450, true);


	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		RENDERMANAGER->push_BackRenderInfo(-999, "BackGround", 0, 0,true);
		_background->render(getMemDC(), 0, 0);
	}
	
	if (_tagPlayer->x < 1098 || _tagPlayer->y < 400) 
	{
		RENDERMANAGER->push_BackAniRenderInfo(442 + 228, "SG_sit_idle", KEYANIMANAGER->findAnimation("SIT_GIRL_SIT"), 1080, 442, true);
		RENDERMANAGER->push_BackRenderInfo(442 + 228, "Desk4", 1098, 487, true);
	}
	else 
	{
		RENDERMANAGER->push_BackAniRenderInfo(442, "SG_sit_idle", KEYANIMANAGER->findAnimation("SIT_GIRL_SIT"), 1080, 442, true);
		RENDERMANAGER->push_BackRenderInfo(442, "Desk4", 1098, 487, true);
	}

	if (_tagPlayer->x < 838 || _tagPlayer->y < 400)
	RENDERMANAGER->push_BackRenderInfo(442 + 228, "Desk3", 838, 487, true);
	else
	RENDERMANAGER->push_BackRenderInfo(442, "Desk3", 838, 487, true);

	if (_tagPlayer->x < 572 || _tagPlayer->y < 400)
	RENDERMANAGER->push_BackRenderInfo(442 + 228, "Desk2", 572, 487, true);
	else
	RENDERMANAGER->push_BackRenderInfo(442, "Desk2", 572, 487, true);

	if (_tagPlayer->x < 328 || _tagPlayer->y < 400)
	RENDERMANAGER->push_BackRenderInfo(442 + 228, "Desk1", 328, 487, true);
	else
	RENDERMANAGER->push_BackRenderInfo(442, "Desk1", 328, 487, true);


	_player->render();	
	RENDERMANAGER->push_BackAniRenderInfo(3000, "SB_sit_idle", _sit_boy_ani, 425, 632, true);
	RENDERMANAGER->push_BackRenderInfo(3000, "Desk5", 175, 642, true);
	RENDERMANAGER->push_BackRenderInfo(3000, "Desk6", 425, 638, true);
	RENDERMANAGER->push_BackRenderInfo(3000, "Desk7", 685, 642, true);
	RENDERMANAGER->push_BackRenderInfo(3000, "Desk8", 940, 642, true);
	RENDERMANAGER->push_BackRenderInfo(3000, "TeacherDesk", 1400, 684, true);
	EFFECTMANAGER->render();
	RENDERMANAGER->push_BackRenderInfo(3000, "UI_UNLOCKED_DOOR", 1400, 300, true, true, doorAlpha);



//	EllipseMakeCenter(getMemDC(), _player.x, _player.y, 90, 45);

	//==================================================
	//에너미
	//==================================================

	

	RENDERMANAGER->render(getMemDC());
	_background3->render(getMemDC());
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), _tagPlayer->rc);
	}

	_em->render();

	Rectangle(getMemDC(), _tagPlayer->rc);
}

void testScene::pixelCollision()
{

	for (int i = _tagPlayer->rc.left; i <= _tagPlayer->rc.left + 20; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("BackGround")->getMemDC(), i, (_tagPlayer->rc.top + _tagPlayer->rc.bottom) / 2);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
		if (r == 0  && g == 255 && b == 0)
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

void testScene::addEnemyImage_school_girl()
{

	//IDLE 이미지
	IMAGEMANAGER->addFrameImage("Enemy_Image_Idle_School_Girl", "img/enemy/school_girl/school_girl_Idle.bmp", 1170, 354, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Enemy_Image_Move_School_Girl", "img/enemy/school_girl/school_girl_Walk.bmp", 1296, 372, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Enemy_Image_Run_School_Girl", "img/enemy/school_girl/school_girl_Run.bmp", 1530, 336, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Enemy_Image_Jump_School_Girl", "img/enemy/school_girl/school_girl_Jump.bmp", 351, 372, 3, 2, true, RGB(255, 0, 255));
	


	
	//공격 이미지
	IMAGEMANAGER->addFrameImage("Enemy_Image_Attack_1_School_Girl", "img/enemy/school_girl/school_girl_Attack_1.bmp", 825, 354, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Enemy_Image_Attack_2_School_Girl", "img/enemy/school_girl/school_girl_Attack_2.bmp", 1260, 354, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Enemy_Image_Attack_3_School_Girl", "img/enemy/school_girl/school_girl_Attack_3.bmp", 1632, 354, 8, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("Enemy_Image_Dash_Attack_School_Girl", "img/enemy/school_girl/school_girl_Dash_Attack.bmp", 3312, 414, 12, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("Enemy_Image_Jump_Attack_School_Girl", "img/enemy/school_girl/school_girl_Jump_Attack.bmp", 1239, 354, 7, 2, true, RGB(255, 0, 255));


	//피격 이미지
	IMAGEMANAGER->addFrameImage("Enemy_Image_Attacked_1_School_Girl", "img/enemy/school_girl/school_girl_getHit_1.bmp", 477, 360, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Enemy_Image_Attacked_2_School_Girl", "img/enemy/school_girl/school_girl_getHit_2.bmp", 477, 360, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Enemy_Image_Attacked_3_School_Girl", "img/enemy/school_girl/school_girl_getHit_3.bmp", 477, 360, 3, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("Enemy_Image_Ground_Hitted_School_Girl", "img/enemy/school_girl/school_girl_Ground_Hitted.bmp", 675, 360, 3, 2, true, RGB(255, 0, 255));

	//넉다운 이미지
	IMAGEMANAGER->addFrameImage("Enemy_Image_KnockDown_1_School_Girl", "img/enemy/school_girl/school_girl_KnockDown_1.bmp", 675, 360, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Enemy_Image_KnockDown_2_School_Girl", "img/enemy/school_girl/school_girl_KnockDown_2.bmp", 450, 360, 3, 2, true, RGB(255, 0, 255));
	//기상 이미지 
	IMAGEMANAGER->addFrameImage("Enemy_Image_Wake_up_School_Girl", "img/enemy/school_girl/school_girl_Wake_up.bmp", 2025, 360, 9, 2, true, RGB(255, 0, 255));
}

void testScene::addEnemyImage_school_boy()
{
	IMAGEMANAGER->addFrameImage("Enemy_Image_Wake_up_School_Boy", "img/enemy/school_boy/schoo_boy_wake_up.bmp",2160,420,8,2,true,RGB(255,0,255));


	IMAGEMANAGER->addFrameImage("Enemy_Image_Idle_School_Boy", "img/enemy/school_boy/school_boy_idle.bmp", 1224, 432, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Enemy_Image_Jump_School_Boy", "img/enemy/school_boy/school_boy_jump.bmp", 423, 486, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Enemy_Image_Move_School_Boy", "img/enemy/school_boy/school_boy_walk.bmp", 1620, 444, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Enemy_Image_Run_School_Boy", "img/enemy/school_boy/school_boy_run.bmp", 1920, 390, 10, 2, true, RGB(255, 0, 255));


	IMAGEMANAGER->addFrameImage("Enemy_Image_Attack_1_School_Boy", "img/enemy/school_boy/school_boy_attack_1.bmp", 1764, 426, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Enemy_Image_Attack_2_School_Boy", "img/enemy/school_boy/school_boy_attack_2.bmp", 1386, 510, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Enemy_Image_Attack_3_School_Boy", "img/enemy/school_boy/school_boy_attack_3.bmp", 1863, 558, 9, 2, true, RGB(255, 0, 255)); 
	IMAGEMANAGER->addFrameImage("Enemy_Image_Dash_Attack_School_Boy", "img/enemy/school_boy/school_boy_dash_attack.bmp", 1764, 444, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Enemy_Image_Jump_Attack_School_Boy", "img/enemy/school_boy/school_boy_jump_attack.bmp", 1188, 456, 6, 2, true, RGB(255, 0, 255));


	IMAGEMANAGER->addFrameImage("Enemy_Image_Attacked_1_School_Boy", "img/enemy/school_boy/school_boy_attacked_1.bmp",576,450,3,2,true,RGB(255,0,255));
	IMAGEMANAGER->addFrameImage("Enemy_Image_Attacked_2_School_Boy", "img/enemy/school_boy/school_boy_attacked_2.bmp",576,450,3,2,true,RGB(255,0,255));
	IMAGEMANAGER->addFrameImage("Enemy_Image_Attacked_3_School_Boy", "img/enemy/school_boy/school_boy_attacked_3.bmp",576,450,3,2,true,RGB(255,0,255));



	IMAGEMANAGER->addFrameImage("Enemy_Image_KnockDown_1_School_Boy", "img/enemy/school_boy/school_boy_knockdown_1.bmp", 6210, 420, 23, 2, true, RGB(255, 0, 255));//23
	IMAGEMANAGER->addFrameImage("Enemy_Image_KnockDown_2_School_Boy", "img/enemy/school_boy/school_boy_knockdown_3.bmp",540,420,2,2,true,RGB(255,0,255));




}
