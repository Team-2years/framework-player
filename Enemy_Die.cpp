#include "stdafx.h"
#include "Enemy_Die.h"

#include "Enemy_Basic.h"

#include "Enemy_Idle.h"

Enemy_State * Enemy_Die::input_state(Enemy_Basic * _Enemy, bool reverse, int targetX, int targetY)
{
	return nullptr;
}

void Enemy_Die::update(Enemy_Basic * _Enemy, int targetX, int targetY)
{
	if (count != NULL)
	{
		count++;


		if (count > 100)
		{
			Enemy_State* new_Idle;

			new_Idle = new Enemy_Idle();

			_Enemy->set_Enemy_State(new_Idle);

			count = NULL;
			
		}
	}
}                                                                                                                                                    

void Enemy_Die::release(Enemy_Basic * _Enemy)
{
}

void Enemy_Die::render()
{
}

void Enemy_Die::enter_this_state(Enemy_Basic * _Enemy)
{
	_Enemy->setEnemyTestText("DIE");
	_Enemy->set_Enemy_State_Enum(DIE);

	count = 1;

}
