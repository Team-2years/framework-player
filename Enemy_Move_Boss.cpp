#include "stdafx.h"

#include "Enemy_Basic.h"

#include "Enemy_Move_Boss.h"
#include "Enemy_Attack_1_Boss.h"
#include "Enemy_Attack_3_Boss.h"


Enemy_State * Enemy_Move_Boss::input_state(Enemy_Basic * _Enemy, bool reverse, int targetX, int targetY)
{



	return nullptr;
}

void Enemy_Move_Boss::update(Enemy_Basic * _Enemy, int targetX, int targetY)
{
}

void Enemy_Move_Boss::release(Enemy_Basic * _Enemy)
{
}

void Enemy_Move_Boss::enter_this_state(Enemy_Basic * _Enemy)
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

void Enemy_Move_Boss::call_Idle_function(Enemy_Basic * _Enemy)
{
}

void Enemy_Move_Boss::ImageUpdateFunc(Enemy_Basic * _Enemy)
{
}
