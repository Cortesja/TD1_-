#pragma once
#include "myStructs.h"
#include "Camera.h"

class Player
{
private:
	Vector2 pos_;
	Vector2 newPos_;
	Vector2 vel_;
	Vector2 accel_;

	PositionInt p_;

	int radius_;
	Size size_;
	int jumpCount_;
	int speed_;
	int img_[4];
	int imgDeath[4];
	int color_;

public:
	bool isHit_;
	bool isAlive_;

	Player();
	~Player();
	void ToScreen();

	Vector2 GetPosition();
	void MovePlayer(char keys[], char preKeys[], int maptipmap[bMapY][bMapX]);
	void Update(int maptipmap[bMapY][bMapX], Maptip &maptip);
	void Draw();
};