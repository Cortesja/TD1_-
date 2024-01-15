#pragma once
#include "myStructs.h"

class Camera {
public:
	Vector2 pos_;
	Vector2 scroll_;
	Position v;
public:
	Camera();
	~Camera();
	Vector2 ToScreenV2(Vector2 pos);
	Position ToScreenV4(Position pos);
};