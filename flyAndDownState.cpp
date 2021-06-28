#include "stdafx.h"
#include "flyAndDownState.h"
#include "downState.h"
#include "player.h"

state * flyAndDownState::inputHandle(player * player)
{
	if (player->getPlayer().frameX >= player->getPlayer().image->getMaxFrameX())
	{
		return new downState;
	}
	return nullptr;
}

void flyAndDownState::enter(player * player)
{
	player->setImage(IMAGEMANAGER->findImage("캐릭터멀리날아감"));
	player->setFrameX(0);
	player->setTime(0);
	player->setSpeed(9.0);
	player->getPlayerData()->stateEnum = down;
}

void flyAndDownState::update(player * player)
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

void flyAndDownState::exit(player * player)
{
}
