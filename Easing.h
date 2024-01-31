#pragma once
#include "myStructs.h"

class Easing
{
public:
	Vector2 startPos_ = { 0 };
	Vector2 endPos_ = { 0 };
	Vector2 newPos_ = { 0 };
	Size size_ = { 640.0f, 352.0f };
	float startFrame_ = 0;
	float endFrame_ = 180;
	int img_;
	bool isMove_ = false;
public:

	~Easing() {}
	float easeInSine(float x);
	float easeOutElastic(float x);
	void StartEasing(bool &isMove);
	void StartEasingElastic(bool &isMove);
	void Draw();
};

