#pragma once
#include "gameNode.h"
class stage1_3rdFloor :
	public gameNode
{
private:
	// 이미지
	image _background1;
	// 픽셀
	image _background2;
	// 레터 박스
	image _background3;
public:
	stage1_3rdFloor() {}
	~stage1_3rdFloor() {}

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void pixelCollision();
};

