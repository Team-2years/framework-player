#include "stdafx.h"
#include "comboState.h"
#include "player.h"
#include "idleState.h"
#include "strongAttackState.h"

state * comboState::inputHandle(player * player)
{
	if (player->getPlayer().frameX >= player->getPlayer().image->getMaxFrameX())
	{
		return new idleState;
	}
	if (player->getPlayer().comboCount == 2 &&
		player->getPlayer().time > 26 && 
		player->getPlayer().time < 30 &&
		KEYMANAGER->isOnceKeyDown('S'))
	{
		return new strongAttackState;
	}
	return nullptr;
}

void comboState::enter(player * player)
{
	player->setImage(IMAGEMANAGER->findImage("캐릭터콤보1"));
	player->setFrameX(0);
	player->setTime(0);
	player->setSpeed(0.f);
	player->setComboCount(0);
	_comboOn = false;
	switch (player->getPlayerData()->frameY)
	{
	case 0:
		player->getPlayerData()->imageErrorX = 35;
		break;
	case 1:
		player->getPlayerData()->imageErrorX = -35;
		break;
	default:
		break;
	}
	player->getPlayerData()->imageErrorY = 0;
	player->getPlayerData()->stateEnum = combo;
}

void comboState::update(player * player)
{
	if (player->getPlayer().time % 4 == 3)
	{
		player->setFrameX(player->getPlayer().frameX + 1);
	}

	/*커맨드 입력 타이밍을 좀 널널하게 잡고 그 타이밍 안에 눌렀으면
	마지막 동작 후에 자동으로 다음 콤보로 연결*/
	switch (player->getPlayer().comboCount)
	{
	case 0:
		if (player->getPlayer().time > 4 &&
			player->getPlayer().time < 19 &&
			KEYMANAGER->isOnceKeyDown('A'))
		{
			_comboOn = true;
		}
		if (player->getPlayer().time == 19 &&
			_comboOn)
		{
			_comboOn = false;
			player->setImage(IMAGEMANAGER->findImage("캐릭터콤보2"));
			player->setFrameX(0);
			player->setTime(0);
			player->setComboCount(1);
		}
		break; 
	case 1:
		if (player->getPlayer().time < 11)
		{
			switch (player->getPlayerData()->frameY)
			{
			case 0:
				player->setX(player->getPlayer().x + 1.5f);
				break;
			case 1:
				player->setX(player->getPlayer().x - 1.5f);
				break;
			default:
				break;
			}
		}
		if (player->getPlayer().time > 11 &&
			player->getPlayer().time < 23 &&
			KEYMANAGER->isOnceKeyDown('A'))
		{ 
			_comboOn = true;
		}
		if (player->getPlayer().time == 23 &&
			_comboOn)
		{
			_comboOn = false;
			player->setImage(IMAGEMANAGER->findImage("캐릭터콤보3"));
			player->setFrameX(0);
			player->setTime(0);
			player->setComboCount(2);
			switch (player->getPlayerData()->frameY)
			{
			case 0:
				player->getPlayerData()->imageErrorX = 20;
				break;
			case 1:
				player->getPlayerData()->imageErrorX = -20;
				break;
			default:
				break;
			}
		}
		break;
	case 2:
		if (player->getPlayer().time < 14)
		{
			switch (player->getPlayerData()->frameY)
			{
			case 0:
				player->setX(player->getPlayer().x + 1.8f);
				break;
			case 1:
				player->setX(player->getPlayer().x - 1.8f);
				break;
			default:
				break;
			}
		}
		break;
	default:
		break;
	}

}

void comboState::exit(player * player)
{

}
