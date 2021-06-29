#include "stdafx.h"
#include "Enemy_Basic.h"

#include "Enemy_Jump_Attack_stun_Boss.h"
#include "Enemy_Idle_Boss.h"

Enemy_State * Enemy_Jump_Attack_stun_Boss::input_state(Enemy_Basic * _Enemy, bool reverse, int targetX, int targetY)
{
	return nullptr;
}

void Enemy_Jump_Attack_stun_Boss::update(Enemy_Basic * _Enemy, int targetX, int targetY)
{
	ImageUpdateFunc(_Enemy);
}

void Enemy_Jump_Attack_stun_Boss::release(Enemy_Basic * _Enemy)
{
}

void Enemy_Jump_Attack_stun_Boss::enter_this_state(Enemy_Basic * _Enemy)
{
	_Enemy->setEnemyTestText("JUMP_BOSS");
	//_Enemy->set_Enemy_State_Enum();

	char str[128] = "Misuzu_Jump_after_groggy";

	_Enemy->setEnemyImage(IMAGEMANAGER->findImage(str));

	frameCount = 0;
	frameUpdateCount = 4;

	_Enemy->setEnemyFrameX(0);

	if (_Enemy->getEnemyInfo()->isRight) _Enemy->setEnemyFrameY(0);
	else _Enemy->setEnemyFrameY(1);
}



void Enemy_Jump_Attack_stun_Boss::ImageUpdateFunc(Enemy_Basic * _Enemy)
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
				Enemy_State* IDLE;
				IDLE = new Enemy_Idle_Boss();

				_Enemy->set_Enemy_State(IDLE);
			}
		}
		else
		{
			_Enemy->setEnemyFrameY(1);
			_Enemy->setEnemyFrameX(_Enemy->getEnemyInfo()->CurrentframeX + 1);

			if (_Enemy->getEnemyInfo()->CurrentframeX > _Enemy->getEnemyInfo()->_image->getMaxFrameX())
			{
				Enemy_State* IDLE;
				IDLE = new Enemy_Idle_Boss();

				_Enemy->set_Enemy_State(IDLE);
			}
		}
	}
}
