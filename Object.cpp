#include "Object.h"
#include "Novice.h"
#include <assert.h>

Object::Object() {
	this->img = Novice::LoadTexture("./resources/objects/spikeBall.png");
	this->size = { 200.0f, 25.0f };

	this->pos_.leftTop = { -this->size.w / 2, -this->size.h / 2 };
	this->pos_.leftBottom = { -this->size.w / 2, this->size.h / 2 };
	this->pos_.rightTop = { this->size.w / 2, -this->size.h / 2 };
	this->pos_.rightBottom = { this->size.w / 2, this->size.h / 2 };

	this->speed_ = 5.0f;

	//位置変更したあとの変数を良いします
	this->newPos_.leftTop = { 0 };
	this->newPos_.leftBottom = { 0 };
	this->newPos_.rightTop = { 0 };
	this->newPos_.rightBottom = { 0 };

	position_.x = 800;
	position_.y = 180;

	color = new Color;
	color->colorHandler_ = 0xFFFFFFFF;

	timer_ = 0;
}

Object::~Object() {
	color->~Color();
}

//使われてない
void Object::Multiply(Matrix3x3 matrix) {

	this->newPos_.leftTop.x = pos_.leftTop.x * matrix.m[0][0] + pos_.leftTop.y * matrix.m[1][0];
	this->newPos_.leftTop.y = pos_.leftTop.x * matrix.m[0][1] + pos_.leftTop.y * matrix.m[1][1];

	this->newPos_.leftBottom.x = pos_.leftBottom.x * matrix.m[0][0] + pos_.leftBottom.y * matrix.m[1][0];
	this->newPos_.leftBottom.y = pos_.leftBottom.x * matrix.m[0][1] + pos_.leftBottom.y * matrix.m[1][1];

	this->newPos_.rightTop.x = pos_.rightTop.x * matrix.m[0][0] + pos_.rightTop.y * matrix.m[1][0];
	this->newPos_.rightTop.y = pos_.rightTop.x * matrix.m[0][1] + pos_.rightTop.y * matrix.m[1][1];

	this->newPos_.rightBottom.x = pos_.rightBottom.x * matrix.m[0][0] + pos_.rightBottom.y * matrix.m[1][0];
	this->newPos_.rightBottom.y = pos_.rightBottom.x * matrix.m[0][1] + pos_.rightBottom.y * matrix.m[1][1];

	newPos_.leftTop.x += 800;
	newPos_.leftTop.y += 180;
	newPos_.leftBottom.x += 800;
	newPos_.leftBottom.y += 180;
	newPos_.rightTop.x += 800;
	newPos_.rightTop.y += 180;
	newPos_.rightBottom.x += 800;
	newPos_.rightBottom.y += 180;
}

void Object::ToScreen() {
	const Vector2 kWorldToScreenTranslate = { 0.0f,500.0f };
	const Vector2 kWorldToScreenScale = { 1.0f,-1.0f };

	this->newPos_.leftTop.x = (this->newPos_.leftTop.x * kWorldToScreenScale.x) + kWorldToScreenTranslate.x;
	this->newPos_.leftTop.y = (this->newPos_.leftTop.y * kWorldToScreenScale.y) + kWorldToScreenTranslate.y;
	this->newPos_.leftBottom.x = (this->newPos_.leftBottom.x * kWorldToScreenScale.x) + kWorldToScreenTranslate.x;
	this->newPos_.leftBottom.y = (this->newPos_.leftBottom.y * kWorldToScreenScale.y) + kWorldToScreenTranslate.y;
	this->newPos_.rightTop.x = (this->newPos_.rightTop.x * kWorldToScreenScale.x) + kWorldToScreenTranslate.x;
	this->newPos_.rightTop.y = (this->newPos_.rightTop.y * kWorldToScreenScale.y) + kWorldToScreenTranslate.y;
	this->newPos_.rightBottom.x = (this->newPos_.rightBottom.x * kWorldToScreenScale.x) + kWorldToScreenTranslate.x;
	this->newPos_.rightBottom.y = (this->newPos_.rightBottom.y * kWorldToScreenScale.y) + kWorldToScreenTranslate.y;
}

