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