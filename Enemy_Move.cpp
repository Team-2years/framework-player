#include "stdafx.h"

#include "Enemy_Basic.h"

#include "Enemy_Move.h"
#include "Enemy_Idle.h"
#include "Enemy_Attack.h"
#include "Enemy_Run.h"
#include "Enemy_Jump.h"

Enemy_State * Enemy_Move::input_state(Enemy_Basic * _Enemy, bool reverse, int targetX, int targetY)
{

	switch (_Enemy->getAITRIGGER())
	{
	case OBSERVE_STATE_TRIGGER:

		if (getDistance(_Enemy->getEnemyInfo()->x, _Enemy->getEnemyInfo()->y, 
			targetX, targetY) < OBSERVE_RANGE)
		{
		}
		break;

	case NORMAL_ATTACK_TRIGGER: //일반 공격일경우, distance만 받고 공격범위 내까지 이동 시키기.

		if (getDistance(_Enemy->getEnemyInfo()->x, _Enemy->getEnemyInfo()->y, 
			targetX, targetY) <= NORMAL_ATTACK_RANGE)
		{
			return new Enemy_Attack();
		}
		break;

	case DASH_ATTACK_TRIGGER:

		if (getDistance(_Enemy->getEnemyInfo()->x, _Enemy->getEnemyInfo()->y, 
			targetX, targetY) >= DASH_ATTACK_RANGE)
		{
			return new Enemy_Run();
		}

		break;
	case JUMP_ATTACK_TRIGGER:
		if (getDistance(_Enemy->getEnemyInfo()->x, _Enemy->getEnemyInfo()->y, 
			targetX, targetY) < JUMP_ATTACK_RANGE)
		{
			return new Enemy_Jump();
		}

		break;
	}


	return nullptr;
	//해당 거리 벗어나면 IDLE로 .
	/*
	일단 임시로 설정해놓았음. 추후 수정해야함.
	*/


}

