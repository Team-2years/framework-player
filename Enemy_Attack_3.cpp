#include "stdafx.h"
#include "Enemy_Attack_3.h"
#include "Enemy_Idle.h"

#include "Enemy_Basic.h"



Enemy_State * Enemy_Attack_3::input_state(Enemy_Basic * _Enemy, bool reverse, int targetX, int targetY)
{
	return nullptr;
}

void Enemy_Attack_3::update(Enemy_Basic * _Enemy, int targetX, int targetY)
{

	ImageUpdateFunc(_Enemy);


}

void Enemy_Attack_3::release(Enemy_Basic * _Enemy)
{
}

void Enemy_Attack_3::render()
{
}

void Enemy_Attack_3::enter_this_state(Enemy_Basic * _Enemy)
{
	_Enemy->setEnemyTestText("ATTACK_3");
	_Enemy->set_Enemy_State_Enum(ATTACK_1);



	char str[128] = "Enemy_Image_Attack_3_";

	strcat_s(str, _Enemy->getEnemyInfo()->imageName);

	string Idle_Image = str;

	_Enemy->setEnemyImage(IMAGEMANAGER->findImage(Idle_Image));

	frameCount = 0;
	frameUpdateCount = 5;
	index = 0;

}

void Enemy_Attack_3::call_Idle_function(Enemy_Basic * _Enemy)
{
	Enemy_State* Idle_ST;

	Idle_ST = new Enemy_Idle();

	_Enemy->set_Enemy_State(Idle_ST);
}

void Enemy_Attack_3::ImageUpdateFunc(Enemy_Basic * _Enemy)
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
				_Enemy->setEnemyAiTrigger(OBSERVE_STATE_TRIGGER);

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

				_Enemy->setEnemyAiTrigger(OBSERVE_STATE_TRIGGER);
			}
		}
	}
}

