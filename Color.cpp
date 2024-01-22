#include "Color.h"
#define _USE_MATH_DEFINES
#include <math.h>

void Color::ToCode() {

	colorHandler_ = (R_ << 24) + (G_ << 16) + (B_ << 8) + A_;
}

void Color::SetColor(int color) {
	colorHandler_ = color;
}