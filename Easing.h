#pragma once
#include "myStructs.h"

class Easing
{
public:
	Vector2 startPos_;
	Vector2 endPos_;
	Vector2 newPos_;
	float startFrame_;
	float endFrame_;
	int img_;
	bool isMove_ = false;
public:
	float easeInSine(float x);
	void StartEasing(bool &isMove);
	void Draw();
};

