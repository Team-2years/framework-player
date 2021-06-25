#pragma once
#include "gameNode.h"
#include "testScene.h"
#include "stage_3rdFloor_Corridor.h"
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

