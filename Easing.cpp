#include "Easing.h"
#include "Novice.h"

float Easing::easeInSine(float x) {
	return 1 - cosf((float)(x * M_PI) / 2);
}

void Easing::Draw() {
}

float Easing::easeOutElastic(float x) {
	float c4 = (float)(2 * M_PI) / 3;

	if (x == 0)
	{
		return 0;
	}
	else if (x == 1)
	{
		return 1;
	}
	else
	{
		return powf(2, -10 * x) * sinf((float)(x * 10 - 0.75) * c4) + 1;
	}

	//return x == 0 ? 0 : (x == 1 ? 1 : powf(2, -10 * x) * sinf((x * 10 - 0.75) * c4) + 1);
}

void Easing::StartEasing(bool& isMove) {

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

void Easing::StartEasingElastic(bool& isMove) {

	if (isMove) {
		startFrame_++;
	}
	if (startFrame_ == endFrame_) {
		isMove = false;
	}

	newPos_.x = startPos_.x + (endPos_.x - startPos_.x) * easeOutElastic(float(startFrame_ / endFrame_));
	newPos_.y = startPos_.y + (endPos_.y - startPos_.y) * easeOutElastic(float(startFrame_ / endFrame_));

	Novice::DrawSprite((int)newPos_.x, (int)newPos_.y, img_, 1.0f, 1.0f, 0.0f, WHITE);
}