#pragma once
#include "gameNode.h"

class animation;

class effect : public gameNode
{
protected:
	int _x;
	int _y;
	bool _isBlend;
	BYTE _alpha;
	image* _effectImage;
	animation* _effectAnimation;
	BOOL _isRunning;
	float _elapsedTime;

public:
	effect();
	virtual ~effect();

	HRESULT init(image* effectImage, int frameW, int frameH, int fps, float elapsedTime);
	void release();
	void update();
	void render();

	void startEffect(int x, int y, bool isBlend = false, BYTE alpha = 255);


	void killEffect();

	BOOL getIsRunning() { return _isRunning; }
};

