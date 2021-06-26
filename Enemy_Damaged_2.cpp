#include "stdafx.h"
#include "Enemy_Basic.h"


#include "Enemy_Damaged_2.h"
#include "Enemy_Damaged_3.h"
#include "Enemy_Idle.h"


Enemy_State * Enemy_Damaged_2::input_state(Enemy_Basic * _Enemy, bool reverse, int targetX, int targetY)
{
	return nullptr;
}

void Enemy_Damaged_2::update(Enemy_Basic * _Enemy, int targetX, int targetY)
{
	/*

	���߿� �̹��� ������ �������϶� ȸ���ϵ��� �ٲ� ����.

	*/


	//recoverCount++;
	//if (recoverCount > 100)
	//{
	//	recoverCount = 0;
	//	Enemy_State* _change_Idle;
	//	_change_Idle = new Enemy_Idle;
	//	_Enemy->set_Enemy_State(_change_Idle);
	//}

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

void Enemy_Damaged_2::release(Enemy_Basic * _Enemy)
{
}

void Enemy_Damaged_2::render()
{
}

void Enemy_Damaged_2::enter_this_state(Enemy_Basic * _Enemy)
{
	_Enemy->setEnemyTestText("DAMAGED_2");
	_Enemy->set_Enemy_State_Enum(DAMAGED_1);

	recoverCount = 0;


	char str[128] = "Enemy_Image_Attacked_2";

	strcat_s(str, _Enemy->getEnemyInfo()->imageName);

	_Enemy->setEnemyImageKey(str);

	string Idle_Image = str;

	_Enemy->setEnemyImage(IMAGEMANAGER->findImage(Idle_Image));

	frameCount = 0;
	frameUpdateCount = 5;
	index = 0;

}

void Enemy_Damaged_2::call_Idle_function(Enemy_Basic * _Enemy)
{
	Enemy_State* Idle_ST;

	Idle_ST = new Enemy_Idle();

	_Enemy->set_Enemy_State(Idle_ST);
}