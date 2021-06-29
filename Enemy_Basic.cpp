#include "stdafx.h"
#include "Enemy_Basic.h"
#include "Enemy_Idle.h"
#include "Enemy_Move.h"
#include "Enemy_Attack.h"
#include "Enemy_Die.h"


void Enemy_Basic::input_state_data(int targetX, int targetY)
{
	Enemy_State* _newState = _state->input_state(this,_EnemyInfo.isRight,targetX,targetY); //���� �־��� state Ŭ���� �ӽú���



	if (_newState != nullptr)//���� ���� �����Ͱ� ������ ���� �����͸� ���� ��, nullptr�� �������
	{
		SAFE_DELETE(_state);
		_state = _newState;
		_state->enter_this_state(this);
	}
}

HRESULT Enemy_Basic::init(int _x, int _y, const char * _imageName,int _Hp, EnemyKind _kind)
{
	_EnemyInfo.x = _x;
	_EnemyInfo.y = _y;
	_EnemyInfo.z = 0.0f;

	_EnemyInfo.imageName = _imageName;
	_EnemyInfo.imageName_RenderManager = _EnemyInfo.imageName;


	_state = new Enemy_Idle();
	_state->enter_this_state(this);

	_EnemyInfo.ShedowRect = RectMakeCenter(_EnemyInfo.x, _EnemyInfo.y,80,20);
	_EnemyInfo.gravity = 0;
	_EnemyInfo.JumpPower = 0;
	_EnemyInfo.range = 9999;

	_EnemyInfo.Hp = _Hp;
	_EnemyInfo.isRight = true;

	_EnemyInfo.CurrentframeX = _EnemyInfo.CurrentframeY=0;


	Kind = _kind;

	_AI = OBSERVE_STATE_TRIGGER;
	_AI_BOSS = OBSERVE_STATE_TRIGGER_BOSS;
	currentPhase = PHASE_1;

	triggerCount =0;//�ش� Ʈ���� ������Ʈ������ ī����


	//���������� �����ϰ� triggercount���� �������� 0�� �� ��� Ʈ���Ÿ� �ٲ��ֱ�.
	if(Kind==BOSS) updateTriggerCount = 3;
	else updateTriggerCount = RND->getFromIntTo(200, 300);

	//������
	testText = "NON";

	return S_OK;
}

