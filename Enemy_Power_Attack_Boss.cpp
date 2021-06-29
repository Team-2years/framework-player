#include "stdafx.h"
#include "Enemy_Basic.h"

#include "Enemy_Power_Attack_Boss.h"
#include "Enemy_Idle_Boss.h"

Enemy_State * Enemy_Power_Attack_Boss::input_state(Enemy_Basic * _Enemy, bool reverse, int targetX, int targetY)
{
	return nullptr;
}

void Enemy_Power_Attack_Boss::update(Enemy_Basic * _Enemy, int targetX, int targetY)
{
	if(_Enemy->getEnemyInfo()->isRight) _Enemy->setEnemyImageError(100);
	else _Enemy->setEnemyImageError(-100);

	ImageUpdateFunc(_Enemy);
}

void Enemy_Power_Attack_Boss::release(Enemy_Basic * _Enemy)
{
}

void Enemy_Power_Attack_Boss::enter_this_state(Enemy_Basic * _Enemy)
{
	_Enemy->setEnemyTestText("POWER_ATTACK");
	//_Enemy->set_Enemy_State_Enum();

	char str[128] = "Misuzu_PowerAttack";

	_Enemy->setEnemyImage(IMAGEMANAGER->findImage(str));

	frameCount = 0;
	frameUpdateCount = 5;

	_Enemy->setEnemyFrameX(0);

	if (_Enemy->getEnemyInfo()->isRight) _Enemy->setEnemyFrameY(0);
	else _Enemy->setEnemyFrameY(1);
}


void Enemy_Power_Attack_Boss::ImageUpdateFunc(Enemy_Basic * _Enemy)
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