void Enemy_Move::update(Enemy_Basic* _Enemy, int targetX, int targetY)
{

	//일정 거리안에 있으면 움직이게 
	switch (_Enemy->getAITRIGGER())
	{
	case OBSERVE_STATE_TRIGGER:
	
		if (getDistance(_Enemy->getEnemyInfo()->x, _Enemy->getEnemyInfo()->y, targetX, targetY) < OBSERVE_RANGE)
		{
			float angle = getAngle(_Enemy->getEnemyInfo()->x, _Enemy->getEnemyInfo()->y, targetX, targetY);

			_Enemy->setEnemyPointX(_Enemy->getEnemyInfo()->x + cosf(angle)*MOVESPEED_LEFT_RIGHT);
			_Enemy->setEnemyPointY(_Enemy->getEnemyInfo()->y - sinf(angle)*MOVESPEED_UP_DOWN);

		}
		break;
	
	case NORMAL_ATTACK_TRIGGER: //일반 공격일경우, distance만 받고 공격범위 내까지 이동 시키기.

		if (getDistance(_Enemy->getEnemyInfo()->x, _Enemy->getEnemyInfo()->y, targetX, targetY) > NORMAL_ATTACK_RANGE
			&& (_Enemy->getEnemyInfo()->y < targetY - 15 || _Enemy->getEnemyInfo()->y > targetY + 15))
		{
			float angle = getAngle(_Enemy->getEnemyInfo()->x, _Enemy->getEnemyInfo()->y, targetX, targetY);

			_Enemy->setEnemyPointX(_Enemy->getEnemyInfo()->x + cosf(angle)*MOVESPEED_LEFT_RIGHT);
			_Enemy->setEnemyPointY(_Enemy->getEnemyInfo()->y - sinf(angle)*MOVESPEED_UP_DOWN);

		}
		/*else
		{
			Enemy_State* AttackState;
			AttackState = new Enemy_Attack();

			_Enemy->set_Enemy_State(AttackState);
		}*/
		break;

	case DASH_ATTACK_TRIGGER:

		if (getDistance(_Enemy->getEnemyInfo()->x, _Enemy->getEnemyInfo()->y, targetX, targetY) > DASH_ATTACK_RANGE 
			&& (_Enemy->getEnemyInfo()->y < targetY -15 || _Enemy->getEnemyInfo()->y > targetY+15)) 
		{

			float angle = -getAngle(_Enemy->getEnemyInfo()->x, _Enemy->getEnemyInfo()->y, targetX, targetY);

			_Enemy->setEnemyPointX(_Enemy->getEnemyInfo()->x + cosf(angle)*MOVESPEED_LEFT_RIGHT);
			_Enemy->setEnemyPointY(_Enemy->getEnemyInfo()->y - sinf(angle)*MOVESPEED_UP_DOWN);
		}
		break;
	case JUMP_ATTACK_TRIGGER:

		if (getDistance(_Enemy->getEnemyInfo()->x, _Enemy->getEnemyInfo()->y, targetX, targetY) > JUMP_ATTACK_RANGE
			&& (_Enemy->getEnemyInfo()->y < targetY - 15 || _Enemy->getEnemyInfo()->y > targetY + 15))
		{

			float angle = -getAngle(_Enemy->getEnemyInfo()->x, _Enemy->getEnemyInfo()->y, targetX, targetY);

			_Enemy->setEnemyPointX(_Enemy->getEnemyInfo()->x + cosf(angle)*MOVESPEED_LEFT_RIGHT);
			_Enemy->setEnemyPointY(_Enemy->getEnemyInfo()->y - sinf(angle)*MOVESPEED_UP_DOWN);

		}

		break;
	}



	//if (_Enemy->getAITRIGGER().TriggerName == NORMAL_ATTACK_TRIGGER)
	//{
	//	if (getDistance(_Enemy->getEnemyInfo()->x, _Enemy->getEnemyInfo()->y, targetX, targetY) < _Enemy->getEnemyInfo()->range &&
	//		getDistance(_Enemy->getEnemyInfo()->x, _Enemy->getEnemyInfo()->y, targetX, targetY) > 50)
	//	{
	//		float angle = getAngle(_Enemy->getEnemyInfo()->x, _Enemy->getEnemyInfo()->y, targetX, targetY);
	//		_Enemy->setEnemyPointX(_Enemy->getEnemyInfo()->x + cosf(angle)*MOVESPEED_LEFT_RIGHT);
	//		_Enemy->setEnemyPointY(_Enemy->getEnemyInfo()->y - sinf(angle)*MOVESPEED_UP_DOWN);
	//	}
	//}


	//프레임 이미지 돌리는 함수
	ImageUpdateFunc(_Enemy);



}

void Enemy_Move::release(Enemy_Basic* _Enemy)
{
}

void Enemy_Move::render()
{
}

void Enemy_Move::enter_this_state(Enemy_Basic * _Enemy)
{
	_Enemy->setEnemyTestText("MOVE");
	_Enemy->set_Enemy_State_Enum(MOVE);



	char str[128] = "Enemy_Image_Move_";

	strcat_s(str, _Enemy->getEnemyInfo()->imageName);

	_Enemy->setEnemyImageKey(str);

	string Idle_Image = str;
	_Enemy->setEnemyImage(IMAGEMANAGER->findImage(Idle_Image));

	frameCount = 0;
	frameUpdateCount = 5;
	index = 0;

}

void Enemy_Move::ImageUpdateFunc(Enemy_Basic * _Enemy)
{
	frameCount++;

	if (frameCount % frameUpdateCount == 0)
	{
		if (_Enemy->getEnemyInfo()->isRight)
		{
			_Enemy->getEnemyInfo()->_image->setFrameY(0);
			_Enemy->getEnemyInfo()->_image->setFrameX(index);


			index++;

			if (index > _Enemy->getEnemyInfo()->_image->getMaxFrameX()) index = 0;
		}
		else
		{
			_Enemy->getEnemyInfo()->_image->setFrameY(1);
			_Enemy->getEnemyInfo()->_image->setFrameX(index);

			index++;

			if (index > _Enemy->getEnemyInfo()->_image->getMaxFrameX()) index = 0;
		}
	}

}

