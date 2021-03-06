#pragma once
#include "gameNode.h"
#include "idleState.h"

enum playerStateEnum
{
	idle,
	walk,
	run,
	dashAttack,
	jump,
	jumpStrongAttack,
	combo,
	strongAttack,
	skill,
	hit,
	down,
	dead
};

struct tagPlayer
{
	image* image;				//캐릭 이미지
	state* state;				//상태
	playerStateEnum	stateEnum;	//상태를 외부에서 알 수 있도록 이넘으로
	RECT rc;			//충돌용 렉트
	RECT attackRect;			//공격용 렉트
	float x, y, z;				//좌표
	float hp;					//피통
	float gravity;				//점프 시 중력값
	float jumpPower;			//점프력
	int time;					//프레임 겸 여러가지
	int frameX;					//프레임X
	int frameY;					//프레임Y
	float speed;				//스피드
	int moveCommandInput;		//대시같은거 할때 n초안에 입력해야 나오게
	int attackCommandInput;		//콤보같은거 할때 n초안에 입력해야 나오게
	int comboCount;				//몇번커맨드 썼는지
	float collsionRcWidth;		//이미지마다 렉트 크기 다르게 하려고 일단 만들어둠
	float collsionRcHeight;		//이미지마다 렉트 크기 다르게 하려고 일단 만들어둠
	float imageErrorX;			//이미지 렌더링 시 오차값X
	float imageErrorY;			//이미지 렌더링 시 오차값Y
	bool isHit;					//맞았는가
	bool isAttack;				//적이 플레이어 공격을 맞았는가
	bool isRide;				//오브젝트 위에 있는가(픽셀충돌 예정)
	bool isDead;				//플레이어가 죽었는가
	int objectGround;			//플레이어가 밟을 땅의 Z값
	int hitRecovery;			//경직도(피격시 줄어듬)
};
class player : public gameNode
{
private:
	tagPlayer _player;
	
public:
	HRESULT init();
	void release();
	void update();
	void render();
	void setX(float x) { _player.x = x; }
	void setY(float y) { _player.y = y; }
	void setZ(float z) { _player.z = z; }
	void setImage(image * image) { _player.image = image; }
	void setFrameX(int x) { _player.frameX = x; }
	void setFrameY(int y) { _player.frameY = y; }
	void setJumpPower(float power) { _player.jumpPower = power; }
	void setTime(int time) { _player.time = time; }
	void setSpeed(float speed) { _player.speed = speed; }
	void setMoveCommandInput(int input) { _player.moveCommandInput = input; }
	void setAttackCommandInput(int input) { _player.attackCommandInput = input; }
	void setComboCount(int input) { _player.comboCount = input; }
	void changeState(state * state);
	tagPlayer getPlayer() { return _player; }			//세터 쓸 때
	tagPlayer* getPlayerData() { return &_player; }		//세터쓰기 귀찮을 때
	void inputHandle();
};

