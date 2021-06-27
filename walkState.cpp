#include "stdafx.h"
#include "walkState.h"
#include "idleState.h"
#include "skillState.h"
#include "comboState.h"
#include "strongAttackState.h"
#include "jumpState.h"
#include "player.h"

state * walkState::inputHandle(player * player)
{	
	//Ű���带 �ϳ��� ���� idle�� ���°� �����ϱ� ����
	//�Ұ����� �༭ �Ұ��� ���� false�� �� idle�� �ǵ���
	if (!_leftMove && !_rightMove && !_upMove && !_downMove)
	{
		player->setSpeed(0.0f);
		return new idleState;
	}
	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		player->setSpeed(0.0f);
		return new skillState;
	}
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		player->setSpeed(0.0f);
		return new comboState;
	}
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		player->setSpeed(0.0f);
		return new strongAttackState;
	}
	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		return new jumpState;
	}
	return nullptr;
}

void walkState::enter(player * player)
{
	player->setImage(IMAGEMANAGER->findImage("ĳ���͹���"));
	player->setFrameX(0);
	player->setTime(0);
	player->getPlayerData()->imageErrorX = 0;
	player->getPlayerData()->imageErrorY = 0;
	player->getPlayerData()->stateEnum = walk;
}

//����Ű�� stay�ϴ� ���� �Ұ� true ���� false
void walkState::update(player * player)
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_leftMove = true;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		_leftMove = false;
	}
	if (_leftMove)
	{
		if (player->getPlayer().frameY == 0)
			player->setFrameY(1);
		player->setX(player->getPlayer().x - player->getPlayer().speed);
		
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_rightMove = true;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		_rightMove = false;
	}
	if (_rightMove)
	{
		if (player->getPlayer().frameY == 1)
			player->setFrameY(0);
		player->setX(player->getPlayer().x + player->getPlayer().speed);
		
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_upMove = true;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_UP))
	{
		_upMove = false;
	}
	if (_upMove)
	{
		player->setY(player->getPlayer().y - player->getPlayer().speed);


	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_downMove = true;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
	{
		_downMove = false;
	}
	if (_downMove)
	{
		player->setY(player->getPlayer().y + player->getPlayer().speed);
		
	}
	if (player->getPlayer().time % 5 == 4)
	{
		player->setFrameX(player->getPlayer().frameX + 1);
		if (player->getPlayer().frameX >= player->getPlayer().image->getMaxFrameX())
			player->setFrameX(0);
	}
}

void walkState::exit(player * player)
{

}
