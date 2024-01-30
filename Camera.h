#pragma once
#include "myStructs.h"

class Camera {
public:
	Vector2 pos_;
	Vector2 scroll_;
	Position v;

	int effTimer_;
	int randx_;
	int randy_;
	int max_;
	int min_;

	int imgHandler_;
	int colorHandler_;

	bool isShake_;

public:
	Camera();
	~Camera() {}
	Vector2 ToScreenV2(Vector2 pos);
	Position ToScreenV4(Position pos);

	void screenShake();
};