#include "Object.h"
#include "Novice.h"
#include <assert.h>

Object::Object() {
	this->img = Novice::LoadTexture("./kukeiWHITE.png");
	this->size = { 200.0f, 100.0f };

	this->pos_.leftTop = { -this->size.w / 2, -this->size.h / 2 };
	this->pos_.leftBottom = { -this->size.w / 2, this->size.h / 2 };
	this->pos_.rightTop = { this->size.w / 2, -this->size.h / 2 };
	this->pos_.rightBottom = { this->size.w / 2, this->size.h / 2 };

	this->position = { 400.0f, 100.0f };
	this->speed_ = 5.0f;

	//位置変更したあとの変数を良いします
	this->newPos.leftTop = { 0 };
	this->newPos.leftBottom = { 0 };
	this->newPos.rightTop = { 0 };
	this->newPos.rightBottom = { 0 };
}

Object::~Object() {
}

//使われてない
void Object::Multiply(Matrix3x3 matrix) {

	this->newPos.leftTop.x = pos_.leftTop.x * matrix.m[0][0] + pos_.leftTop.y * matrix.m[1][0];
	this->newPos.leftTop.y = pos_.leftTop.x * matrix.m[0][1] + pos_.leftTop.y * matrix.m[1][1];

	this->newPos.leftBottom.x = pos_.leftBottom.x * matrix.m[0][0] + pos_.leftBottom.y * matrix.m[1][0];
	this->newPos.leftBottom.y = pos_.leftBottom.x * matrix.m[0][1] + pos_.leftBottom.y * matrix.m[1][1];

	this->newPos.rightTop.x = pos_.rightTop.x * matrix.m[0][0] + pos_.rightTop.y * matrix.m[1][0];
	this->newPos.rightTop.y = pos_.rightTop.x * matrix.m[0][1] + pos_.rightTop.y * matrix.m[1][1];

	this->newPos.rightBottom.x = pos_.rightBottom.x * matrix.m[0][0] + pos_.rightBottom.y * matrix.m[1][0];
	this->newPos.rightBottom.y = pos_.rightBottom.x * matrix.m[0][1] + pos_.rightBottom.y * matrix.m[1][1];
}

void Object::ToScreen() {
	const Vector2 kWorldToScreenTranslate = { 0.0f,500.0f };
	const Vector2 kWorldToScreenScale = { 1.0f,-1.0f };

	this->newPos.leftTop.x = (this->newPos.leftTop.x * kWorldToScreenScale.x) + kWorldToScreenTranslate.x;
	this->newPos.leftTop.y = (this->newPos.leftTop.y * kWorldToScreenScale.y) + kWorldToScreenTranslate.y;
	this->newPos.leftBottom.x = (this->newPos.leftBottom.x * kWorldToScreenScale.x) + kWorldToScreenTranslate.x;
	this->newPos.leftBottom.y = (this->newPos.leftBottom.y * kWorldToScreenScale.y) + kWorldToScreenTranslate.y;
	this->newPos.rightTop.x = (this->newPos.rightTop.x * kWorldToScreenScale.x) + kWorldToScreenTranslate.x;
	this->newPos.rightTop.y = (this->newPos.rightTop.y * kWorldToScreenScale.y) + kWorldToScreenTranslate.y;
	this->newPos.rightBottom.x = (this->newPos.rightBottom.x * kWorldToScreenScale.x) + kWorldToScreenTranslate.x;
	this->newPos.rightBottom.y = (this->newPos.rightBottom.y * kWorldToScreenScale.y) + kWorldToScreenTranslate.y;
}

void Object::Update(char keys[]) {
	if (keys[DIK_W]) {
		this->position.y += speed_;
	}
	if (keys[DIK_A]) {
		this->position.x -= speed_;
	}
	if (keys[DIK_S]) {
		this->position.y -= speed_;
	}
	if (keys[DIK_D]) {
		this->position.x += speed_;
	}
}

void Object::Transform(Matrix3x3 matrix) {
	newPos.leftTop.x = pos_.leftTop.x * matrix.m[0][0] + pos_.leftTop.y * matrix.m[1][0] + 1.0f * matrix.m[2][0];
	newPos.leftTop.y = pos_.leftTop.x * matrix.m[0][1] + pos_.leftTop.y * matrix.m[1][1] + 1.0f * matrix.m[2][1];
	float w1 = pos_.leftTop.x * matrix.m[0][2] + pos_.leftTop.y * matrix.m[1][2] + 1.0f * matrix.m[2][2];
	assert(w1 != 0);
	newPos.leftTop.x /= w1;
	newPos.leftTop.y /= w1;

	newPos.leftBottom.x = pos_.leftBottom.x * matrix.m[0][0] + pos_.leftBottom.y * matrix.m[1][0] + 1.0f * matrix.m[2][0];
	newPos.leftBottom.y = pos_.leftBottom.x * matrix.m[0][1] + pos_.leftBottom.y * matrix.m[1][1] + 1.0f * matrix.m[2][1];
	float w2 = pos_.leftBottom.x * matrix.m[0][2] + pos_.leftBottom.y * matrix.m[1][2] + 1.0f * matrix.m[2][2];
	assert(w2 != 0);
	newPos.leftBottom.x /= w2;
	newPos.leftBottom.y /= w2;

	newPos.rightTop.x = pos_.rightTop.x * matrix.m[0][0] + pos_.rightTop.y * matrix.m[1][0] + 1.0f * matrix.m[2][0];
	newPos.rightTop.y = pos_.rightTop.x * matrix.m[0][1] + pos_.rightTop.y * matrix.m[1][1] + 1.0f * matrix.m[2][1];
	float w3 = pos_.rightTop.x * matrix.m[0][2] + pos_.rightTop.y * matrix.m[1][2] + 1.0f * matrix.m[2][2];
	assert(w3 != 0);
	newPos.rightTop.x /= w3;
	newPos.rightTop.y /= w3;

	newPos.rightBottom.x = pos_.rightBottom.x * matrix.m[0][0] + pos_.rightBottom.y * matrix.m[1][0] + 1.0f * matrix.m[2][0];
	newPos.rightBottom.y = pos_.rightBottom.x * matrix.m[0][1] + pos_.rightBottom.y * matrix.m[1][1] + 1.0f * matrix.m[2][1];
	float w4 = pos_.rightBottom.x * matrix.m[0][2] + pos_.rightBottom.y * matrix.m[1][2] + 1.0f * matrix.m[2][2];
	assert(w4 != 0);
	newPos.rightBottom.x /= w4;
	newPos.rightBottom.y /= w4;
}

void Object::Draw() {
	Novice::DrawQuad(
		(int)this->newPos.leftTop.x,
		(int)this->newPos.leftTop.y,
		(int)this->newPos.leftBottom.x,
		(int)this->newPos.leftBottom.y,
		(int)this->newPos.rightTop.x,
		(int)this->newPos.rightTop.y,
		(int)this->newPos.rightBottom.x,
		(int)this->newPos.rightBottom.y,
		0, 0, 200, 100, this->img, WHITE
	);
}