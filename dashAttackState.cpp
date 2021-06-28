#include "stdafx.h"
#include "dashAttackState.h"
#include "idleState.h"
#include "player.h"

state * dashAttackState::inputHandle(player * player)
{
	if (player->getPlayer().frameX >= player->getPlayer().image->getMaxFrameX())
	{
		player->setSpeed(0.f);
		return new idleState;
	}

	return nullptr;
}

void dashAttackState::enter(player * player)
{
	player->setImage(IMAGEMANAGER->findImage("캐릭터대시공격"));
	player->setFrameX(0);
	player->setTime(0);
	player->setComboCount(0);
	player->setSpeed(14.0f);
	switch (player->getPlayerData()->frameY)
	{
	case 0:
		player->getPlayerData()->imageErrorX = 55;
		break;
	case 1:
		player->getPlayerData()->imageErrorX = -55;
		break;
	default:
		break;
	}
	player->getPlayerData()->imageErrorY = 5;
	player->getPlayerData()->stateEnum = dashAttack;
}

void dashAttackState::update(player * player)
{
	if (player->getPlayer().time % 5 == 4)
	{
		player->setFrameX(player->getPlayer().frameX + 1);
	}
	if (player->getPlayerData()->speed > 0.f)
	{
		player->setSpeed(player->getPlayerData()->speed - 0.3f);
		switch (player->getPlayerData()->frameY)
		{
		case 0:
			player->setX(player->getPlayer().x + player->getPlayer().speed);
			break;
		case 1:
			player->setX(player->getPlayer().x - player->getPlayer().speed);
			break;
		default:
			break;
		}
	}
}

void dashAttackState::exit(player * player)
{
}
