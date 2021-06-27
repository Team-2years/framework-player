#pragma once
#include "gameNode.h"
#include "testScene.h"
#include "stage_3rdFloor_Corridor.h"
#include "stage_2ndFloor_HallA.h"
#include "stage_2ndFloor_room.h"
#include "stage_2ndFloor_HallB.h"
#include "stage_1stFloor_HallA.h"
#include "stage_1stFloor_HallB.h"
#include "stage_1stFloor_room.h"
#include "stage_cafeteria.h"
#include "stage_lobby.h"
#include "stage_Detention.h"

class playGround : public gameNode
{
private:


public:
	playGround();
	~playGround();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	
};

