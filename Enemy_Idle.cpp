#include "stdafx.h"
#include "Enemy_Idle.h"
#include "Enemy_Move.h"

#include "Enemy_Basic.h"

Enemy_State * Enemy_Idle::input_state(Enemy_Basic * _Enemy, bool reverse, int targetX, int targetY)
{
	if (_Enemy->getAITRIGGER() != OBSERVE_STATE_TRIGGER)
	{
		if (getDistance(_Enemy->getEnemyInfo()->x, _Enemy->getEnemyInfo()->y, targetX, targetY) < _Enemy->getEnemyInfo()->range)
		{
			return new Enemy_Move();
		}
	}





	return nullptr;
}

void Enemy_Idle::update(Enemy_Basic* _Enemy, int targetX, int targetY)
{
	
	/*if (getDistance(_Enemy->getEnemyInfo()->x, _Enemy->getEnemyInfo()->y, targetX, targetY) < _Enemy->getEnemyInfo()->range)
	{
		Enemy_State*
	}*/

	//프레임 이미지 돌리는 함수
	ImageUpdateFunc(_Enemy);

}

void Enemy_Idle::release(Enemy_Basic* _Enemy)
{
}

void Enemy_Idle::render()
{
}

void Enemy_Idle::enter_this_state(Enemy_Basic * _Enemy)
{
	_Enemy->setEnemyTestText("IDLE");
	_Enemy->set_Enemy_State_Enum(IDLE);

	char str[128] = "Enemy_Image_Idle_";

	strcat_s(str, _Enemy->getEnemyInfo()->imageName);


	_Enemy->setEnemyImageKey(str);



	string Idle_Image = str;

	_Enemy->setEnemyImage(IMAGEMANAGER->findImage(Idle_Image));

	frameCount = 0;
	frameUpdateCount = 5;
	index = 0;

}

void Enemy_Idle::ImageUpdateFunc(Enemy_Basic* _Enemy)
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
