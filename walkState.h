#pragma once
#include "state.h"

class player;
class walkState : public state
{
private:
	//불의 전사
	bool _rightMove;
	bool _leftMove;
	bool _upMove;
	bool _downMove;
public:
	virtual state* inputHandle(player* player);
	virtual void enter(player* player);
	virtual void update(player * player);
	virtual void exit(player * player);
};

