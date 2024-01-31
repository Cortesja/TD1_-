#include "Light.h"
#include "Novice.h"

Light::Light() {
	pos_ = { 0 };
	mode_ = 0;
	img_ = Novice::LoadTexture("./resources/player/light.png");
	size_ = { 480.0f,480.0f };

	color = new Color;
	color->colorHandler_ = 0xFFFFFF99;
}

void Light::Draw(Vector2 playerPos) {
	Novice::DrawSprite((int)playerPos.x - (int)(size_.w / 2), (int)playerPos.y - (int)(size_.h / 2), img_, 1.0f, 1.0f, 0.0f, color->colorHandler_);
}