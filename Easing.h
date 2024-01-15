#pragma once
#include "myStructs.h"

class Easing
{
public:
	Vector2 startPos_;
	int endFrame;
	bool isMove_ = false;
public:
	Vector2 easeInSine(float x);
};

