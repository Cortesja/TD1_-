#include "Backround.h"
#include "Novice.h"

Backround::Backround() {
	for (int i = 0; i < 3; i++) {
		pos_[i] = {
			0.0f + (i * kWindowWidth), 0.0f
		};
	}
	img_[0] = Novice::LoadTexture("./resources/AL1_backround_1.png");
	img_[1] = Novice::LoadTexture("./resources/AL1_backround_2.png");
	img_[2] = Novice::LoadTexture("./resources/AL1_backround_3.png");

	timer_ = 0;

	color = new Color;

	color->R_ = 255;
	color->G_ = 255;
	color->B_ = 255;
	color->A_ = 255;

	night_ = false;

	color-> colorHandler_ = 0xAAAAAAAA;

	camera = new Camera();
}

Backround::~Backround() {

}

Vector2 Backround::GetPos() {
	return pos_[0];
}

void Backround::Update(float timeElapsed, bool &isShake) {

	if (isShake) {
		camera->isShake_ = isShake;
		isShake = false;
	}

	if (timeElapsed >= 40.0f) {
		night_ = true;
	}

	if (!night_) {
		timer_ += 1;
		if (timer_ % 10 == 0) {
			color->R_ -= 1;
			color->G_ -= 1;
			color->B_ -= 1;
		}
	}
	else {
		color->R_ = 0;
		color->G_ = 0;
		color->B_ = 0;
	}

	color->ToCode();
}

void Backround::Draw() {

	if (camera->isShake_) {
		camera->pos_ = GetPos(), camera->imgHandler_ = img_[0], camera->colorHandler_ = color->colorHandler_;

		camera->screenShake();
	}
	else {
		for (int i = 0; i < 3; i++) {
			//Novice::DrawBox(0, 0, kWindowWidth, kWindowHeight, 0.0f, colorHandler_, kFillModeSolid);
			Novice::DrawSprite((int)pos_[i].x, (int)pos_[i].y, img_[i], 1.0f, 1.0f, 0.0f, color->colorHandler_);
		}
	}
}