#include "Easing.h"
#include "Novice.h"

float Easing::easeInSine(float x) {
	return 1 - cosf((float)(x * M_PI) / 2);
}

void Easing::StartEasing(bool &isMove) {

	if (isMove) {
		startFrame_++;
	}
	if (startFrame_ == endFrame_) {
		isMove = false;
	}

	newPos_.x = startPos_.x + (endPos_.x - startPos_.x) * easeInSine(float(startFrame_ / endFrame_));
	newPos_.y = startPos_.y + (endPos_.y - startPos_.y) * easeInSine(float(startFrame_ / endFrame_));

	Novice::DrawSprite((int)newPos_.x, (int)newPos_.y, img_, 1.0f, 1.0f, 0.0f, WHITE);
}

void Easing::Draw() {
}