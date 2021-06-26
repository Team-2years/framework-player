#pragma once
#include "stdafx.h"

class Enemy_Basic;

class Enemy_State
{
protected:

	const char* Enemy_State_Text;//디버깅용


	int index=0;//이미지 출력 인덱스	
	int frameCount;
	int frameUpdateCount;


	int Check_range;//해당 범위 안에 있을때, 해당 행동을 하게 하는거?

	image* _image;



public:

	virtual Enemy_State* input_state(Enemy_Basic* _Enemy, bool reverse, int targetX,int targetY)=0; //스테이트 상태와, 좌우값을 받음.
	virtual void update(Enemy_Basic* _Enemy ,int targetX, int targetY)=0; //업데이트 함수.  주로 프레임 이미지 조정or공격 렉트 생성 등을 담당할듯
	virtual void release(Enemy_Basic* _Enemy)=0; //나중에 삭제할듯


	virtual void enter_this_state(Enemy_Basic* _Enemy)=0;//초기화 해주는 함수.

	virtual int getImageIndex() { return index; }

};

