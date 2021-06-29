#include "stdafx.h"
#include "downState.h"
#include "player.h"
#include "idleState.h"
#include "deadState.h"

state * downState::inputHandle(player * player)
{
	if (player->getPlayer().hp <= 0)
		return new deadState;
	if (player->getPlayer().frameX >= player->getPlayer().image->getMaxFrameX())
	{
		player->getPlayerData()->hitRecovery = 100;
		return new idleState;
	}
	return nullptr;
}

void downState::enter(player * player)
{
	player->setImage(IMAGEMANAGER->findImage("캐릭터피격후기상"));
	player->setFrameX(23);
	player->setTime(0);
	player->setSpeed(0);
}
void downState::update(player * player)
{
	if (player->getPlayer().frameX == 23)
	{
		if(player->getPlayer().time % 80 == 79)
			player->setFrameX(player->getPlayer().frameX + 1);
	}
	else if (player->getPlayer().time % 5 == 4)
	{
		player->setFrameX(player->getPlayer().frameX + 1);
	}
}

void downState::exit(player * player)
{

}
