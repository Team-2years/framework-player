#pragma once
#include "gameNode.h"
class stageUI :
	public gameNode
{
private:
	

public:
	stageUI();
	~stageUI();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

};

