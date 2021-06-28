#include "stdafx.h"
#include "hitState.h"
#include "player.h"
#include "idleState.h"
#include "hitAndDownState.h"

state * hitState::inputHandle(player * player)
{
	if (player->getPlayerData()->time % 8 == 7 && player->getPlayer().frameX >= _hitCount * 4 - 1)
		return new idleState;
	if (player->getPlayerData()->isHit && _hitCount == 3)
		return new hitAndDownState;

	return nullptr;
}

void hitState::enter(player * player)
{
	player->setImage(IMAGEMANAGER->findImage("캐릭터피격"));
	player->setFrameX(0);
	player->setTime(0);
	player->setSpeed(0);
	player->getPlayerData()->stateEnum = hit;
	_hitCount = 1;
}

void hitState::update(player * player)
{
	if (player->getPlayerData()->isHit)
	{
		switch (_hitCount)
		{
		case 1:
			player->setFrameX(4);
			player->setTime(0);
			_hitCount = 2;
			break;
		case 2:
			player->setFrameX(8);
			player->setTime(0);
			_hitCount = 3;
			break;
		default:
			break;
		}
		player->getPlayerData()->isHit = false;
	}
	if (player->getPlayer().frameX == (_hitCount -1) * 4)
	{
		if (player->getPlayer().time % 15 == 14)
		{
			player->setFrameX(player->getPlayer().frameX + 1);
		}

	}
	else if (player->getPlayer().time % 8 == 7)
	{
		player->setFrameX(player->getPlayer().frameX + 1);
	}
}

void hitState::exit(player * player)
{

}
