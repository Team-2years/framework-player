#include "stdafx.h"

#include "Enemy_Basic.h"

#include "Enemy_Damaged_1.h"
#include "Enemy_Damaged_2.h"
#include "Enemy_Idle.h"


Enemy_State * Enemy_Damaged_1::input_state(Enemy_Basic * _Enemy, bool reverse, int targetX, int targetY)
{



	return nullptr;
}

void Enemy_Damaged_1::update(Enemy_Basic * _Enemy, int targetX, int targetY)
{
	/*
	나중에 이미지 마지막 프레임일때 회복하도록 바꿀 예정.
	*/

	//recoverCount++;
	//if (recoverCount > 100)
	//{
	//	recoverCount = 0;
	//	Enemy_State* _change_Idle;
	//	_change_Idle = new Enemy_Idle;
	//	_Enemy->set_Enemy_State(_change_Idle);
	//}

	frameCount++;

	if (frameCount % frameUpdateCount == 0)
	{
		if (_Enemy->getEnemyInfo()->isRight)
		{
			_Enemy->setEnemyFrameY(0);
			_Enemy->setEnemyFrameX(_Enemy->getEnemyInfo()->CurrentframeX + 1);

			if (_Enemy->getEnemyInfo()->CurrentframeX > _Enemy->getEnemyInfo()->_image->getMaxFrameX()) call_Idle_function(_Enemy);
			
				
		}
		else
		{
			_Enemy->setEnemyFrameY(0);
			_Enemy->setEnemyFrameX(_Enemy->getEnemyInfo()->CurrentframeX + 1);

			if (_Enemy->getEnemyInfo()->CurrentframeX > _Enemy->getEnemyInfo()->_image->getMaxFrameX()) call_Idle_function(_Enemy);


		}
	}
	
}

void Enemy_Damaged_1::release(Enemy_Basic * _Enemy)
{
}

void Enemy_Damaged_1::render()
{
}

void Enemy_Damaged_1::enter_this_state(Enemy_Basic * _Enemy)
{
	_Enemy->setEnemyTestText("DAMAGED_1");
	_Enemy->set_Enemy_State_Enum(DAMAGED_1);

	recoverCount = 0;


	char str[128] = "Enemy_Image_Attacked_1";

	strcat_s(str, _Enemy->getEnemyInfo()->imageName);

	string Idle_Image = str;

	_Enemy->setEnemyImage(IMAGEMANAGER->findImage(Idle_Image));

	frameCount = 0;
	frameUpdateCount = 5;
	
	_Enemy->setEnemyFrameX(0);
}

void Enemy_Damaged_1::call_Idle_function(Enemy_Basic * _Enemy)
{
	Enemy_State* Idle_ST;

	Idle_ST = new Enemy_Idle();

	_Enemy->set_Enemy_State(Idle_ST);
}
