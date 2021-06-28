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
	player->setSpeed(6.0);
	player->getPlayerData()->stateEnum = down;
}

void flyAndDownState::update(player * player)
{
	if (player->getPlayer().time % 5 == 4)
	{
		player->setFrameX(player->getPlayer().frameX + 1);
	}

}

void flyAndDownState::exit(player * player)
{
}
