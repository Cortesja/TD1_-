#include "Camera.h"

Camera::Camera() {
	pos_ = { 0 };
	scroll_ = { 0 };
	v = { 0 };
}

Camera::~Camera() {

}

Vector2 Camera::ToScreenV2(Vector2 playerPos) {

	scroll_.x = playerPos.x - kWindowWidth / 2;
	scroll_.y = playerPos.y - kWindowHeight / 2;

	if (scroll_.x < 0) {
		scroll_.x = 0;
	}
	if (scroll_.x >= WORLD_WIDTH - kWindowWidth) {
		scroll_.x = WORLD_WIDTH - kWindowWidth;
	}

	if (scroll_.y < 0) {
		scroll_.y = 0;
	}
	if (scroll_.y >= WORLD_HEIGHT - kWindowHeight) {
		scroll_.y = WORLD_HEIGHT - kWindowHeight;
	}

	pos_.x = playerPos.x - scroll_.x;
	pos_.y = playerPos.y - scroll_.y;

	return pos_;
} 

Position Camera::ToScreenV4(Position pos) {
	const Vector2 kWorldToScreenTranslate = { 0.0f, 0.0f };
	const Vector2 kWorldToScale = { 1.0f, -1.0f };

	Position result = { 0 };
	result.leftTop.x = (pos.leftTop.x * kWorldToScale.x) + kWorldToScreenTranslate.x;
	result.leftTop.y = (pos.leftTop.y * kWorldToScale.y) + kWorldToScreenTranslate.y;

	result.leftBottom.x = (pos.leftBottom.x * kWorldToScale.x) + kWorldToScreenTranslate.x;
	result.leftBottom.y = (pos.leftBottom.y * kWorldToScale.y) + kWorldToScreenTranslate.y;
	
	result.rightTop.x = (pos.rightTop.x * kWorldToScale.x) + kWorldToScreenTranslate.x;
	result.rightTop.y = (pos.rightTop.y * kWorldToScale.y) + kWorldToScreenTranslate.y;

	result.rightBottom.x = (pos.rightBottom.x * kWorldToScale.x) + kWorldToScreenTranslate.x;
	result.rightBottom.y = (pos.rightBottom.y * kWorldToScale.y) + kWorldToScreenTranslate.y;

	return result;
}

