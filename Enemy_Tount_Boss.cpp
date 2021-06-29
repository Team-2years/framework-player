#include "stdafx.h"
#include "Enemy_Basic.h"

#include "Enemy_Tount_Boss.h"
#include "Enemy_Idle.h"
#include "Enemy_Dash_Attack_Boss.h"

Enemy_State * Enemy_Tount_Boss::input_state(Enemy_Basic * _Enemy, bool reverse, int targetX, int targetY)
{
	if (_Enemy->getEnemyInfo()->CurrentframeX > _Enemy->getEnemyInfo()->_image->getMaxFrameX())
	{
		

	}
	/*
	���� Ƚ������ �����ϰ�, �ش� Ƚ���� �پ��� idle�� ���ư��� �ϱ�
	*/


	return nullptr;
}

void Enemy_Tount_Boss::update(Enemy_Basic * _Enemy, int targetX, int targetY)
{
}

void Enemy_Tount_Boss::release(Enemy_Basic * _Enemy)
{
}

void Enemy_Tount_Boss::enter_this_state(Enemy_Basic * _Enemy)
{
	_Enemy->setEnemyTestText("Misuzu_Tount");
	//_Enemy->set_Enemy_State_Enum();

	char str[128] = "Misuzu_Tount";

	_Enemy->setEnemyImage(IMAGEMANAGER->findImage(str));

	frameCount = 0;
	frameUpdateCount = 5;

	_Enemy->setEnemyFrameX(0);

	if (_Enemy->getEnemyInfo()->isRight) _Enemy->setEnemyFrameY(0);
	else _Enemy->setEnemyFrameY(1);
}


void Enemy_Tount_Boss::ImageUpdateFunc(Enemy_Basic * _Enemy)
{
	if (frameCount % frameUpdateCount == 0)
	{
		if (_Enemy->getEnemyInfo()->isRight)
		{
			_Enemy->setEnemyFrameY(0);
			_Enemy->setEnemyFrameX(_Enemy->getEnemyInfo()->CurrentframeX + 1);

			
		}
		else
		{
			_Enemy->setEnemyFrameY(1);
			_Enemy->setEnemyFrameX(_Enemy->getEnemyInfo()->CurrentframeX + 1);

			
		}
	}
}
