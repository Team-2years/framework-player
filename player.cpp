#include "stdafx.h"
#include "player.h"

HRESULT player::init()
{
	IMAGEMANAGER->addFrameImage("캐릭터기본", "img/player/KyokoIdle.bmp", 1404, 414, 12, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("캐릭터무브", "img/player/KyokoMove.bmp", 1476, 402, 12, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("쿄코발차기", "img/player/KyokoKick.bmp", 6402, 432, 22, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("캐릭터달리기", "img/player/KyokoRun.bmp", 2736, 384, 16, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("캐릭터콤보1", "img/player/KyokoCombo1.bmp", 1062, 390, 6, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("캐릭터콤보2", "img/player/KyokoCombo2.bmp", 1470, 402, 7, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("캐릭터콤보3", "img/player/KyokoCombo3.bmp", 2952, 414, 12, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("캐릭터강공격", "img/player/KyokoStrongAttack.bmp", 2040, 462, 8, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("캐릭터점프", "img/player/KyokoJump.bmp", 405, 420, 3, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("캐릭터점프강공격", "img/player/KyokoJumpStrongAttack.bmp", 1551, 522, 11, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("캐릭터대시공격", "img/player/KyokoDashAttack.bmp", 1728, 378, 8, 2, true, RGB(255, 0, 255), true);
	_player.state = new idleState;
	_player.state->enter(this);
	_player.image->setFrameX(0);
	_player.frameY = 0;
	
	_player.x = WINSIZEX/2;
	_player.y = WINSIZEY/2 + 200;
	_player.z = 0.f;
	_player.frameX = 0;
	_player.gravity = 0.7f;
	_player.jumpPower = 0.f;
	_player.time = 0;
	_player.speed = 0.0f;
	_player.moveCommandInput = 0;
	_player.attackCommandInput = 0;
	_player.comboCount = 0;
	_player.collsionRcWidth = 70;
	_player.collsionRcHeight = 40;
	_player.imageErrorX = 0.f;
	_player.imageErrorY = 0.f;
	_player.rc = RectMakeCenter(_player.x,
		_player.y - 105,
		_player.collsionRcWidth,
		_player.collsionRcHeight);
	return S_OK;
}

void player::release()
{

}

void player::update()
{
	inputHandle();
	_player.state->update(this);
	//타임은 계속 올라가고 커맨드 입력시간은 줄임
	_player.time++;
	if (_player.moveCommandInput > 0)
		_player.moveCommandInput--;
	if (_player.attackCommandInput > 0)
		_player.attackCommandInput--;

	//일단 대충 콜리전 렉트
	

	_player.rc = RectMakeCenter(
		_player.x, 
		_player.y,
		_player.collsionRcWidth,
		_player.collsionRcHeight);

	if (_player.time == 50)
		_player.time = 1;
	
}

void player::render()
{
	Rectangle(getMemDC(), _player.rc);
	EllipseMakeCenter(getMemDC(), _player.x, _player.y, 90, 45);
	RENDERMANAGER->push_BackFrameImageRenderInfo(_player.y, _player.image,
		_player.x - _player.image->getFrameWidth() * 0.5 - _player.imageErrorX,
		_player.y - _player.image->getFrameHeight() - _player.z - _player.imageErrorY,
		_player.frameX,
		_player.frameY, true);
}

void player::setAttackRect()
{
	
}

//업데이트마다 상태가 바뀌는지 체크
void player::inputHandle()
{
	state* tmpstate = _player.state->inputHandle(this);
	if (tmpstate != nullptr)
	{
		SAFE_DELETE(_player.state);
		_player.state = tmpstate;
		_player.state->enter(this);
	}

}
