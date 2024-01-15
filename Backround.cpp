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
}

Backround::~Backround() {

}

void Backround::Draw() {

	for (int i = 0; i < 3; i++) {
		Novice::DrawSprite((int)pos_[i].x, (int)pos_[i].y, img_[i], 1.0f, 1.0f, 0.0f, 0xFFFFFFFF);
	}
}