#include "stdafx.h"

#include "Enemy_Basic.h"

#include "Enemy_Jump.h"
#include "Enemy_JumpAttack.h"

Enemy_State * Enemy_Jump::input_state(Enemy_Basic * _Enemy, bool reverse, int targetX, int targetY)
{
	if (_Enemy->getEnemyInfo()->JumpPower  < _Enemy->getEnemyInfo()->gravity)
	{
		return new Enemy_JumpAttack();
	}


	return nullptr;
}

void Enemy_Jump::update(Enemy_Basic * _Enemy, int targetX, int targetY)
{
	//_Enemy->setEnemyPointY(_Enemy->getEnemyInfo()->y
	//					- _Enemy->getEnemyInfo()->JumpPower + _Enemy->getEnemyInfo()->gravity);


	if (_Enemy->getEnemyInfo()->isRight)
	{
		_Enemy->setEnemyPointX(_Enemy->getEnemyInfo()->x + MOVESPEED_LEFT_RIGHT * 0.5f);
	}
	else
	{
		_Enemy->setEnemyPointX(_Enemy->getEnemyInfo()->x - MOVESPEED_LEFT_RIGHT*0.5f);
	}


	_Enemy->setEnemyGravity(_Enemy->getEnemyInfo()->gravity + GRAVITY_POWER);
	_Enemy->setEnemyPointZ(_Enemy->getEnemyInfo()->z + _Enemy->getEnemyInfo()->gravity - _Enemy->getEnemyInfo()->JumpPower);
	ImageUpdateFunc(_Enemy);
}

void Enemy_Jump::release(Enemy_Basic * _Enemy)
{
}

void Enemy_Jump::render()
{
}

void Enemy_Jump::enter_this_state(Enemy_Basic * _Enemy)
{
	_Enemy->setEnemyTestText("Jump");
	_Enemy->set_Enemy_State_Enum(DAMAGED_1);


	char str[128] = "Enemy_Image_Jump_";

	strcat_s(str, _Enemy->getEnemyInfo()->imageName);

	_Enemy->setEnemyImageKey(str);

	string Idle_Image = str;

	_Enemy->setEnemyImage(IMAGEMANAGER->findImage(Idle_Image));

	frameCount = 0;
	frameUpdateCount = 4;
	index = 0;

	_Enemy->setEnemyJumpSpeed(JUMP_POWER);
}


void Enemy_Jump::ImageUpdateFunc(Enemy_Basic * _Enemy)
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

			
			}
		}
	}
}
