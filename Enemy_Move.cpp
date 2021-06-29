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

		/*if (getDistance(_Enemy->getEnemyInfo()->x, _Enemy->getEnemyInfo()->y, 
			targetX, targetY) < OBSERVE_RANGE)
		{
		}*/
		break;

		//Y축 보정 후 , 해당 타겟과의 거리가 일정 거리 일 경우 아래 공격 함수들 실행


	case NORMAL_ATTACK_TRIGGER: //일반 공격일경우, distance만 받고 공격범위 내까지 이동 시키기.

		if ((_Enemy->getEnemyInfo()->y >= targetY - 15 && _Enemy->getEnemyInfo()->y <= targetY + 15) &&
			getDistance(_Enemy->getEnemyInfo()->x, _Enemy->getEnemyInfo()->y, targetX, targetY) <= NORMAL_ATTACK_RANGE)  return new Enemy_Attack();
		
		break;
	case DASH_ATTACK_TRIGGER:

		if ((_Enemy->getEnemyInfo()->y >= targetY - 30 && _Enemy->getEnemyInfo()->y <= targetY + 30) &&
			(getDistance(_Enemy->getEnemyInfo()->x, _Enemy->getEnemyInfo()->y, targetX, targetY) <= DASH_ATTACK_RANGE &&
			getDistance(_Enemy->getEnemyInfo()->x, _Enemy->getEnemyInfo()->y, targetX, targetY) >= DASH_ATTACK_RANGE-40))  return new Enemy_Run();
		
		break;
	case JUMP_ATTACK_TRIGGER:
		if ((_Enemy->getEnemyInfo()->y >= targetY - 20 && _Enemy->getEnemyInfo()->y <= targetY + 20) &&
			(getDistance(_Enemy->getEnemyInfo()->x, _Enemy->getEnemyInfo()->y, targetX, targetY) <= JUMP_ATTACK_RANGE &&
				getDistance(_Enemy->getEnemyInfo()->x, _Enemy->getEnemyInfo()->y, targetX, targetY) >= JUMP_ATTACK_RANGE-30)) return new Enemy_Jump();
		
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

	float angle = getAngle(_Enemy->getEnemyInfo()->x, _Enemy->getEnemyInfo()->y, targetX, targetY);



	//일정 거리안에 있으면 움직이게 
	switch (_Enemy->getAITRIGGER())
	{
	case OBSERVE_STATE_TRIGGER:

		if (!isObserve)
		{
			if (getDistance(_Enemy->getEnemyInfo()->x, _Enemy->getEnemyInfo()->y, targetX, targetY) > OBSERVE_RANGE)
			{
				_Enemy->setEnemyPointX(_Enemy->getEnemyInfo()->x + cosf(angle)*MOVESPEED_LEFT_RIGHT);
				_Enemy->setEnemyPointY(_Enemy->getEnemyInfo()->y - sinf(angle)*MOVESPEED_UP_DOWN);
			}
			else isObserve = true;
		}
		else
		{
			ObserveCount++;

			if (ObserveCount%RandomObserveUpdateCount == 0)
			{
				RandomAngle = RND->getFromFloatTo(0, PI2);			  //랜덤한 앵글로 이동하게 시행함.
				RandomObserveUpdateCount = RND->getFromIntTo(70, 120); //다음 랜덤 방향으로 가게 해주기
			}

			
			_Enemy->setEnemyPointX(_Enemy->getEnemyInfo()->x + cosf(RandomAngle)*MOVESPEED_LEFT_RIGHT*0.7f);
			_Enemy->setEnemyPointY(_Enemy->getEnemyInfo()->y - sinf(RandomAngle)*MOVESPEED_UP_DOWN*0.7f);
		}



		break;
	
	case NORMAL_ATTACK_TRIGGER: //일반 공격일경우, distance만 받고 공격범위 내까지 이동 시키기.

		//if (getDistance(_Enemy->getEnemyInfo()->x, _Enemy->getEnemyInfo()->y, targetX, targetY) > NORMAL_ATTACK_RANGE
		//	&& (_Enemy->getEnemyInfo()->y < targetY - 3|| _Enemy->getEnemyInfo()->y > targetY + 3))
		{
			//float angle = getAngle(_Enemy->getEnemyInfo()->x, _Enemy->getEnemyInfo()->y, targetX, targetY);

			_Enemy->setEnemyPointX(_Enemy->getEnemyInfo()->x + cosf(angle)*MOVESPEED_LEFT_RIGHT*0.7f);
			_Enemy->setEnemyPointY(_Enemy->getEnemyInfo()->y - sinf(angle)*MOVESPEED_UP_DOWN*0.7f);

		}

		//플레이어랑 y축 차이가 많이 심할경우, y축 보정해주기	
		if ((_Enemy->getEnemyInfo()->y < targetY - 15 || _Enemy->getEnemyInfo()->y > targetY + 15))
		{
			_Enemy->setEnemyPointY(_Enemy->getEnemyInfo()->y - sinf(angle)*MOVESPEED_LEFT_RIGHT*1.5f);
		}
		//만약 대쉬공격 사거리보다 멀 경우 전진하게
		if (getDistance(_Enemy->getEnemyInfo()->x, _Enemy->getEnemyInfo()->y, targetX, targetY) > DASH_ATTACK_RANGE)
		{
			_Enemy->setEnemyPointX(_Enemy->getEnemyInfo()->x + cosf(angle)*MOVESPEED_LEFT_RIGHT);
		}


		break;

	case DASH_ATTACK_TRIGGER:

		
		//플레이어랑 y축 차이가 많이 심할경우, y축 보정해주기	
		if ((_Enemy->getEnemyInfo()->y < targetY - 30 || _Enemy->getEnemyInfo()->y > targetY + 30))
		{
			_Enemy->setEnemyPointY(_Enemy->getEnemyInfo()->y - sinf(angle)*MOVESPEED_LEFT_RIGHT*1.5f);
		}
		//만약 대쉬공격 사거리보다 멀 경우 전진하게
		if (getDistance(_Enemy->getEnemyInfo()->x, _Enemy->getEnemyInfo()->y, targetX, targetY) > DASH_ATTACK_RANGE)
		{
			_Enemy->setEnemyPointX(_Enemy->getEnemyInfo()->x + cosf(angle)*MOVESPEED_LEFT_RIGHT);
		}
		//만약 대쉬공격 사거리보다 멀 경우 전진하게
		else if (getDistance(_Enemy->getEnemyInfo()->x, _Enemy->getEnemyInfo()->y, targetX, targetY) < DASH_ATTACK_RANGE - 40)
		{
			_Enemy->setEnemyPointX(_Enemy->getEnemyInfo()->x - cosf(angle)*MOVESPEED_LEFT_RIGHT);
		}

		break;
	case JUMP_ATTACK_TRIGGER:

		//플레이어랑 y축 차이가 많이 심할경우, y축 보정해주기	
		if((_Enemy->getEnemyInfo()->y < targetY - 20 || _Enemy->getEnemyInfo()->y > targetY + 20))
		{
			_Enemy->setEnemyPointY(_Enemy->getEnemyInfo()->y - sinf(angle)*MOVESPEED_LEFT_RIGHT);
		}
		//만약 점프공격 사거리보다 멀 경우 전진하게
		if (getDistance(_Enemy->getEnemyInfo()->x, _Enemy->getEnemyInfo()->y, targetX, targetY) > JUMP_ATTACK_RANGE)
		{
			_Enemy->setEnemyPointX(_Enemy->getEnemyInfo()->x + cosf(angle)*MOVESPEED_LEFT_RIGHT);
		}
		//만약 점프 공격 사거리보다 가까울 경우 후진하게
		else if (getDistance(_Enemy->getEnemyInfo()->x, _Enemy->getEnemyInfo()->y, targetX, targetY) < JUMP_ATTACK_RANGE - 30)
		{
			_Enemy->setEnemyPointX(_Enemy->getEnemyInfo()->x - cosf(angle)*MOVESPEED_LEFT_RIGHT);
		}

		break;
	}



	

	//프레임 이미지 돌리는 함수
	ImageUpdateFunc(_Enemy);


	if (_Enemy->getEnemyInfo()->x > targetX)
	{
		_Enemy->setEnemyReverse(false);
	}
	else _Enemy->setEnemyReverse(true);

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
	

	_Enemy->setEnemyFrameX(0);

	if (_Enemy->getEnemyInfo()->isRight) _Enemy->setEnemyFrameY(0);
	else _Enemy->setEnemyFrameY(1);

	isObserve = false; //탐색중인지
	ObserveCount = 0;									  //랜덤방향 업데이트 카운트
	RandomAngle = RND->getFromFloatTo(0,PI2);			  //랜덤한 앵글로 이동하게 시행함.
	RandomObserveUpdateCount = RND->getFromIntTo(70, 120); //다음 랜덤 방향으로 가게 해주기

}

void Enemy_Move::ImageUpdateFunc(Enemy_Basic * _Enemy)
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

