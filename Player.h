#pragma once
#include "Camera.h"
#include "Easing.h"

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
	Easing* easing;

	Player();
	~Player();

	Vector2 GetPosition() { return { pos_.x + (size_.w / 2), pos_.y + (size_.h / 2) }; }
	Size GetSize() { return size_; };
	void SetPosition(Vector2 pos) { pos_ = pos; };

	void MovePlayer(char keys[], char preKeys[], int maptipmap[bMapY][bMapX], int clearTimer);
	void Update(int maptipmap[bMapY][bMapX], Maptip &maptip);
	void Draw();
};