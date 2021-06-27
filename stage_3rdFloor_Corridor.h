#pragma once
#include "stage.h"
#include "player.h"
class stage_3rdFloor_Corridor :
	public stage
{
private:
	player* _player;
	tagPlayer* _tagPlayer;
	RECT _door;
	RECT _temp;
	int _count;
	BYTE doorAlpha;
	image* _background1;
	image* _background2;
	image* _background3;
public:
	stage_3rdFloor_Corridor() {}
	~stage_3rdFloor_Corridor() {}

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void cameraWork();
	void doorWork();
};

