#include "stdafx.h"
#include "idleState.h"
#include "walkState.h"
#include "skillState.h"
#include "runState.h"
#include "comboState.h"
#include "strongAttackState.h"
#include "jumpState.h"
#include "player.h"

state * idleState::inputHandle(player * player)
{
	if (player->getPlayer().moveCommandInput == 0 && KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		player->setFrameY(1);
		player->setSpeed(3.0f);
		player->setMoveCommandInput(20);
		return new walkState;
	}
	if (player->getPlayer().moveCommandInput == 0 && KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		player->setFrameY(0);
		player->setSpeed(3.0f);
		player->setMoveCommandInput(20);
		return new walkState;
	}
	if (player->getPlayer().moveCommandInput > 0 && KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		player->setFrameY(1);
		player->setSpeed(7.0f);
		return new runState;
	}
	if (player->getPlayer().moveCommandInput > 0 && KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		player->setFrameY(0);
		player->setSpeed(7.0f);
		return new runState;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		player->setSpeed(3.0f);
		return new walkState;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		player->setSpeed(3.0f);
		return new walkState;
	}
	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		return new skillState;
	}
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		return new comboState;
	}
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		return new strongAttackState;
	}
	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		return new jumpState;
	}
	return nullptr;
}

void idleState::enter(player * player)
{
	player->setImage(IMAGEMANAGER->findImage("캐릭터기본"));
	player->setFrameX(0);
	player->setTime(0);
	player->setComboCount(0);
}

void idleState::update(player * player)
{
	if (player->getPlayer().frameY == 0)
	{
		player->setX(player->getPlayer().x + player->getPlayer().speed);
	}
	if (player->getPlayer().frameY == 1)
	{
		player->setX(player->getPlayer().x - player->getPlayer().speed);
	}
	if (player->getPlayer().time % 5 == 4)
	{
		player->setFrameX(player->getPlayer().frameX + 1);
		if (player->getPlayer().frameX > player->getPlayer().image->getMaxFrameX())
			player->setFrameX(0);
	}
	if (player->getPlayer().speed > 0.f)
	{
		player->setSpeed(player->getPlayer() .speed - 0.4f);
	}
}

void idleState::exit(player * player)
{

}
