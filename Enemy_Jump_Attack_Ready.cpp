#include "stdafx.h"
#include "Enemy_Basic.h"


#include "Enemy_Jump_Attack_Ready.h"
#include "Enemy_Jump_Attack_Boss.h"

Enemy_State * Enemy_Jump_Attack_Ready::input_state(Enemy_Basic * _Enemy, bool reverse, int targetX, int targetY)
{
	return nullptr;
}

void Enemy_Jump_Attack_Ready::update(Enemy_Basic * _Enemy, int targetX, int targetY)
{
	ImageUpdateFunc(_Enemy);
}

void Enemy_Jump_Attack_Ready::release(Enemy_Basic * _Enemy)
{
}

void Enemy_Jump_Attack_Ready::enter_this_state(Enemy_Basic * _Enemy)
{
	_Enemy->setEnemyTestText("JUMP_BOSS");
	//_Enemy->set_Enemy_State_Enum();

	char str[128] = "Misuzu_Jump_Up_Ready";

	_Enemy->setEnemyImage(IMAGEMANAGER->findImage(str));

	frameCount = 0;
	frameUpdateCount = 5;

	_Enemy->setEnemyFrameX(0);

	if (_Enemy->getEnemyInfo()->isRight) _Enemy->setEnemyFrameY(0);
	else _Enemy->setEnemyFrameY(1);
}

void Enemy_Jump_Attack_Ready::ImageUpdateFunc(Enemy_Basic * _Enemy)
{
	frameCount++;

	if (frameCount % frameUpdateCount == 0)
	{
		if (_Enemy->getEnemyInfo()->isRight)
		{
			_Enemy->setEnemyFrameY(0);
			_Enemy->setEnemyFrameX(_Enemy->getEnemyInfo()->CurrentframeX + 1);

			if (_Enemy->getEnemyInfo()->CurrentframeX > _Enemy->getEnemyInfo()->_image->getMaxFrameX()-2)
			{
				Enemy_State* JumpAttack;
				JumpAttack = new Enemy_Jump_Attack_Boss();

				_Enemy->set_Enemy_State(JumpAttack);
			}
		}
		else
		{
			_Enemy->setEnemyFrameY(1);
			_Enemy->setEnemyFrameX(_Enemy->getEnemyInfo()->CurrentframeX + 1);

			if (_Enemy->getEnemyInfo()->CurrentframeX > _Enemy->getEnemyInfo()->_image->getMaxFrameX()-2)
			{
				Enemy_State* JumpAttack;
				JumpAttack = new Enemy_Jump_Attack_Boss();

				_Enemy->set_Enemy_State(JumpAttack);
			}
		}
	}
}
