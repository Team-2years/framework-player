#include "stdafx.h"
#include "Enemy_DashAttack.h"

#include "Enemy_Basic.h"
#include "Enemy_Idle.h"


Enemy_State * Enemy_DashAttack::input_state(Enemy_Basic * _Enemy, bool reverse, int targetX, int targetY)
{
	return nullptr;
}

void Enemy_DashAttack::update(Enemy_Basic * _Enemy, int targetX, int targetY)
{
	ImageUpdateFunc(_Enemy);
}

void Enemy_DashAttack::release(Enemy_Basic * _Enemy)
{
}


void Enemy_DashAttack::enter_this_state(Enemy_Basic * _Enemy)
{
	//Enemy_Image_Dash_Attack_School_Girl

	_Enemy->setEnemyTestText("DASH_ATTACK");
	_Enemy->set_Enemy_State_Enum(ATTACK_1);



	char str[128] = "Enemy_Image_Dash_Attack_";

	strcat_s(str, _Enemy->getEnemyInfo()->imageName);

	string Idle_Image = str;

	_Enemy->setEnemyImage(IMAGEMANAGER->findImage(Idle_Image));

	frameCount = 0;
	frameUpdateCount = 5;
	index = 0;
}

void Enemy_DashAttack::call_Idle_function(Enemy_Basic * _Enemy)
{
	Enemy_State* idle_state;

	idle_state = new Enemy_Idle();

	_Enemy->set_Enemy_State(idle_state);

}

void Enemy_DashAttack::ImageUpdateFunc(Enemy_Basic * _Enemy)
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



				call_Idle_function(_Enemy);
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

				call_Idle_function(_Enemy);
			}
		}
	}

}
