#pragma once
#include "myStructs.h"

class Bullet
{
public:
	Vector2 pos_;
	int radius_;
	int speed_;
	bool isShot;

public:
	Bullet();
	~Bullet();
	void Update(Vector2 playerPos);
	void Draw();
};

