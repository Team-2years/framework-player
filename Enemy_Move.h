#pragma once
#include "Enemy_State.h"

#define OBSERVE_RANGE 300
#define NORMAL_ATTACK_RANGE 80
#define DASH_ATTACK_RANGE 500
#define JUMP_ATTACK_RANGE 200

class Enemy_Move : public Enemy_State
{
private:


	bool isObserve; //탐색중인지
	int RandomObserveUpdateCount; //다음 랜덤 방향으로 가게 해주기
	int ObserveCount;			  //랜덤방향 업데이트 카운트
	float RandomAngle; //랜덤한 앵글로 이동하게 시행함.





public:


	virtual Enemy_State* input_state(Enemy_Basic* _Enemy, bool reverse, int targetX, int targetY); //스테이트 상태와, 좌우값을 받음.
	virtual void update(Enemy_Basic* _Enemy, int targetX, int targetY);
	virtual void release(Enemy_Basic* _Enemy);
	virtual void render();

	virtual void enter_this_state(Enemy_Basic* _Enemy);


	void ImageUpdateFunc(Enemy_Basic* _Enemy);

};

