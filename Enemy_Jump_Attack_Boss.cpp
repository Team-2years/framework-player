#include "stdafx.h"
#include "Enemy_Basic.h"

#include "Enemy_Jump_Attack_Boss.h"
#include "Enemy_Jump_Attack_stun_Boss.h"
#include "Enemy_Jump_Attack_not_stun.h"


#include "Enemy_Idle_Boss.h"

Enemy_State * Enemy_Jump_Attack_Boss::input_state(Enemy_Basic * _Enemy, bool reverse, int targetX, int targetY)
{
	if (_Enemy->getEnemyInfo()->y - _Enemy->getEnemyInfo()->z < _Enemy->getEnemyInfo()->y)
	{
		_Enemy->setEnemyGravity(0);
		_Enemy->setEnemyJumpSpeed(0);

		_Enemy->setEnemyPointZ(0);

		int rnd = RND->getFromIntTo(1, 2);

		//if(rnd==1) return new Enemy_Jump_Attack_stun_Boss();
		//else return new Enemy_Jump_Attack_not_stun();
		
		return new Enemy_Jump_Attack_not_stun();
	}

	return nullptr;
}

void Enemy_Jump_Attack_Boss::update(Enemy_Basic * _Enemy, int targetX, int targetY)
{

	if(_Enemy->getEnemyInfo()->gravity > BOSS_JUMP_SPEED)  
		 _Enemy->setEnemyImage(IMAGEMANAGER->findImage("Misuzu_Jump_Down"));
	
	float angle = getAngle(_Enemy->getEnemyInfo()->x, _Enemy->getEnemyInfo()->y, targetX, targetY);

	_Enemy->setEnemyPointX(_Enemy->getEnemyInfo()->x + cosf(angle)*MOVESPEED_LEFT_RIGHT*0.7f);
	_Enemy->setEnemyPointY(_Enemy->getEnemyInfo()->y - sinf(angle)*MOVESPEED_UP_DOWN*0.7f);


	ImageUpdateFunc(_Enemy);

	_Enemy->setEnemyGravity(_Enemy->getEnemyInfo()->gravity + BOSS_GRAVITY);
	_Enemy->setEnemyPointZ(_Enemy->getEnemyInfo()->z + _Enemy->getEnemyInfo()->gravity - _Enemy->getEnemyInfo()->JumpPower);



}

void Enemy_Jump_Attack_Boss::release(Enemy_Basic * _Enemy)
{
}

void Enemy_Jump_Attack_Boss::enter_this_state(Enemy_Basic * _Enemy)
{
	_Enemy->setEnemyTestText("IDLE");
	//_Enemy->set_Enemy_State_Enum();

	char str[128] = "Misuzu_Jump_Up";

	_Enemy->setEnemyImage(IMAGEMANAGER->findImage(str));

	_Enemy->setEnemyJumpSpeed(BOSS_JUMP_SPEED);

	frameCount = 0;
	frameUpdateCount = 100;

	_Enemy->setEnemyFrameX(0);

	if (_Enemy->getEnemyInfo()->isRight) _Enemy->setEnemyFrameY(0);
	else _Enemy->setEnemyFrameY(1);
}


void Enemy_Jump_Attack_Boss::ImageUpdateFunc(Enemy_Basic * _Enemy)
{
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
