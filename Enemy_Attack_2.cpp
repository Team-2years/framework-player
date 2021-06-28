#include "stdafx.h"
#include "Enemy_Attack_2.h"

#include "Enemy_Basic.h"
#include "Enemy_Idle.h"
#include "Enemy_Attack_3.h"


Enemy_State * Enemy_Attack_2::input_state(Enemy_Basic * _Enemy, bool reverse, int targetX, int targetY)
{
	return nullptr;
}

void Enemy_Attack_2::update(Enemy_Basic * _Enemy, int targetX, int targetY)
{
	
	ImageUpdateFunc(_Enemy);
}

void Enemy_Attack_2::release(Enemy_Basic * _Enemy)
{
}

void Enemy_Attack_2::render()
{
}

void Enemy_Attack_2::enter_this_state(Enemy_Basic * _Enemy)
{
	_Enemy->setEnemyTestText("ATTACK_2");
	_Enemy->set_Enemy_State_Enum(ATTACK_1);



	char str[128] = "Enemy_Image_Attack_2_";

	strcat_s(str, _Enemy->getEnemyInfo()->imageName);


	_Enemy->setEnemyImageKey(str);


	string Idle_Image = str;

	_Enemy->setEnemyImage(IMAGEMANAGER->findImage(Idle_Image));

	frameCount = 0;
	frameUpdateCount = 5;
	
	_Enemy->setEnemyFrameX(0);

	if (_Enemy->getEnemyInfo()->isRight) _Enemy->setEnemyFrameY(0);
	else _Enemy->setEnemyFrameY(1);
}

void Enemy_Attack_2::call_Attack_3_function(Enemy_Basic * _Enemy)
{
	Enemy_State* Attack_3;

	Attack_3 = new Enemy_Attack_3();

	_Enemy->set_Enemy_State(Attack_3);
}

void Enemy_Attack_2::ImageUpdateFunc(Enemy_Basic * _Enemy)
{
	frameCount++;

	if (frameCount % frameUpdateCount == 0)
	{
		if (_Enemy->getEnemyInfo()->isRight)
		{
			_Enemy->setEnemyFrameY(0);
			_Enemy->setEnemyFrameX(_Enemy->getEnemyInfo()->CurrentframeX + 1);

			if (_Enemy->getEnemyInfo()->CurrentframeX > _Enemy->getEnemyInfo()->_image->getMaxFrameX())
			{
				call_Attack_3_function(_Enemy);
			}
		}
		else
		{
			_Enemy->setEnemyFrameY(1);
			_Enemy->setEnemyFrameX(_Enemy->getEnemyInfo()->CurrentframeX + 1);

			if (_Enemy->getEnemyInfo()->CurrentframeX > _Enemy->getEnemyInfo()->_image->getMaxFrameX())
			{
				call_Attack_3_function(_Enemy);
			}
		}
	}
}
