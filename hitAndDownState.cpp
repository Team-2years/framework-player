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
	player->setSpeed(9.0);
	player->getPlayerData()->stateEnum = down;
}

void hitAndDownState::update(player * player)
{
	if (player->getPlayer().time % 4 == 3)
	{
		player->setFrameX(player->getPlayer().frameX + 1);
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
