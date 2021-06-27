#pragma once
#include "state.h"
class player;
class hitState : public state
{
private:
	int _hitCount;
public:
	virtual state* inputHandle(player* player);
	virtual void enter(player* player);
	virtual void update(player * player);
	virtual void exit(player * player);
};

