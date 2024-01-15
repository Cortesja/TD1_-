#include "Bullet.h"
#include "Novice.h"

Bullet::Bullet() {
	this->speed_ = 7;
	this->radius_ = 10;
}

Bullet::~Bullet() {

}

void Bullet::Update(Vector2 playerPos) {

	if (isShot) {
		pos_.y -= speed_;
	}
	else {
		pos_.x = playerPos.x;
		pos_.y = playerPos.y;
	}
	if (pos_.y + radius_ <= 0) {
		isShot = false;
	}
}

void Bullet::Draw() {
	if (isShot) {
		Novice::DrawEllipse((int)pos_.x, (int)pos_.y, radius_, radius_, 0.0f, RED, kFillModeSolid);
	}
}