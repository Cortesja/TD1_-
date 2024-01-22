#pragma once
#include "myStructs.h"
#include "Color.h"

class Backround : Color
{
public:
	Vector2 pos_[3];
	int img_[3];
	int timer_;
	bool night_;
public:
	Backround();
	~Backround();
	void Update(float timeElapsed);
	void Draw();
};