void Object::Update(float timeElapsed, bool night, Vector2 playerPos, bool &playerHit) {
	float distance[16];
	Vector2 line[4];
	Vector2 lineEnd[4];

	line[0] = { newPos_.leftTop.x, newPos_.leftTop.y };
	lineEnd[0] = { newPos_.rightTop.x, newPos_.rightTop.y };

	line[1] = { newPos_.leftBottom.x, newPos_.leftBottom.y };
	lineEnd[1] = { newPos_.rightBottom.x,newPos_.rightBottom.y };

	line[2] = { newPos_.leftBottom.x, newPos_.leftBottom.y };
	lineEnd[2] = { newPos_.leftTop.x, newPos_.leftTop.y };

	line[3] = { newPos_.rightTop.x, newPos_.rightTop.y };
	lineEnd[3] = { newPos_.rightBottom.x, newPos_.rightBottom.y };

	float dot[4];
	float total[4];

	distance[0] = playerPos.x - line[0].x;
	distance[1] = playerPos.y - line[0].y;
	distance[2] = playerPos.x - lineEnd[0].x;
	distance[3] = playerPos.y - lineEnd[0].y;

	distance[4] = playerPos.x - line[1].x;
	distance[5] = playerPos.y - line[1].y;
	distance[6] = playerPos.x - lineEnd[1].x;
	distance[7] = playerPos.y - lineEnd[1].y;

	distance[8] = playerPos.x - line[2].x;
	distance[9] = playerPos.y - line[2].y;
	distance[10] = playerPos.x - lineEnd[2].x;
	distance[11] = playerPos.y - lineEnd[2].y;

	distance[12] = playerPos.x - line[3].x;
	distance[13] = playerPos.y - line[3].y;
	distance[14] = playerPos.x - lineEnd[3].x;
	distance[15] = playerPos.y - lineEnd[3].y;

	dot[0] = distance[0] * distance[3] - distance[1] * distance[2];
	total[0] = distance[0] + distance[1] + distance[2] + distance[3];

	dot[1] = distance[4] * distance[7] - distance[5] * distance[6];
	total[1] = distance[4] + distance[5] + distance[6] + distance[7];

	dot[2] = distance[8] * distance[11] - distance[9] * distance[10];
	total[2] = distance[8] + distance[9] + distance[10] + distance[11];

	dot[3] = distance[12] * distance[15] - distance[13] * distance[14];
	total[3] = distance[12] + distance[13] + distance[14] + distance[15];

	if (dot[0] > total[0] && dot[1] < total[1] && dot[2] > total[2] && dot[3] > total[3]) {
 		playerHit = true;
	}

	/*Novice::DrawLine((int)line[0].x, (int)line[0].y, (int)lineEnd[0].x, (int)lineEnd[0].y, RED);
	Novice::DrawLine((int)line[1].x, (int)line[1].y, (int)lineEnd[1].x, (int)lineEnd[1].y, RED);
	Novice::DrawLine((int)line[2].x, (int)line[2].y, (int)lineEnd[2].x, (int)lineEnd[2].y, RED);
	Novice::DrawLine((int)line[3].x, (int)line[3].y, (int)lineEnd[3].x, (int)lineEnd[3].y, RED);*/

	if (timeElapsed >= 20.0f) {
		night = true;
	}

	if (!night) {
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

void Object::Transform(Matrix3x3 matrix) {
	newPos_.leftTop.x = pos_.leftTop.x * matrix.m[0][0] + pos_.leftTop.y * matrix.m[1][0] + 1.0f * matrix.m[2][0];
	newPos_.leftTop.y = pos_.leftTop.x * matrix.m[0][1] + pos_.leftTop.y * matrix.m[1][1] + 1.0f * matrix.m[2][1];
	float w1 = pos_.leftTop.x * matrix.m[0][2] + pos_.leftTop.y * matrix.m[1][2] + 1.0f * matrix.m[2][2];
	assert(w1 != 0);
	newPos_.leftTop.x /= w1;
	newPos_.leftTop.y /= w1;

	newPos_.leftBottom.x = pos_.leftBottom.x * matrix.m[0][0] + pos_.leftBottom.y * matrix.m[1][0] + 1.0f * matrix.m[2][0];
	newPos_.leftBottom.y = pos_.leftBottom.x * matrix.m[0][1] + pos_.leftBottom.y * matrix.m[1][1] + 1.0f * matrix.m[2][1];
	float w2 = pos_.leftBottom.x * matrix.m[0][2] + pos_.leftBottom.y * matrix.m[1][2] + 1.0f * matrix.m[2][2];
	assert(w2 != 0);
	newPos_.leftBottom.x /= w2;
	newPos_.leftBottom.y /= w2;

	newPos_.rightTop.x = pos_.rightTop.x * matrix.m[0][0] + pos_.rightTop.y * matrix.m[1][0] + 1.0f * matrix.m[2][0];
	newPos_.rightTop.y = pos_.rightTop.x * matrix.m[0][1] + pos_.rightTop.y * matrix.m[1][1] + 1.0f * matrix.m[2][1];
	float w3 = pos_.rightTop.x * matrix.m[0][2] + pos_.rightTop.y * matrix.m[1][2] + 1.0f * matrix.m[2][2];
	assert(w3 != 0);
	newPos_.rightTop.x /= w3;
	newPos_.rightTop.y /= w3;

	newPos_.rightBottom.x = pos_.rightBottom.x * matrix.m[0][0] + pos_.rightBottom.y * matrix.m[1][0] + 1.0f * matrix.m[2][0];
	newPos_.rightBottom.y = pos_.rightBottom.x * matrix.m[0][1] + pos_.rightBottom.y * matrix.m[1][1] + 1.0f * matrix.m[2][1];
	float w4 = pos_.rightBottom.x * matrix.m[0][2] + pos_.rightBottom.y * matrix.m[1][2] + 1.0f * matrix.m[2][2];
	assert(w4 != 0);
	newPos_.rightBottom.x /= w4;
	newPos_.rightBottom.y /= w4;
}

void Object::Draw() {
	Novice::DrawQuad(
		(int)this->newPos_.leftTop.x,
		(int)this->newPos_.leftTop.y,
		(int)this->newPos_.rightTop.x,
		(int)this->newPos_.rightTop.y,
		(int)this->newPos_.leftBottom.x,
		(int)this->newPos_.leftBottom.y,
		(int)this->newPos_.rightBottom.x,
		(int)this->newPos_.rightBottom.y,
		0, 0, (int)size.w, (int)size.h, this->img, color->colorHandler_
	);
}