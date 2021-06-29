#include "stdafx.h"
#include "Enemy_Basic.h"

#include "Enemy_Dash_Attack_Boss.h"
#include "Enemy_Tount_Boss.h"
#include "Enemy_Idle.h"

Enemy_State * Enemy_Dash_Attack_Boss::input_state(Enemy_Basic * _Enemy, bool reverse, int targetX, int targetY)
{
	return nullptr;
}

void Enemy_Dash_Attack_Boss::update(Enemy_Basic * _Enemy, int targetX, int targetY)
{
	ImageUpdateFunc(_Enemy);

	//방향전환
	if (_Enemy->getEnemyInfo()->x > targetX) _Enemy->setEnemyReverse(true);
	else _Enemy->setEnemyReverse(false);


	//이동 
	float angle = getAngle(_Enemy->getEnemyInfo()->x, _Enemy->getEnemyInfo()->y, targetX, targetY);

	_Enemy->setEnemyPointX(_Enemy->getEnemyInfo()->x + cosf(angle)*MOVESPEED_LEFT_RIGHT*0.7f);
	_Enemy->setEnemyPointY(_Enemy->getEnemyInfo()->y - sinf(angle)*MOVESPEED_UP_DOWN*0.7f);

	/*
	y축은 완전히 전환하지 않고, 일정 거리만큼만 내려감.
	적에게 명중, 혹은 일정시간동안 맞지않으면 tount로 돌아감.
	
	*/

}

void Enemy_Dash_Attack_Boss::release(Enemy_Basic * _Enemy)
{
}

void Enemy_Dash_Attack_Boss::enter_this_state(Enemy_Basic * _Enemy)
{
	_Enemy->setEnemyTestText("IDLE");
	//_Enemy->set_Enemy_State_Enum();

	char str[128] = "";

	_Enemy->setEnemyImage(IMAGEMANAGER->findImage(str));

	frameCount = 0;
	frameUpdateCount = 5;

	_Enemy->setEnemyFrameX(0);

	if (_Enemy->getEnemyInfo()->isRight) _Enemy->setEnemyFrameY(0);
	else _Enemy->setEnemyFrameY(1);
}

void Enemy_Dash_Attack_Boss::call_Idle_function(Enemy_Basic * _Enemy)
{
}

void Enemy_Dash_Attack_Boss::ImageUpdateFunc(Enemy_Basic * _Enemy)
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
