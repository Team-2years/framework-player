#include "stdafx.h"
#include "strongAttackState.h"
#include "idleState.h"
#include "player.h"

state * strongAttackState::inputHandle(player * player)
{
	if (player->getPlayer().frameX >= player->getPlayer().image->getMaxFrameX())
	{
		return new idleState;
	}
	return nullptr;
}

void strongAttackState::enter(player * player)
{
	player->setImage(IMAGEMANAGER->findImage("캐릭터강공격"));
	player->setTime(0);
	player->setFrameX(0);
	player->setComboCount(0);
}

void strongAttackState::update(player * player)
{
	if (player->getPlayer().time % 5 == 4)
	{
		player->setFrameX(player->getPlayer().frameX + 1);
	}
}

void strongAttackState::exit(player * player)
{
}
