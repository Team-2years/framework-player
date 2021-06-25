#pragma once
#include "Enemy_State.h"
class Enemy_Attack_2 :
	public Enemy_State
{
private:


public:

	virtual Enemy_State* input_state(Enemy_Basic* _Enemy, bool reverse, int targetX, int targetY); //스테이트 상태와, 좌우값을 받음.
	virtual void update(Enemy_Basic* _Enemy, int targetX, int targetY);
	virtual void release(Enemy_Basic* _Enemy);
	virtual void render();

	virtual void enter_this_state(Enemy_Basic* _Enemy);

	void call_Attack_3_function(Enemy_Basic* _Enemy);



};

