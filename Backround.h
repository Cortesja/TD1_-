#pragma once
#include "myStructs.h"

class Backround
{
public:
	Vector2 pos_[3];
	int img_[3];
public:
	Backround();
	~Backround();
	void Draw();
};

