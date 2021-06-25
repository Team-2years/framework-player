#include "stdafx.h"
#include "runState.h"
#include "idleState.h"
#include "skillState.h"
#include "jumpState.h"
#include "player.h"

state * runState::inputHandle(player * player)
{
	if (!_leftMove && !_rightMove && !_upMove && !_downMove)
	{
		player->setSpeed(4.0f);
		return new idleState;
	}
	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		player->setSpeed(0.0f);
		return new skillState;
	}
	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		return new jumpState;
	}
	return nullptr;
}

void runState::enter(player * player)
{
	player->setImage(IMAGEMANAGER->findImage("캐릭터달리기"));
	player->setFrameX(0);
	player->setTime(0);
}

void runState::update(player * player)
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
	if (player->getPlayer().time % 3 == 2)
	{
		player->setFrameX(player->getPlayer().frameX + 1);
		if (player->getPlayer().frameX > player->getPlayer().image->getMaxFrameX())
			player->setFrameX(0);
	}
}

void runState::exit(player * player)
{
}
