#pragma once
#include "gameNode.h"
#include "player.h"

class stage :
	public gameNode
{
private:
protected:
	
	player* _player;
	tagPlayer* _tagPlayer;
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void pixelCollision(tagPlayer* _tagplayer, string strkey, player* _player);
};

