#include "stdafx.h"
#include "skillState.h"
#include "idleState.h"
#include "player.h"

state * skillState::inputHandle(player * player)
{
	if (player->getPlayer().frameX >= player->getPlayer().image->getMaxFrameX())
	{
		return new idleState;
	}
	return nullptr;
}

void skillState::enter(player * player)
{
	player->setFrameX(0);
	player->setTime(0);
	player->setSpeed(0.f);
	player->setImage(IMAGEMANAGER->findImage("ÄìÄÚ¹ßÂ÷±â"));
	switch (player->getPlayerData()->frameY)
	{
	case 0:
		player->getPlayerData()->imageErrorX = -66;
		break;
	case 1:
		player->getPlayerData()->imageErrorX = 66;
		break;
	default:
		break;
	}
	player->getPlayerData()->imageErrorY = -3;
	player->getPlayerData()->stateEnum = skill;
}

void skillState::update(player * player)
{
	if (player->getPlayer().time % 3 == 2)
	{
		player->setFrameX(player->getPlayer().frameX + 1);
	}
}

void skillState::exit(player * player)
{

}
