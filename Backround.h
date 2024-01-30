#pragma once
#include "Color.h"
#include "Camera.h"
#include "Easing.h"

class Backround 
{
public:
	Vector2 pos_[5];
	Size size_;
	int img_[5];
	int timer_;
	int aniTimer_;
	int speed_;
	bool night_;

	Camera* camera;
	Color* color;
	Easing* easing;

public:
	Backround();
	~Backround();

	Vector2 GetPos();

	void Update(float timeElapsed);
	void Draw();
	void DrawTitleScreen();
};

