#include "stdafx.h"

#include "Enemy_Basic.h"

#include "Enemy_Move_Boss.h"
#include "Enemy_Attack_1_Boss.h"
#include "Enemy_Attack_3_Boss.h"

#include "Enemy_Power_Attack_Boss.h"

Enemy_State * Enemy_Move_Boss::input_state(Enemy_Basic * _Enemy, bool reverse, int targetX, int targetY)
{
	if (getDistance(_Enemy->getEnemyInfo()->x, _Enemy->getEnemyInfo()->y,
		targetX, targetY) < 200)
	{
		switch (_Enemy->getBOSS_AI_TRIGGER())
		{
		case NORMAL_ATTACK_TRIGGER_BOSS:
			return new Enemy_Attack_1_Boss();
			break;
		case POWER_ATTACK_TRIGGER_BOSS:
			return new Enemy_Attack_3_Boss();
			break;
		case POWER_ATTACK_2_TRIGGER_BOSS:
			return new Enemy_Power_Attack_Boss();
			break;
		}
	}

	return nullptr;
}

void Enemy_Move_Boss::update(Enemy_Basic * _Enemy, int targetX, int targetY)
{
	_Enemy->setEnemyImageError(0);

	ImageUpdateFunc(_Enemy);


	//방향전환
	if (_Enemy->getEnemyInfo()->x < targetX) _Enemy->setEnemyReverse(true);
	else _Enemy->setEnemyReverse(false);


	//이동 
	float angle = getAngle(_Enemy->getEnemyInfo()->x, _Enemy->getEnemyInfo()->y, targetX, targetY);

	_Enemy->setEnemyPointX(_Enemy->getEnemyInfo()->x + cosf(angle)*MOVESPEED_LEFT_RIGHT*0.7f);
	_Enemy->setEnemyPointY(_Enemy->getEnemyInfo()->y - sinf(angle)*MOVESPEED_UP_DOWN*0.7f);

	/*
			if ((_Enemy->getEnemyInfo()->y < targetY - 15 || _Enemy->getEnemyInfo()->y > targetY + 15))
		{
			_Enemy->setEnemyPointY(_Enemy->getEnemyInfo()->y - sinf(angle)*MOVESPEED_LEFT_RIGHT*1.5f);
		}
		//만약 대쉬공격 사거리보다 멀 경우 전진하게
		if (getDistance(_Enemy->getEnemyInfo()->x, _Enemy->getEnemyInfo()->y, targetX, targetY) > DASH_ATTACK_RANGE)
		{
			_Enemy->setEnemyPointX(_Enemy->getEnemyInfo()->x + cosf(angle)*MOVESPEED_LEFT_RIGHT);
		}

	*/

}

void Enemy_Move_Boss::release(Enemy_Basic * _Enemy)
{
}

void Enemy_Move_Boss::enter_this_state(Enemy_Basic * _Enemy)
{
	_Enemy->setEnemyTestText("IDLE");
	//_Enemy->set_Enemy_State_Enum();

	char str[128] = "Misuzu_Move";

	_Enemy->setEnemyImage(IMAGEMANAGER->findImage(str));

	frameCount = 0;
	frameUpdateCount = 5;

	_Enemy->setEnemyImageError(0);
	_Enemy->setEnemyFrameX(0);

	if (_Enemy->getEnemyInfo()->isRight) _Enemy->setEnemyFrameY(0);
	else _Enemy->setEnemyFrameY(1);
}



void Enemy_Move_Boss::ImageUpdateFunc(Enemy_Basic * _Enemy)
{
	frameCount++;

	if (frameCount % frameUpdateCount == 0)
	{
		if (_Enemy->getEnemyInfo()->isRight)
		{
			_Enemy->setEnemyFrameY(0);
			_Enemy->setEnemyFrameX(_Enemy->getEnemyInfo()->CurrentframeX + 1);

			if (_Enemy->getEnemyInfo()->CurrentframeX > _Enemy->getEnemyInfo()->_image->getMaxFrameX()) _Enemy->setEnemyFrameX(0);
		}
		else
		{
			_Enemy->setEnemyFrameY(1);
			_Enemy->setEnemyFrameX(_Enemy->getEnemyInfo()->CurrentframeX + 1);

			if (_Enemy->getEnemyInfo()->CurrentframeX > _Enemy->getEnemyInfo()->_image->getMaxFrameX()) _Enemy->setEnemyFrameX(0);
		}
	}
}
