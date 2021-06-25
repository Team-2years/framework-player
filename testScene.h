#pragma once
#include "gameNode.h"
#include "player.h"

class testScene :
	public gameNode
{
private:
	BYTE doorAlpha;
	image* _school_girl;
	RECT _rc;
	RECT _door;
	RECT _temp;
	animation* _school_girl_ani;
	animation* _sit_boy_ani;
	animation* _MrRudis_idle_ani;
	image* _background;
	image* _background2;
	image* _background3;
	player* _player;

	tagPlayer* _tagPlayer;
	int _count;
public:
	testScene() {}
	~testScene() {}

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void pixelCollision();

};

