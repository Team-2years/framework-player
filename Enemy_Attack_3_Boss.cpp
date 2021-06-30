#include "stdafx.h"
#include "Enemy_Basic.h"

#include "Enemy_Attack_3_Boss.h"
#include "Enemy_Idle_Boss.h"



Enemy_State * Enemy_Attack_3_Boss::input_state(Enemy_Basic * _Enemy, bool reverse, int targetX, int targetY)
{
	
	//if (_Enemy->getEnemyInfo()->CurrentframeX > _Enemy->getEnemyInfo()->_image->getMaxFrameX())
	//{
	//	_Enemy->setEnemyImageError(0);
	//	return new Enemy_Idle_Boss();
	//}

	return nullptr;
}

void Enemy_Attack_3_Boss::update(Enemy_Basic * _Enemy, int targetX, int targetY)
{
	if(_Enemy->getEnemyInfo()->isRight) _Enemy->setEnemyImageError(80);
	else _Enemy->setEnemyImageError(-80);

 	
	ImageUpdateFunc(_Enemy);
}

void Enemy_Attack_3_Boss::release(Enemy_Basic * _Enemy)
{
}

void Enemy_Attack_3_Boss::enter_this_state(Enemy_Basic * _Enemy)
{
	_Enemy->setEnemyTestText("IDLE");
	//_Enemy->set_Enemy_State_Enum();

	char str[128] = "Misuzu_Attack_2";

	_Enemy->setEnemyImage(IMAGEMANAGER->findImage(str));

	frameCount = 0;


	//frameUpdateCount =3;

	frameUpdateCount = _Enemy->getBOSS_AI_TRIGGER() == POWER_ATTACK_TRIGGER_BOSS ? 4 : 3;

	_Enemy->setEnemyFrameX(0);
	//_Enemy->setEnemyImageError(0);

	if (_Enemy->getEnemyInfo()->isRight) _Enemy->setEnemyFrameY(0);
	else _Enemy->setEnemyFrameY(1); 

	ChangeCount = 0;
}

void Enemy_Attack_3_Boss::call_Idle_function(Enemy_Basic * _Enemy)
{
}

void Enemy_Attack_3_Boss::ImageUpdateFunc(Enemy_Basic * _Enemy)
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

				_Enemy->setEnemyAiTrigger_Boss(OBSERVE_STATE_TRIGGER_BOSS);
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
				_Enemy->setEnemyAiTrigger_Boss(OBSERVE_STATE_TRIGGER_BOSS);
				_Enemy->set_Enemy_State(IDLE);
			}
		
		}
	}
}
