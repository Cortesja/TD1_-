#pragma once
#include "myStructs.h"

class Object
{
public:
	Position pos_;
	Position newPos;
	Vector2 position;
	Size size;
	float speed_;
	int img;
public:
	Object();
	~Object();
	void ToScreen();
	void Multiply(Matrix3x3 matrix);
	void Update(char keys[]);
	void Transform(Matrix3x3 matrix);

	void Draw();
};