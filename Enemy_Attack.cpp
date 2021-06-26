#include "stdafx.h"
#include "Enemy_Attack.h"
#include "Enemy_Attack_2.h"



#include "Enemy_Move.h"

#include "Enemy_Basic.h"



Enemy_State * Enemy_Attack::input_state(Enemy_Basic * _Enemy, bool reverse, int targetX, int targetY)
{
	if (getDistance(_Enemy->getEnemyInfo()->x, _Enemy->getEnemyInfo()->y, targetX, targetY)
		> _Enemy->getEnemyInfo()->AttackRange)
	{
		return new Enemy_Move();
	}


	return nullptr;
}

void Enemy_Attack::update(Enemy_Basic * _Enemy, int targetX, int targetY)
{

	ImageUpdateFunc(_Enemy);
}

void Enemy_Attack::release(Enemy_Basic * _Enemy)
{
}

void Enemy_Attack::render()
{
}

void Enemy_Attack::enter_this_state(Enemy_Basic * _Enemy)
{
	_Enemy->setEnemyTestText("ATTACK");
	_Enemy->set_Enemy_State_Enum(ATTACK_1);

	char str[128] = "Enemy_Image_Attack_1_";

	strcat_s(str, _Enemy->getEnemyInfo()->imageName);

	string Idle_Image = str;


	_Enemy->setEnemyImageKey(str);

	_Enemy->setEnemyImage(IMAGEMANAGER->findImage(Idle_Image));

	frameCount = 0;
	frameUpdateCount = 5;
	index = 0;


}

void Enemy_Attack::call_Attack_2_function(Enemy_Basic* _Enemy)
{
	Enemy_State* Attack_2;

	Attack_2 = new Enemy_Attack_2();

	_Enemy->set_Enemy_State(Attack_2);
}

void Enemy_Attack::ImageUpdateFunc(Enemy_Basic * _Enemy)
{
	frameCount++;

	if (frameCount % frameUpdateCount == 0)
	{
		if (_Enemy->getEnemyInfo()->isRight)
		{
			_Enemy->getEnemyInfo()->_image->setFrameY(0);
			_Enemy->getEnemyInfo()->_image->setFrameX(index);


			index++;

			if (index > _Enemy->getEnemyInfo()->_image->getMaxFrameX())
			{
				//index = 0;



				call_Attack_2_function(_Enemy);
			}
		}
		else
		{
			_Enemy->getEnemyInfo()->_image->setFrameY(1);
			_Enemy->getEnemyInfo()->_image->setFrameX(index);

			index++;

			if (index > _Enemy->getEnemyInfo()->_image->getMaxFrameX())
			{
				//index = 0;

				call_Attack_2_function(_Enemy);
			}
		}
	}
}
