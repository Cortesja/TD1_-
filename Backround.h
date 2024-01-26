#pragma once
#include "Color.h"
#include "Camera.h"

class Backround 
{
public:
	Vector2 pos_[3];
	int img_[3];
	int timer_;
	bool night_;

	Camera* camera;
	Color* color;

public:
	Backround();
	~Backround();

	Vector2 GetPos();

	void Update(float timeElapsed);
	void Draw();
};

