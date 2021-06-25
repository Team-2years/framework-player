#pragma once
#include "gameNode.h"
#include "button.h"

class selectScene : public gameNode
{
private:
	button* _btnSceneChange;	//씬 변경용



public:
	selectScene();
	~selectScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	//함수포인터가 선언된 곳이 전역공간이라 static 붙여줘야함
	static void cbSceneChange();
};

