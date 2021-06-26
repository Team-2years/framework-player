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
	OBSERVE_STATE_TRIGGER, //�����ϴ� �ൿ. ���� ���� ������Ʈ ���� ������ �ش� ������Ʈ�� �������.
	CANT_JESTURE, //�ٿ�, �ǰ� � ���� �ൿ ������ ���
	NORMAL_ATTACK_TRIGGER, //�⺻������ ���ϰ� �ϴ� Ʈ����
	DASH_ATTACK_TRIGGER,	//�뽬������ �ϱ� ���� Ʈ���� 
	JUMP_ATTACK_TRIGGER		//���������� �ϱ� ���� Ʈ����.
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
//���������� switch�� �Ἥ ������ȯ �ϱ� ���ؼ� �������.
//���ó : EnemyManager���� ���ʹ� �ǰ� ���Ҷ����� �ǰ� state �ٲ��ֱ�


struct tagEnemyInfo
{
	RECT _rc;	//�浹������ ��
	int x, y;	//rc�� ����
	int z; //z��. ���߿� ���� �ǰ� Ÿ�� �������� �� ����. 


	image* _image; //�̹��� Ŭ���� ����
	const char* imageName; //�ش� IMAGEMANAGER���� �ش� �̹����� ã�� ���� key��
	const char* imageName_RenderManager;//�����Ŵ������� �̹��� Ű���� �־��ֱ� ���� ���� 

	bool isRight;		//���������� �Ǵܿ���

	int range; //���ʹ��� �Ǵܹ���. �ϴ� �ӽ÷� �����س��� 
	int AttackRange = 70;//���� ��Ÿ�. �ӽ÷� ����.

	int Hp;//ü��

	int stiffness; //������ ���� ���� 
	
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

	int triggerCount;//�ش� Ʈ���� ������Ʈ������ ī����
	int updateTriggerCount;//���������� �����ϰ� triggercount���� �������� 0�� �� ��� Ʈ���Ÿ� �ٲ��ֱ�.

	EnemyKind test;

public:

	//==========================================================================

	//void input_state_data(Enemy_State* getNewstate);//������Ʈ ���¸� �������� �Լ�
	void input_state_data(int targetX, int targetY);//������Ʈ ���¸� �������� �Լ�


	virtual HRESULT init(int _x, int _y, const char* _imageName, int _Hp); //init
	virtual void update(int targetX, int targetY);	//���� �÷��̾� x,y���� �ȳ־���, �̹��� �Ǵ� 
	virtual void release();
	virtual void render();
		
	//==========================================================================

	/*
	state���� �ش��ϴ� ���� ��������
	EnemyBasic�� ���������ַ�����.	
	*/

	//==========================================================================

	//���ʹ� ����ü ���� ��������(getter)
	tagEnemyInfo* getEnemyInfo() { return &_EnemyInfo; }
	EnemyTrigger getAITRIGGER() { return _AI; }
	Enemy_State* getEnemyStateInfo() { return _state; }
	Enemy_State_enum getEnemyStateEnumInfo() { return _enum_state; }

	//==========================================================================

	//���ʹ� ���� ������(setter)
	void setEnemyImage(image* _image) { _EnemyInfo._image = _image; }//�̹��� ����

	void setEnemyPointX(float _x) { _EnemyInfo.x = _x; }
	void setEnemyPointY(float _y) { _EnemyInfo.y = _y; }

	void setEnemyTestText(const char* _TT) { testText = _TT; }

	void set_Enemy_State(Enemy_State* _new_State);//���ʹ� ������Ʈ �����.���ݴ��ϰų� �׾����� ����?
	void set_Enemy_State_Enum(Enemy_State_enum _new_Enum_state) { _enum_state = _new_Enum_state; }

	void set_Enemy_Hp(int _Hp) { _EnemyInfo.Hp -= _Hp; }//�⺻������ - ����.

	void setEnemyImageKey(const char* this_imageName) { _EnemyInfo.imageName_RenderManager = this_imageName; }
	
	void setEnemyShedowRect();

	//==========================================================================

	//������
	void Controller(image* _FieldImage);

	void moveLeft(image* _FieldImage);
	void moveRight(image* _FieldImage);
	void moveUp(image* _FieldImage);
	void moveDown(image* _FieldImage);

	//==========================================================================
};