void Enemy_Basic::update(int targetX, int targetY)
{

	input_state_data(targetX, targetY);
	
	_state->update(this, targetX, targetY);

//	_EnemyInfo._rc = RectMakeCenter(_EnemyInfo.x, _EnemyInfo.y, _EnemyInfo._image->getFrameWidth(), _EnemyInfo._image->getFrameHeight());
	_EnemyInfo.ShedowRect = RectMakeCenter(_EnemyInfo.x + RENDERMANAGER->getCameraX(), 
		_EnemyInfo.y  + RENDERMANAGER->getCameraY(),
		80, 20);
	//- _EnemyInfo.JumpPower + _EnemyInfo.gravity

	switch (Kind)
	{
	case BOSS:

		if (_AI_BOSS == OBSERVE_STATE_TRIGGER_BOSS)
		{
			triggerCount++;

			if (triggerCount % updateTriggerCount == 0)
			{
				int randomPattern;


				//����� ���� ���� ���� 
				switch (currentPhase)
				{
				case PHASE_1: 
					randomPattern = RND->getFromIntTo(1, 4);
					break;
				case PHASE_2:  
								//�����Ÿ� �̻��̸� ���Ÿ����ϵ� ���, �ƴϸ� �������ϵ� ���.
					if(getDistance(_EnemyInfo.x,_EnemyInfo.y,targetX,targetY) > 300) randomPattern = RND->getFromIntTo(4, 6);
					else randomPattern = RND->getFromIntTo(1, 6);
					
					break;
				case PHASE_3: 
					
					if (getDistance(_EnemyInfo.x, _EnemyInfo.y, targetX, targetY) > 300) randomPattern = RND->getFromIntTo(4, 7);
					else randomPattern = RND->getFromIntTo(1, 7);
					
					break;
				}


				//���� ���� ����
				switch (_AI_BOSS)
				{
				case 1:
					_AI_BOSS = NORMAL_ATTACK_TRIGGER_BOSS;
					break;
				case 2:
					_AI_BOSS = POWER_ATTACK_TRIGGER_BOSS;
					break;
				case 3:
					_AI_BOSS = POWER_ATTACK_2_TRIGGER_BOSS;
					break;
				case 4:
					_AI_BOSS = TAKKLE_TRIGGER_BOSS;
					break;
				case 5:
					_AI_BOSS = METEOR_JUMP_TRIGGER_BOSS;
					break;
				case 6:
					_AI_BOSS = SUPER_METEOR_JUMP_TRIGGER_BOSS;
					break;
				}
			}
		}


		break;
	default:

		//Ž�� ���� Ʈ�����ϰ��, �����ð����� Ž�� �� ������ ������Ʈ�� �ٲ���
		if (_AI == OBSERVE_STATE_TRIGGER)
		{
			triggerCount++;

			if (triggerCount % updateTriggerCount == 0)
			{
				int RandomPattern = RND->getFromIntTo(2, 5);
				//int RandomPattern = ;
				switch (RandomPattern)
				{
				case 2:		//�Ϲݰ���
					_AI = NORMAL_ATTACK_TRIGGER;
					break;
				case 3:		//�뽬����
					_AI = DASH_ATTACK_TRIGGER;
					break;
				case 4:		//��������
					_AI = JUMP_ATTACK_TRIGGER;
					break;
				}
				//_AI.TriggerName = (EnemyTrigger)RandomPattern;
			}
		}



		break;
	}




}


void Enemy_Basic::release()
{
}

void Enemy_Basic::render()
{
	//Rectangle(getMemDC(), _EnemyInfo._rc);


	//_EnemyInfo._image->frameRender(getMemDC(), 
	//	_EnemyInfo.x - _EnemyInfo._image->getFrameWidth()/2,
	//	_EnemyInfo.y - _EnemyInfo._image->getFrameHeight()/2,
	//	_EnemyInfo._image->getFrameX(), _EnemyInfo._image->getFrameY());
	

	//RENDERMANAGER->push_BackFrameImageRenderInfo(_EnemyInfo._rc.bottom,
	//	_EnemyInfo._image,
	//	_EnemyInfo.x , _EnemyInfo.y ,
	//	_state->getImageIndex(), _EnemyInfo._image->getFrameY());


	RENDERMANAGER->push_BackFrameImageRenderInfo(_EnemyInfo.ShedowRect.bottom ,
		_EnemyInfo._image,
		_EnemyInfo.x , _EnemyInfo.y - _EnemyInfo._image->getFrameHeight()/2 + _EnemyInfo.z,
		_EnemyInfo.CurrentframeX, _EnemyInfo.CurrentframeY);
		



	Rectangle(getMemDC(), _EnemyInfo.ShedowRect);

	//RENDERMANAGER->push_BackFrameImageRenderInfo(_EnemyInfo._rc.bottom,
	//	);


	char str[128];

	//sprintf_s(str,testText);
	//TextOut(getMemDC(), _EnemyInfo.x - 20 + RENDERMANAGER->getCameraX(), _EnemyInfo.y - 220 + RENDERMANAGER->getCameraY(), str, strlen(str));
	

	//switch (_AI)
	//{
	//case OBSERVE_STATE_TRIGGER:		sprintf_s(str, "TRIGGER : OBSERVE");
	//	break;
	//case CANT_JESTURE:	sprintf_s(str, "TRIGGER :STUN");
	//	break;
	//case NORMAL_ATTACK_TRIGGER:	sprintf_s(str, "TRIGGER :NORMAL_ATTACK");
	//	break;
	//case DASH_ATTACK_TRIGGER:	sprintf_s(str, "TRIGGER :DASH_ATTACK");
	//	break;
	//case JUMP_ATTACK_TRIGGER:	sprintf_s(str, "TRIGGER :JUMP_ATTACK");
	//	break;
	//}
	//TextOut(getMemDC(), _EnemyInfo.x - 20 + RENDERMANAGER->getCameraX(), _EnemyInfo.y -200 + RENDERMANAGER->getCameraY(), str, strlen(str));


	//switch(_AI.TriggerName)
}


