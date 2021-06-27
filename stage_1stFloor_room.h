#pragma once
#include "stage.h"
class stage_1stFloor_room :
	public stage
{
private:
	image* _background1;
	image* _background2;
	image* _background3;
	player* _player;
	tagPlayer* _tagPlayer;

	RECT _door1;
	BYTE _door1Alpha;
	RECT _door2;
	BYTE _door2Alpha;

	RECT _temp;

public:
	stage_1stFloor_room() {}
	~stage_1stFloor_room() {}

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void cameraWork();
	void doorWork();
};

