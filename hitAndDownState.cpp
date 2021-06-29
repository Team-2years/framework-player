#include "stdafx.h"
#include "hitAndDownState.h"
#include "downState.h"
#include "player.h"

state * hitAndDownState::inputHandle(player * player)
{
	if (player->getPlayer().frameX == 23)
	{
		return new downState;
	}
	return nullptr;
}

void hitAndDownState::enter(player * player)
{
	player->setImage(IMAGEMANAGER->findImage("캐릭터피격후기상"));
	player->setFrameX(0);
	player->setTime(0);
	player->setSpeed(3.0f);
	player->setJumpPower(12.0f);
	player->setZ(player->getPlayer().z + player->getPlayer().jumpPower);
	player->setJumpPower(player->getPlayer().jumpPower - player->getPlayer().gravity);
	player->getPlayerData()->stateEnum = down;
}

void hitAndDownState::update(player * player)
{
	if (player->getPlayer().z > 0)
	{
		player->setZ(player->getPlayer().z + player->getPlayer().jumpPower);
		player->setJumpPower(player->getPlayer().jumpPower - player->getPlayer().gravity);
		
	}if (player->getPlayer().z < 0)
	{
		player->setZ(0);
	}
	if (player->getPlayer().time % 3 == 2)
	{
		player->setFrameX(player->getPlayer().frameX + 1);
		
	}
	if (player->getPlayer().time < 55)
	{
		switch (player->getPlayer().frameY)
		{
		case 0:
			player->setX(player->getPlayer().x - player->getPlayer().speed);
			break;
		case 1:
			player->setX(player->getPlayer().x + player->getPlayer().speed);
			break;
		default:
			break;
		}
	}
}

void hitAndDownState::exit(player * player)
{
}
