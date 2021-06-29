#include "stdafx.h"
#include "Enemy_Run.h"


#include "Enemy_Basic.h"
#include "Enemy_DashAttack.h"



//_Enemy->set_Enemy_State_Enum(RUN);

Enemy_State * Enemy_Run::input_state(Enemy_Basic * _Enemy, bool reverse, int targetX, int targetY)
{

	int DashAttackRange;

	switch (_Enemy->getEnemyKind())
	{
	case SCHOOL_GIRL: DashAttackRange = 300;
		break;
	case SCHOOL_BOY: DashAttackRange = 200;
		break;
	}

	if (getDistance(_Enemy->getEnemyInfo()->x, _Enemy->getEnemyInfo()->y, targetX, targetY) <= DashAttackRange)
	//	&& (_Enemy->getEnemyInfo()->y > targetY - 15 && _Enemy->getEnemyInfo()->y < targetY + 15))
	{
		return new Enemy_DashAttack();
	}


	return nullptr;
}

void Enemy_Run::update(Enemy_Basic * _Enemy, int targetX, int targetY)
{


	int DashAttackRange;

	switch (_Enemy->getEnemyKind())
	{
	case SCHOOL_GIRL: DashAttackRange = 300;
		break;
	case SCHOOL_BOY: DashAttackRange = 200;
		break;
	}


	//===================================================
	//이동
	//===================================================

	float angle = getAngle(_Enemy->getEnemyInfo()->x, _Enemy->getEnemyInfo()->y, targetX, targetY);
	

	//if (getDistance(_Enemy->getEnemyInfo()->x, _Enemy->getEnemyInfo()->y, targetX, targetY) > 300
	//	&& (_Enemy->getEnemyInfo()->y < targetY - 15 || _Enemy->getEnemyInfo()->y > targetY + 15))
	//{
	//	
	//	_Enemy->setEnemyPointX(_Enemy->getEnemyInfo()->x + cosf(angle)*MOVESPEED_RUN);
	//	_Enemy->setEnemyPointY(_Enemy->getEnemyInfo()->y - sinf(angle)*MOVESPEED_RUN*0.5f);
	//}
		if ((_Enemy->getEnemyInfo()->y < targetY - 20 || _Enemy->getEnemyInfo()->y > targetY + 20))
		{
			_Enemy->setEnemyPointY(_Enemy->getEnemyInfo()->y - sinf(angle)*MOVESPEED_RUN*0.5f);
		}

		if (getDistance(_Enemy->getEnemyInfo()->x, _Enemy->getEnemyInfo()->y, targetX, targetY) > DashAttackRange)
		{
			_Enemy->setEnemyPointX(_Enemy->getEnemyInfo()->x + cosf(angle)*MOVESPEED_RUN);
		}
	

	//===================================================
	//이미지 업데이트
	//===================================================

	ImageUpdateFunc(_Enemy);
}

void Enemy_Run::release(Enemy_Basic * _Enemy)
{
}


void Enemy_Run::enter_this_state(Enemy_Basic * _Enemy)
{
	//Enemy_Image_Run_School_Girl

	_Enemy->setEnemyTestText("RUN");
	_Enemy->set_Enemy_State_Enum(RUN);



	char str[128] = "Enemy_Image_Run_";

	strcat_s(str, _Enemy->getEnemyInfo()->imageName);

	_Enemy->setEnemyImageKey(str);

	string Idle_Image = str;
	_Enemy->setEnemyImage(IMAGEMANAGER->findImage(Idle_Image));

	frameCount = 0;
	frameUpdateCount = 5;


	_Enemy->setEnemyFrameX(0);

	if(_Enemy->getEnemyInfo()->isRight) _Enemy->setEnemyFrameY(0);
	else _Enemy->setEnemyFrameY(1);

	


}

void Enemy_Run::ImageUpdateFunc(Enemy_Basic * _Enemy)
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
