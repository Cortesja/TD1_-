#include "Backround.h"
#include "Novice.h"

Backround::Backround() {
	for (int i = 0; i < 4; i++) {
		pos_[i] = {
			0.0f, 0.0f
		};
	}

	for (int i = 2; i < 4; i++) {
		pos_[i] = {
			(float)(i - 2) * kWindowWidth, 0.0f
		};
	}

	img_[0] = Novice::LoadTexture("./resources/haikei1.png");
	img_[1] = Novice::LoadTexture("./resources/titleLayer1.png");
	img_[2] = Novice::LoadTexture("./resources/titleLayer2.png");
	img_[3] = Novice::LoadTexture("./resources/titleLayer3.png");

	timer_ = 0;
	aniTimer_ = 0;
	speed_ = 1;

	color = new Color;

	color->R_ = 255;
	color->G_ = 255;
	color->B_ = 255;
	color->A_ = 255;

	easing = new Easing;
	size_ = { 640.0f, 352.0f };

	easing->startPos_ = { float(kWindowWidth / 4), -500.0f - (size_.h / 2) };
	easing->endPos_ = { float(kWindowWidth / 4), float(kWindowHeight / 2 - (size_.h / 2)) };

	easing->startFrame_ = 0;
	easing->endFrame_ = 180;

	easing->img_ = Novice::LoadTexture("./resources/stageClear.png");


	night_ = false;

	color-> colorHandler_ = 0xFFFFFFFF;

	camera = new Camera();
}

Backround::~Backround() {

}

Vector2 Backround::GetPos() {
	return pos_[0];
}

void Backround::Update(float timeElapsed) {

	/*if (isShake) {
		camera->isShake_ = isShake;
	}*/

	if (timeElapsed >= 20.0f) {
		night_ = true;
	}

	if (!night_) {
		timer_ += 1;
		if (timer_ % 5 == 0) {
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
		Novice::DrawSprite((int)pos_[0].x, (int)pos_[0].y, img_[0], 1.0f, 1.0f, 0.0f, color->colorHandler_);
	}
}

void Backround::DrawTitleScreen() {

	for (int i = 2; i < 4; i++) {
		Novice::DrawSprite((int)pos_[i].x, (int)pos_[i].y, img_[i], 1.0f, 1.0f, 0.0f, color->colorHandler_);

		pos_[i].x -= speed_;
	}

	if (pos_[2].x < -kWindowWidth) {
		pos_[2].x = 1280 - 5;
	}
	if (pos_[3].x < -kWindowWidth) {
		pos_[3].x = 1280 - 5;
	}

	Novice::DrawSprite((int)pos_[1].x, (int)pos_[1].y, img_[1], 1.0f, 1.0f, 0.0f, color->colorHandler_);
}