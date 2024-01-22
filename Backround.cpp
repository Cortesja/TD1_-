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

	R_ = 255;
	G_ = 255;
	B_ = 255;
	A_ = 255;

	night_ = false;

	colorHandler_ = 0xAAAAAAAA;
}

Backround::~Backround() {

}

void Backround::Update(float timeElapsed) {

	if (timeElapsed >= 40.0f) {
		night_ = true;
	}

	if (!night_) {
		timer_ += 1;
		if (timer_ % 10 == 0) {
			R_ -= 1;
			G_ -= 1;
			B_ -= 1;
		}
	}
	else {
		R_ = 0;
		G_ = 0;
		B_ = 0;
	}

	ToCode();
}

void Backround::Draw() {

	for (int i = 0; i < 3; i++) {
		//Novice::DrawBox(0, 0, kWindowWidth, kWindowHeight, 0.0f, colorHandler_, kFillModeSolid);
		Novice::DrawSprite((int)pos_[i].x, (int)pos_[i].y, img_[i], 1.0f, 1.0f, 0.0f, colorHandler_);
	}
}