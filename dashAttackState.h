#pragma once
#include "state.h"
class dashAttackState : public state
{
public:
	virtual state* inputHandle(player* player);
	virtual void enter(player* player);
	virtual void update(player * player);
	virtual void exit(player * player);
};

