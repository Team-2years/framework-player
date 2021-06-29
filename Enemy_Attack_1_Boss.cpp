#include "stdafx.h"
#include "Enemy_Basic.h"

#include "Enemy_Attack_1_Boss.h"
#include "Enemy_Attack_2_Boss.h"

#include "Enemy_Idle_Boss.h"

Enemy_State * Enemy_Attack_1_Boss::input_state(Enemy_Basic * _Enemy, bool reverse, int targetX, int targetY)
{


	return nullptr;
}

void Enemy_Attack_1_Boss::update(Enemy_Basic * _Enemy, int targetX, int targetY)
{
	

	ImageUpdateFunc(_Enemy);
}

void Enemy_Attack_1_Boss::release(Enemy_Basic * _Enemy)
{
}

void Enemy_Attack_1_Boss::enter_this_state(Enemy_Basic * _Enemy)
{
	_Enemy->setEnemyTestText("ATTACK_1");
	//_Enemy->set_Enemy_State_Enum();

	char str[128] = "Misuzu_Attack_1";

	_Enemy->setEnemyImage(IMAGEMANAGER->findImage(str));

	frameCount = 0;
	frameUpdateCount = 3;

	_Enemy->setEnemyFrameX(0);
	_Enemy->setEnemyImageError(0);

	if (_Enemy->getEnemyInfo()->isRight) _Enemy->setEnemyFrameY(0);
	else _Enemy->setEnemyFrameY(1);


}



void Enemy_Attack_1_Boss::ImageUpdateFunc(Enemy_Basic * _Enemy)
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
				Enemy_State* Attack_2;
				Attack_2 = new Enemy_Attack_2_Boss();

				_Enemy->set_Enemy_State(Attack_2);
			}
		}
		else
		{
			_Enemy->setEnemyFrameY(1);
			_Enemy->setEnemyFrameX(_Enemy->getEnemyInfo()->CurrentframeX + 1);

			if (_Enemy->getEnemyInfo()->CurrentframeX > _Enemy->getEnemyInfo()->_image->getMaxFrameX())
			{
				Enemy_State* Attack_2;
				Attack_2 = new Enemy_Attack_2_Boss();

				_Enemy->set_Enemy_State(Attack_2);
			}
		}
	}
}
