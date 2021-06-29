#pragma once
#include "gameNode.h"
#include "Enemy_Basic.h"
#include "player.h"

#include "Enemy_School_boy.h"
#include "Enemy_School_Girl.h"
#include "Enemy_Misuzu_Boss.h"

class player;

class enemyManager :
	public gameNode
{
private:

	typedef vector<Enemy_Basic*> vEnemyVector;
	typedef vector<Enemy_Basic*>::iterator iter_vEnemyVector;

private:

	vEnemyVector _vEnemy;

	player* _player;
	
public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();


	void setting_Unit_school_girl(int _x, int _y);
	void setting_Unit_school_boy(int _x, int _y);

	void setting_Unit_Misuzu(int _x, int _y);

	void setAddressLinkPlayer(player* _playerAddressLink)
	{
		_player = _playerAddressLink;
	}

	void changeState_Attacked(Enemy_Basic* _Enemy);
	

};

