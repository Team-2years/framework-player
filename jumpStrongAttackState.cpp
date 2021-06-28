#include "stdafx.h"
#include "jumpStrongAttackState.h"
#include "idleState.h"
#include "runState.h"
#include "player.h"

state * jumpStrongAttackState::inputHandle(player * player)
{
	if (player->getPlayer().z < 0.f)
	{
		if (player->getPlayerData()->speed == 11.f)
		{
			player->setZ(0.f);
			player->setJumpPower(0.f);
			return new runState;
		}
		else
		{
			player->setZ(0.f);
			player->setJumpPower(0.f);
			player->setSpeed(0.f);
			return new idleState;
		}
	}
	return nullptr;
}

void jumpStrongAttackState::enter(player * player)
{
	player->getPlayerData()->image = IMAGEMANAGER->findImage("캐릭터점프강공격");
	player->getPlayerData()->jumpPower = 8.0f;
	player->getPlayerData()->time = 0;
	player->getPlayerData()->frameX = 0;
	player->getPlayerData()->imageErrorX = 0;
	player->getPlayerData()->imageErrorY = 0;
	player->getPlayerData()->stateEnum = jumpStrongAttack;
}

void jumpStrongAttackState::update(player * player)
{
	player->setZ(player->getPlayer().z + player->getPlayer().jumpPower);
	player->setJumpPower(player->getPlayer().jumpPower - player->getPlayer().gravity);
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		if (player->getPlayer().frameY == 1)
			player->setFrameY(0);
		player->setX(player->getPlayer().x + player->getPlayer().speed);
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		if (player->getPlayer().frameY == 0)
			player->setFrameY(1);
		player->setX(player->getPlayer().x - player->getPlayer().speed);

	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		player->setY(player->getPlayer().y - player->getPlayer().speed);
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		player->setY(player->getPlayer().y + player->getPlayer().speed);
	}
	if (player->getPlayer().time % 5 == 4)
	{
		player->setFrameX(player->getPlayer().frameX + 1);
	}
}

void jumpStrongAttackState::exit(player * player)
{

}
