#include "myStructs.h"

Matrix3x3 MakeTranslateRotateMatrix(Vector2 translate, float theta) {
	Matrix3x3 result = {
		cosf(theta), sinf(theta), 0,
		-sinf(theta), cosf(theta), 0,
		translate.x, translate.y, 1
	};

	return result;
}

Matrix3x3 MakeRotateMatrix(float theta) {
	Matrix3x3 result = {
		cosf(theta), sinf(theta), 0,
		-sinf(theta), cosf(theta), 0,
		0,0,1
	};

	return result;
}

float convertToSec(clock_t time) {
	return ((float)time / CLOCKS_PER_SEC);
}
float getElapsedTime(clock_t time) {
	return convertToSec((clock() - time));
}

bool chkObjHit(Vector2 playerPos, Size playerSize, Vector2 objPos, Size objSize) {
	if (playerPos.x < objPos.x + objSize.w && objPos.x < playerPos.x + playerSize.w) {
		if (playerPos.y < objPos.y + objSize.h && objPos.y < playerPos.y + playerSize.h) {
			return true;
		}
	}
	return false;
}

int ChkVisible(float radius, Vector2 playerPos, Vector2 objectPos) {
	float distance = sqrtf(powf(objectPos.x - playerPos.x, 2) + powf(objectPos.y - playerPos.y, 2));

	if (radius * 0.55 <= distance) {
		return 0x000000FF;
	}
	else if (radius * 0.5 <= distance) {
		return 0x444444FF;
	}
	else {
		return 0x888888FF;
	}
}