#pragma once
#include "Color.h"

class Light
{
public:
	Vector2 pos_;
	Size size_;
	int mode_;
	int img_;

	Color* color;

public:
	Light();
	~Light() { color->~Color(); }
	void Draw(Vector2 playerPos);
};