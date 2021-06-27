#include "stdafx.h"
#include "hitState.h"
#include "player.h"
#include "idleState.h"

state * hitState::inputHandle(player * player)
{
	if (player->getPlayer().frameX > _hitCount * 4 - 1)
		return new idleState;
	return nullptr;
}

void hitState::enter(player * player)
{
	player->setImage(IMAGEMANAGER->findImage("플레이어피격"));
	player->setFrameX(0);
	player->setTime(0);
	_hitCount = 1;
}

void hitState::update(player * player)
{
	if (player->getPlayer().time % 5 == 4)
	{
		player->setFrameX(player->getPlayer().frameX + 1);
	}
}

void hitState::exit(player * player)
{

}
