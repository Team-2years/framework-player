#include "stdafx.h"
#include "deadState.h"
#include "player.h"

state * deadState::inputHandle(player * player)
{
	return nullptr;
}

void deadState::enter(player * player)
{
	player->setImage(IMAGEMANAGER->findImage("Ä³¸¯ÅÍ»ç¸Á"));
	player->setFrameX(0);
	player->setTime(0);
	player->setSpeed(0);
	player->getPlayerData()->stateEnum = dead;
	switch (player->getPlayerData()->frameY)
	{
	case 0:
		player->getPlayerData()->imageErrorX = 24;
		break;
	case 1:
		player->getPlayerData()->imageErrorX = -24;
		break;
	default:
		break;
	}
}

void deadState::update(player * player)
{
	if (player->getPlayer().time % 5 == 4)
	{
		player->setFrameX(player->getPlayer().frameX + 1);
		if (player->getPlayer().frameX >= player->getPlayer().image->getMaxFrameX())
			player->setFrameX(player->getPlayer().image->getMaxFrameX());
	}
}

void deadState::exit(player * player)
{

}
