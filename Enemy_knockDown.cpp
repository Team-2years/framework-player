#include "stdafx.h"
#include "Enemy_Basic.h"

#include "Enemy_knockDown.h"
#include "Enemy_KnockDown_2.h"


#include "Enemy_Idle.h"

Enemy_State * Enemy_knockDown::input_state(Enemy_Basic * _Enemy, bool reverse, int targetX, int targetY)
{
	return nullptr;
}

void Enemy_knockDown::update(Enemy_Basic * _Enemy, int targetX, int targetY)
{
	
}

void Enemy_knockDown::release(Enemy_Basic * _Enemy)
{
}

void Enemy_knockDown::render()
{
}

void Enemy_knockDown::enter_this_state(Enemy_Basic * _Enemy)
{
	_Enemy->setEnemyTestText("KNOCK_DOWN_1");
	_Enemy->set_Enemy_State_Enum(KNOCK_DOWN);

	
	//Enemy_Image_Knock_Down_1_School_Girl

	
	_Enemy->set_Enemy_State_Enum(DAMAGED_1);

	//recoverCount = 0;



	char str[128] = "Enemy_Image_Attack_3_";

	strcat_s(str, _Enemy->getEnemyInfo()->imageName);

	string Idle_Image = str;

	_Enemy->setEnemyImage(IMAGEMANAGER->findImage(Idle_Image));

	frameCount = 0;
	frameUpdateCount = 5;
	
}
