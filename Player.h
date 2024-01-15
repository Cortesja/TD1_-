#pragma once
#include "myStructs.h"
#include "Camera.h"

class Player
{
public:
	Vector2 pos_;
	Vector2 newPos_;
	Vector2 vel_;
	Vector2 accel_;

	PositionInt p_;

	int radius_;
	Size size_;
	int speed_;
	Camera* main_;

public:
	Player();
	~Player();
	void ToScreen();
	void MovePlayer(char keys[], char preKeys[], int maptipmap[bMapY][bMapX]);
	void Update();
	void Draw();
};