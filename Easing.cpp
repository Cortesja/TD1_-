#include "Easing.h"

Vector2 Easing::easeInSine(float x) {
	Vector2 result = { 0 };
	
	result.x = 1 - cosf((float)(x * M_PI / 2));
	
	return result;
}