void Enemy_Basic::set_Enemy_State(Enemy_State * _new_State)
{
	_state = _new_State;

	_state->enter_this_state(this);
	

}

void Enemy_Basic::Controller(image* _FieldImage)
{

	//if (KEYMANAGER->isStayKeyDown(VK_LEFT)) moveLeft(_FieldImage);
	//if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) moveRight(_FieldImage);
	//if (KEYMANAGER->isStayKeyDown(VK_UP)) moveUp(_FieldImage);
	//if (KEYMANAGER->isStayKeyDown(VK_DOWN)) moveDown(_FieldImage);
}

void Enemy_Basic::moveLeft(image* _FieldImage)
{
	if (_EnemyInfo.isRight)
	{
		_EnemyInfo.isRight = false;
		_EnemyInfo._image->setFrameX(_EnemyInfo._image->getMaxFrameX());
	}
	//_image->setX(_image->getX() - 3);
	_EnemyInfo.x -= 3;

	COLORREF FieldPixel = GetPixel(_FieldImage->getMemDC(), _EnemyInfo._rc.left, _EnemyInfo._rc.bottom);

	int r = GetRValue(FieldPixel);
	int g = GetGValue(FieldPixel);
	int b = GetBValue(FieldPixel);

	if (!(r == 255 && g == 0 && b == 255)) _EnemyInfo.x += 3;

}

void Enemy_Basic::moveRight(image* _FieldImage)
{
	if (!_EnemyInfo.isRight)
	{
		_EnemyInfo.isRight = true;
		_EnemyInfo._image->setFrameX(_EnemyInfo._image->getMaxFrameX());
	}
	//_image->setX(_image->getX() - 3);
	_EnemyInfo.x += 3;

	COLORREF FieldPixel = GetPixel(_FieldImage->getMemDC(), _EnemyInfo._rc.right, _EnemyInfo._rc.bottom);

	int r = GetRValue(FieldPixel);
	int g = GetGValue(FieldPixel);
	int b = GetBValue(FieldPixel);

	if (!(r == 255 && g == 0 && b == 255)) _EnemyInfo.x -= 3;
}

void Enemy_Basic::moveUp(image* _FieldImage)
{
	
	

	COLORREF FieldPixel = GetPixel(_FieldImage->getMemDC(), _EnemyInfo.x, _EnemyInfo._rc.bottom-5); //y + _image->getFrameHeight()/2);

	int r = GetRValue(FieldPixel);
	int g = GetGValue(FieldPixel);
	int b = GetBValue(FieldPixel);

	

	_EnemyInfo.y -= 3;

	if (!(r == 255 && g == 0 && b == 255)) _EnemyInfo.y += 3;

	

}

void Enemy_Basic::moveDown(image* _FieldImage)
{
	_EnemyInfo.y += 3;

	COLORREF FieldPixel = GetPixel(_FieldImage->getMemDC(), _EnemyInfo.x, _EnemyInfo.y + _EnemyInfo._image->getFrameHeight()/2);

	int r = GetRValue(FieldPixel);
	int g = GetGValue(FieldPixel);
	int b = GetBValue(FieldPixel);

	if (!(r == 255 && g == 0 && b == 255)) _EnemyInfo.y -= 3;
}
