#pragma once
#include "state.h"
class player;
class fallState : public state
{
public:
	virtual state* inputHandle(player* player);
	virtual void enter(player* player);
	virtual void update(player * player);
	virtual void exit(player * player);

};

