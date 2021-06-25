#include "stdafx.h"
#include "enemyManager.h"

#include "player.h"

#include "Enemy_Die.h"
#include "Enemy_Damaged_1.h"
#include "Enemy_Damaged_2.h"
#include "Enemy_Damaged_3.h"

#include "Enemy_knockDown.h"



HRESULT enemyManager::init()
{

	setting_Unit_school_girl(100, WINSIZEY - 100);


	return S_OK;
}

void enemyManager::release()
{
}

void enemyManager::update()
{
	for (int i = 0; i < _vEnemy.size(); i++)
	{

		
		//������Ʈ�� ������.
		if (!_vEnemy.empty()) _vEnemy[i]->update(_player->getPlayerData()->x, _player->getPlayerData()->y);

		//�浹������
	//	RECT temp;

		//���ʹ� �Ŵ������� ���ʹ����� ���� ��ȯ���� �����ϱ� ���ؼ� �����Ѱ�. �ӽ÷� �ϴ� �׾����� ó���� ��.
		//if (isOnColliderEnter(_vEnemy[i]->getEnemyInfo()->_rc, _TP->getAttackRECT()) 
		//	&& _TP->getIsOn())
		//{
		//	
		//	//Enemy_State* ATTACKED_STATE;
		//	//ATTACKED_STATE = new Enemy_Damaged_1();
		//	//
		//	//_vEnemy[i]->set_Enemy_State(ATTACKED_STATE);

		//	changeState_Attacked(_vEnemy[i]);

		//	break;
		//}

	}

	

}

void enemyManager::render()
{
	for (int i = 0; i < _vEnemy.size(); i++) _vEnemy[i]->render();

}

void enemyManager::setting_Unit_school_girl(int _x, int _y)
{
	Enemy_Basic* create_Enemy;

	create_Enemy = new Enemy_Basic;

	create_Enemy->init(_x, _y, "School_Girl", 100);
	//create_Enemy->input_state_data();

	_vEnemy.push_back(create_Enemy);

}

void enemyManager::changeState_Attacked(Enemy_Basic * _Enemy)
{
	Enemy_State* ATTACKED_STATE;

	switch (_Enemy->getEnemyStateEnumInfo())
	{
	case DAMAGED_1:
		
		ATTACKED_STATE = new Enemy_Damaged_2();
		_Enemy->set_Enemy_State(ATTACKED_STATE);
		break;
	case DAMAGED_2:
		
		ATTACKED_STATE = new Enemy_Damaged_3();
		_Enemy->set_Enemy_State(ATTACKED_STATE);
		break;
	case DAMAGED_3:
		
		ATTACKED_STATE = new Enemy_knockDown();
		_Enemy->set_Enemy_State(ATTACKED_STATE);
		break;
	case KNOCK_DOWN:
		break;
	case KNOCK_DOWN_2:
		break;
	case DIE:
		break;

	default:

		Enemy_State* ATTACKED_STATE;
		ATTACKED_STATE = new Enemy_Damaged_1();

		_Enemy->set_Enemy_State(ATTACKED_STATE);

		break;
	}

}
