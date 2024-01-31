#pragma once
#include "Color.h"

class Object
{
public:
	Position pos_;
	Position newPos_;
	Vector2 position_;
	Color* color;
	Size size;
	float speed_;

	int timer_;
	int img;
public:
	Object();
	~Object();
	void ToScreen();
	void Multiply(Matrix3x3 matrix);
	void Update(float timeElapsed, bool night, Vector2 playerPos, bool &playerHit, bool reset);
	void Transform(Matrix3x3 matrix);

	void Draw();
};