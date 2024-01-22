#pragma once
#include "myStructs.h"
#include "Color.h"

class Light : Color
{
public:
	Vector2 pos_;
	Size size_;
	int mode_;
	int img_;

public:
	Light();
	~Light();
	void Draw(Vector2 playerPos);
};