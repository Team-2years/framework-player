#pragma once
#include "stdafx.h"
#include "gameNode.h"
#include "Enemy_State.h"


#define MOVESPEED_RUN  5.0f
#define MOVESPEED_LEFT_RIGHT 3.5f
#define MOVESPEED_UP_DOWN 1.5f

enum EnemyKind
{
	SCHOOL_GIRL,
	SCHOOL_BOY,
	CHEER_LEADER,
	BOSS
};


enum EnemyTrigger
{	
	OBSERVE_STATE_TRIGGER, //관찰하는 행동. 다음 공격 스테이트 입장 전까지 해당 스테이트로 만들어줌.
	CANT_JESTURE, //다운, 피격 등에 의해 행동 못받을 경우
	NORMAL_ATTACK_TRIGGER, //기본공격을 행하게 하는 트리거
	DASH_ATTACK_TRIGGER,	//대쉬공격을 하기 위한 트리거 
	JUMP_ATTACK_TRIGGER		//점프공격을 하기 위한 트리거.
};


enum Enemy_State_enum
{
	IDLE,
	WALK,
	MOVE,
	RUN,
	DASH_ATTACK,
	ATTACK_1,
	//ATTACK_2,
	//ATTACK_3,
	DAMAGED_1,
	DAMAGED_2,
	DAMAGED_3,
	KNOCK_DOWN,
	KNOCK_DOWN_2,
	WAKE_UP,
	DIE
};
//열거형으로 switch문 써서 상태전환 하기 위해서 만들어줌.
//사용처 : EnemyManager에서 에너미 피격 당할때마다 피격 state 바꿔주기


struct tagEnemyInfo
{
	RECT _rc;	//충돌판정용 몸
	int x, y;	//rc의 중점
	int z; //z축. 나중에 공격 피격 타격 관련으로 쓸 변수. 


	image* _image; //이미지 클래스 변수
	const char* imageName; //해당 IMAGEMANAGER에서 해당 이미지를 찾기 위한 key값
	const char* imageName_RenderManager;//렌더매니저에서 이미지 키값을 넣어주기 위한 변수 

	bool isRight;		//오른쪽인지 판단여부

	int range; //에너미의 판단범위. 일단 임시로 설정해놓음 
	int AttackRange = 70;//공격 사거리. 임시로 설정.

	int Hp;//체력

	int stiffness; //경직도 관련 변수 
	
	RECT ShedowRect;
};


class Enemy_Basic :
	public gameNode
{
protected:

	tagEnemyInfo _EnemyInfo;
	
	Enemy_State* _state;
	Enemy_State_enum  _enum_state;

	const char* testText;

	EnemyTrigger _AI;

	int triggerCount;//해당 트리거 업데이트까지의 카운터
	int updateTriggerCount;//랜덤값으로 설정하고 triggercount와의 나머지가 0이 될 경우 트리거를 바꿔주기.

	EnemyKind test;

public:

	//==========================================================================

	//void input_state_data(Enemy_State* getNewstate);//스테이트 상태를 갱신해줄 함수
	void input_state_data(int targetX, int targetY);//스테이트 상태를 갱신해줄 함수


	virtual HRESULT init(int _x, int _y, const char* _imageName, int _Hp); //init
	virtual void update(int targetX, int targetY);	//아직 플레이어 x,y값은 안넣엇고, 이미지 판단 
	virtual void release();
	virtual void render();
		
	//==========================================================================

	/*
	state에서 해당하는 값을 가져오고
	EnemyBasic에 지정시켜주려고함.	
	*/

	//==========================================================================

	//에너미 구조체 정보 가져오기(getter)
	tagEnemyInfo* getEnemyInfo() { return &_EnemyInfo; }
	EnemyTrigger getAITRIGGER() { return _AI; }
	Enemy_State* getEnemyStateInfo() { return _state; }
	Enemy_State_enum getEnemyStateEnumInfo() { return _enum_state; }

	//==========================================================================

	//에너미 정보 수정용(setter)
	void setEnemyImage(image* _image) { _EnemyInfo._image = _image; }//이미지 수정

	void setEnemyPointX(float _x) { _EnemyInfo.x = _x; }
	void setEnemyPointY(float _y) { _EnemyInfo.y = _y; }

	void setEnemyTestText(const char* _TT) { testText = _TT; }

	void set_Enemy_State(Enemy_State* _new_State);//에너미 스테이트 변경용.공격당하거나 죽었을때 쓸듯?
	void set_Enemy_State_Enum(Enemy_State_enum _new_Enum_state) { _enum_state = _new_Enum_state; }

	void set_Enemy_Hp(int _Hp) { _EnemyInfo.Hp -= _Hp; }//기본적으로 - 설정.

	void setEnemyImageKey(const char* this_imageName) { _EnemyInfo.imageName_RenderManager = this_imageName; }
	
	void setEnemyShedowRect();

	//==========================================================================

	//디버깅용
	void Controller(image* _FieldImage);

	void moveLeft(image* _FieldImage);
	void moveRight(image* _FieldImage);
	void moveUp(image* _FieldImage);
	void moveDown(image* _FieldImage);

	//==========================================================================
};

